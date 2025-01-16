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

void AuctionItem::AsyncPurchased(PlayerPtr player, uint64 price, uint64 quantity)
{
    vector<ItemOwnerData> purchased_items;      // 구매한 아이템 리스트
    uint64 purchased_item_quantity = 0;         // 실제 구매 개수
    auction::S_PurchaseItem pkt;                // 구매 요청에 대한 응답
    
    // 1. 아이템 구매 처리
    // 1.1 가장 싼 값 <= 내가 사고자 하는 값 -> count만큼 구매 처리
    // 구매 가능한 개수만큼 계속 처리
    while (quantity > 0)
    {
        auto itemData = owner_data_pq.top();
        owner_data_pq.pop();

        // 입찰가보다 단가가 더 높을 경우 구매 불가능
        if (itemData.price > price) break;

        // 등록된 아이템 개수가 입찰 개수보다 많을 경우, 다시 리스트 등록
        if (itemData.quantity > quantity)
        {
            itemData.quantity -= quantity;
            owner_data_pq.push(itemData);

            // 구매 후처리를 위해 구매 개수로 지정 후 push back
            itemData.quantity = quantity;
        }
        else
        {
            itemData.sold_out = true;
        }
        
        // 구매 후처리를 위한 push
        purchased_items.push_back(itemData);
        purchased_item_quantity += itemData.quantity;
        quantity -= itemData.quantity;
    }
    
    // 1.2 처리 결과 플레이어에게 Send
    pkt.set_price(price);
    pkt.set_item_table(item_table);
    pkt.set_is_success(purchased_item_quantity > 0);
    pkt.set_quantity(purchased_item_quantity);

    if (auto session = player->session.lock())
    {
        auto sendBuffer = PacketUtil::MakeSendBuffer(pkt, message::HEADER::AUCTION_PURCHASE_RES);
        auto bufSize = PacketUtil::RequiredSize(pkt );
        session->Send(sendBuffer, bufSize);

        // 2. DB 갱신
        std::shared_ptr<MySQLConnection> conn = GConnectionPool->borrow();
        while (conn == nullptr)
        {
            conn = GConnectionPool->borrow();
        }

        // 트랜잭션
        conn->sql_connection->setAutoCommit(false);
    

        try
        {
            // 구매기록
            std::string purchase_log_insert_sql = "INSERT INTO auction_purchases(user_pk, item_id, quantity, price) VALUES (?,?,?,?);";
            SqlUtils::executeQuery(conn->sql_connection, "GameDB", purchase_log_insert_sql,
                session->user_pk(),
                item_table,
                purchased_item_quantity,
                price
                );

            // 사용자 테라 감소
            std::string user_tera_update_sql = "UPDATE user_tera SET tera = tera - ? "
                                                "WHERE user_pk = ?";
            SqlUtils::executeUpdate(conn->sql_connection, "GameDB", user_tera_update_sql,
                purchased_item_quantity * price,
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
            
            for (auto& purchased_item : purchased_items)
            {
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
            }
            conn->sql_connection->commit();
            
        }
        catch (sql::SQLException exception)
        {
            // TODO : DB 갱신 실패 시, 로그 남기건 다시 재시도 하던 해야함
            conn->sql_connection->rollback();
        }
        conn->sql_connection.reset();
        GConnectionPool->unborrow(conn );
    }
    

    
}

void AuctionItem::AsyncApplyed(PlayerPtr player, uint64 price, uint64 quantity)
{
}

void AuctionItem::AsyncRemoved(PlayerPtr player, uint64 applyed_auction_id)
{
}

void AuctionItem::AsyncUpdate()
{
    // 비우기
    priority_queue<ItemOwnerData, vector<ItemOwnerData>, CompareAuctionItem> empty;
    swap(owner_data_pq, empty);

    // 물품 새로고침
    auto conn = GConnectionPool->borrow();
    while (conn == nullptr)
    {
        conn = GConnectionPool->borrow();
    }

    // 상위 100개 데이터만 가져오기
    std::string auction_item_select_sql = "SELECT pk, user_pk, quantity, price, item_id, UNIX_TIMESTAMP(created_at) FROM auction_items "
    "WHERE item_id = ? ORDER BY created_at DESC LIMIT 100";
    auto results = SqlUtils::executeQuery(conn->sql_connection, "GameDB", auction_item_select_sql,
        item_table);

    while (results->next())
    {
        auto pk = results->getUInt64("pk");
        auto user_pk = results->getUInt64("user_pk");
        auto item_id = results->getUInt64("item_id");
        auto quantity = results->getUInt64("quantity");
        auto price = results->getUInt64("price");
        auto created_at = results->getUInt64("created_at");

        ItemOwnerData item_owner_data(pk, user_pk, price, quantity, created_at);
        owner_data_pq.push(item_owner_data);
    }

    conn->sql_connection.reset();
    GConnectionPool->unborrow(conn);
    
}

