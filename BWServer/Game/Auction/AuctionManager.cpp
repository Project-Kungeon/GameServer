#include "pch.h"
#include "AuctionManager.h"

std::shared_ptr<AuctionManager> GAuctionManager = std::make_shared<AuctionManager>();

AuctionManager::AuctionManager(asio::io_context& io_context)
    : _io_context(io_context)
{
}

AuctionManager::~AuctionManager()
{
}

bool AuctionManager::registerItem(auction::S_PutItem& pkt)
{
    // TODO : 캐릭터가 아이템 소유 중인지 체크
    
    return true;
}

bool AuctionManager::purchaseItem(auction::S_PurchaseItem& pkt)
{
    // 1. 사용자가 테라 소유 중인지 체크

    // 2. Auction Item 처리

    
    
    return true;
}
