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
    
    std::shared_ptr<MySQLConnection> conn = GConnectionPool->borrow();
    while (conn == nullptr)
    {
        conn = GConnectionPool->borrow();
    }

    
}

void AuctionItem::AsyncApplyed(PlayerPtr player, uint64 price, uint64 quantity)
{
}

void AuctionItem::AsyncRemoved(PlayerPtr player, uint64 applyed_auction_id)
{
}

