#include "pch.h"
#include "AuctionManager.h"

// std::shared_ptr<AuctionManager> GAuctionManager = std::make_shared<AuctionManager>();

AuctionManager::AuctionManager(asio::io_context& io_context)
    : _io_context(io_context), JobQueue(io_context)
{
    Init();
}

AuctionManager::~AuctionManager()
{
}

bool AuctionManager::applyItem(PlayerPtr player, auction::S_PutItem& pkt)
{
}

bool AuctionManager::purchaseItem(PlayerPtr player, auction::S_PurchaseItem& pkt)
{
}

void AuctionManager::Init()
{
    // 경매장 물품 초기화
}
