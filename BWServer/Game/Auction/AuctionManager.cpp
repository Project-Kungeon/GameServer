#include "pch.h"
#include "AuctionItem.h"
#include "AuctionManager.h"
#include <boost/algorithm/string.hpp>

#include "DB/ConnectionPool.h"

// std::shared_ptr<AuctionManager> GAuctionManager = std::make_shared<AuctionManager>();
AuctionManagerPtr GAuctionManager;

AuctionManager::AuctionManager(asio::io_context& io_context)
    : _io_context(io_context)
{
    _AuctionItems[message::ItemTable::GENERAL_HEALTH_POSION] = std::make_shared<AuctionItem>(message::ItemTable::GENERAL_HEALTH_POSION, io_context);
}

AuctionManager::~AuctionManager()
{
}

void AuctionManager::SearchItem(PlayerPtr player, auction::C_SearchItem& pkt)
{
    auction::S_SearchItem searchPkt;

    if (auto session = player->session.lock())
    {
        std::string search_keyword = pkt.item_name().c_str();
        auto conn = GConnectionPool->borrow();
        while (conn == nullptr)
        {
            conn = GConnectionPool->borrow();
        }

        // 상위 100개 데이터만 가져오기
        std::string auction_item_select_sql = "SELECT auction_items.pk as pk, user_pk, quantity, price, item_id, UNIX_TIMESTAMP(created_at) AS created_at"
        " FROM auction_items JOIN item_table ON item_id = item_table.pk"
        " WHERE item_table.name = '%' + ? + '%'"
        " ORDER BY created_at DESC"
        " LIMIT ? OFFSET ?;";
        auto result_set = SqlUtils::executeQuery(conn->sql_connection, "GameDB", auction_item_select_sql,
            search_keyword,
            10,
            pkt.page() - 1);

        while (result_set->next())
        {
            auto item_element = searchPkt.add_item_list();
            item_element->set_auction_pk(result_set->getUInt64("pk"));
            item_element->set_item_table(static_cast<message::ItemTable>(result_set->getUInt64("item_id")));
            item_element->set_price(result_set->getDouble("price"));
            item_element->set_quantity(result_set->getDouble("quantity"));
        }
    
        auto sendBuffer = PacketUtil::MakeSendBuffer(pkt, message::HEADER::AUCTION_SEARCH_RES);
        auto bufSize = PacketUtil::RequiredSize(searchPkt);
        session->Send(sendBuffer, bufSize);
    }
    
    
}

bool AuctionManager::ApplyItem(PlayerPtr player, auction::S_PutItem& pkt)
{
    return true;
}

bool AuctionManager::PurchaseItem(PlayerPtr player, auction::S_PurchaseItem& pkt)
{
    return true;

}

void AuctionManager::Init(asio::io_context& io_context)
{
    // 전역 매니저 초기화
    GAuctionManager = std::make_shared<AuctionManager>(io_context);
}


