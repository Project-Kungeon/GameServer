#include "pch.h"
#include "AuctionItem.h"

#include "DB/ConnectionPool.h"

using namespace active911;

AuctionItem::AuctionItem(message::ItemTable item_table, asio::io_context& io_context)
    : item_table(item_table), JobQueue(io_context)
{
}

AuctionItem::~AuctionItem()
{
}

void AuctionItem::AsyncPurchased(PlayerPtr player, uint64 auction_id, uint64 quantity)
{
    if (auto session = player->session.lock())
    {
        auction::S_PurchaseItem pkt;                // 구매 요청에 대한 응답
        std::shared_ptr<MySQLConnection> conn = GConnectionPool->borrow();
        while (conn == nullptr)
        {
            conn = GConnectionPool->borrow();
        }
        
        try
        {
            // 1. 아이템 구매 처리
            // 경매장 물품 아이디로 물품 가져오기
            std::string auction_item_sql = "SELECT user_pk, quantity, price, item_id FROM auction_items WHERE pk = ?;";
            auto auction_result_set = SqlUtils::executeQuery(conn->sql_connection, "GameDB", auction_item_sql,
                auction_id
                );
            if (!auction_result_set->next())
            {
                // TODO return Exception
            }

            // 실제 플레이어의 테라 보유액 가져오기
            std::string player_tera_sql = "SELECT tera FROM user_tera WHERE user_pk = ?;";
            auto player_tera_result_set = SqlUtils::executeQuery(conn->sql_connection, "GameDB", auction_item_sql,
                session->user_pk()
                );
            if (!player_tera_result_set->next())
            {
                // TODO return Exception
            }

            // 연산 : 현재 보유 중인 테라로 살 수 있는가?
            auto tera = player_tera_result_set->getUInt64("tera");
            auto auction_price = auction_result_set->getUInt64("price");
            auto auction_quantity = auction_result_set->getUInt64("quantity");
            auto need_tera = auction_price * auction_quantity;
            
            // 1.2 플레이어에게 보낼 처리 결과 만들기
            pkt.set_price(auction_price);
            pkt.set_item_table(item_table);
            pkt.set_is_success(tera >= need_tera);
            pkt.set_quantity(quantity);

            // 구매 결과 후처리
            if (tera >= need_tera)
            {
                // 판매 정보 만들기
                auto seller_pk = auction_result_set->getUInt64("user_pk");
                ItemOwnerData purchased_item = {auction_id, seller_pk, auction_price, auction_quantity, auction_quantity == quantity};
            
                // 2. DB 갱신
                // 트랜잭션 시작
                conn->sql_connection->setAutoCommit(false);

            
                // 구매기록
                std::string purchase_log_insert_sql = "INSERT INTO auction_purchases(user_pk, item_id, quantity, price) VALUES (?,?,?,?);";
                SqlUtils::executeQuery(conn->sql_connection, "GameDB", purchase_log_insert_sql,
                    session->user_pk(),
                    item_table,
                    quantity,
                    auction_price
                    );

                // 사용자 테라 감소
                std::string user_tera_update_sql = "UPDATE user_tera SET tera = tera - ? "
                                                    "WHERE user_pk = ?";
                SqlUtils::executeUpdate(conn->sql_connection, "GameDB", user_tera_update_sql,
                    need_tera,
                    session->user_pk()
                    );

                // 경매장 물품 업데이트 및 삭제
            
                std::string auction_item_update_sql = "UPDATE auction_items SET quantity = quantity - ? "
                                                    "WHERE pk = ?";
                std::string auction_item_delete_sql = "DELETE FROM auction_items "
                                                    "WHERE pk = ?";

                // 구매자 혹은 판매자의 우편함에 물품 혹은 테라 발송
                std::string mailbox_insert_sql = "INSERT INTO user_mailbox (user_pk, sender_name, title, content) VALUES (?, ?, ?, ?)";
                std::string mailbox_item_insert_sql = "INSERT INTO mailbox_item (mail_pk, item_id, item_quantity) VALUES (? , ?, ?)";

                // 구매자에게 우편 발송
                SqlUtils::executeUpdate(conn->sql_connection, "GameDB", mailbox_insert_sql,
                    session->user_pk(),
                    "경매장",
                    "경매장 물품 구입",
                    "입찰 물품입니다.");
                auto buyer_mail_rs = SqlUtils::executeQuery(conn->sql_connection, "GameDB", "SELECT LAST_INSERT_ID()");
            
                auto buyer_mail_id = 0;
                if (buyer_mail_rs->next())
                    buyer_mail_id = buyer_mail_rs->getUInt64(1);
                else
                    throw sql::SQLException("Mailbox does not exist.");
            
                // 다 팔린 물품이라면, DB에서 제거
                if (purchased_item.sold_out)
                {
                    SqlUtils::executeQuery(conn->sql_connection, "GameDB", auction_item_delete_sql,
                        purchased_item.auction_id);
                }
                // 일부만 팔린 물품이라면, 업데이트
                else
                {
                    SqlUtils::executeUpdate(conn->sql_connection, "GameDB", auction_item_update_sql,
                        purchased_item.auction_id,
                        session->user_pk());
                }
                SqlUtils::executeUpdate(conn->sql_connection, "GameDB", mailbox_insert_sql,
                            purchased_item.user_id,
                            "경매장",
                            "경매장 물품 판매",
                            "판매 결과입니다.");
                auto seller_mail_rs = SqlUtils::executeQuery(conn->sql_connection, "GameDB", "SELECT LAST_INSERT_ID()");
                auto seller_mail_id = 0;

                if (seller_mail_rs->next())
                    seller_mail_id = seller_mail_rs->getUInt64(1);
                else
                    throw sql::SQLException("Mailbox does not exist.");

            
                // 발송된 우편과 물품 연관관계
                SqlUtils::executeUpdate(conn->sql_connection, "GameDB", mailbox_item_insert_sql,
                    buyer_mail_id,
                    item_table,
                    purchased_item.quantity
                    );

                SqlUtils::executeUpdate(conn->sql_connection, "GameDB", mailbox_item_insert_sql,
                    seller_mail_id,
                    99, // 테라
                    purchased_item.quantity * purchased_item.price
                    );
            
                conn->sql_connection->commit();
            }
            auto sendBuffer = PacketUtil::MakeSendBuffer(pkt, message::HEADER::AUCTION_PURCHASE_RES);
            auto bufSize = PacketUtil::RequiredSize(pkt);
            session->Send(sendBuffer, bufSize);
                
        }
        catch (sql::SQLException exception)
        {
            // TODO : DB 갱신 실패 시, 로그 남기건 다시 재시도 하던 해야함
            conn->sql_connection->rollback();
            
        }
        conn->sql_connection.reset();
        GConnectionPool->unborrow(conn);
    }
}

void AuctionItem::AsyncApplyed(PlayerPtr player, uint64 price, uint64 quantity)
{
}

void AuctionItem::AsyncRemoved(PlayerPtr player, uint64 applyed_auction_id)
{
}

/*void AuctionItem::AsyncUpdate()
{
    // 비우기
    // priority_queue<ItemOwnerData, vector<ItemOwnerData>, CompareAuctionItem> empty;
    vector<ItemOwnerData> empty;
    swap(owner_item_data, empty);

    // 물품 새로고침
    auto conn = GConnectionPool->borrow();
    while (conn == nullptr)
    {
        conn = GConnectionPool->borrow();
    }

    // 상위 100개 데이터만 가져오기
    std::string auction_item_select_sql = "SELECT pk, user_pk, quantity, price, item_id, UNIX_TIMESTAMP(created_at) AS created_at FROM auction_items "
    "WHERE item_id = ? ORDER BY created_at DESC LIMIT 100";
    auto results = SqlUtils::executeQuery(conn->sql_connection, "GameDB", auction_item_select_sql,
        static_cast<int>(item_table));

    while (results->next())
    {
        auto pk = results->getUInt64("pk");
        auto user_pk = results->getUInt64("user_pk");
        auto item_id = results->getUInt64("item_id");
        auto quantity = results->getUInt64("quantity");
        auto price = results->getUInt64("price");
        auto created_at = results->getUInt64("created_at");

        ItemOwnerData item_owner_data(pk, user_pk, price, quantity, created_at);
        owner_item_data.push_back(item_owner_data);
    }

    conn->sql_connection.reset();
    GConnectionPool->unborrow(conn);
    
}*/

