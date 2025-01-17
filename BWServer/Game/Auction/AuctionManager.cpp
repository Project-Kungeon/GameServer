#include "pch.h"
#include "AuctionItem.h"
#include "AuctionManager.h"

// std::shared_ptr<AuctionManager> GAuctionManager = std::make_shared<AuctionManager>();
AuctionManagerPtr GAuctionManager;

AuctionManager::AuctionManager(asio::io_context& io_context)
    : _io_context(io_context), JobQueue(io_context)
{
}

AuctionManager::~AuctionManager()
{
}

bool AuctionManager::applyItem(PlayerPtr player, auction::S_PutItem& pkt)
{
    return true;
}

bool AuctionManager::purchaseItem(PlayerPtr player, auction::S_PurchaseItem& pkt)
{
    return true;

}

void AuctionManager::Init(asio::io_context& io_context)
{
    // 전역 매니저 초기화
    GAuctionManager = std::make_shared<AuctionManager>(io_context);
    GAuctionManager->InitItems();
}

void AuctionManager::InitItems()
{
    // 경매장 물품 초기화
    // TODO : 경매 가능한 물품들 조회 후 초기화. 지금은 테스트 때문에 하나만 초기화한다.
    std::shared_ptr<AuctionItem> item = std::make_shared<AuctionItem>(message::ItemTable::GENERAL_HEALTH_POSION, _io_context);
    _AuctionItems[message::ItemTable::GENERAL_HEALTH_POSION] = item;

    // 일정 주기마다 일감 시작
    MakeTimerUpdate(30);
}

void AuctionManager::AsyncUpdate()
{
    for (auto& item : _AuctionItems)
    {
        item.second->DoAsync(&AuctionItem::AsyncUpdate);
    }
    MakeTimerUpdate(30);
}

void AuctionManager::MakeTimerUpdate(uint64 seconds)
{
    DoTimer(seconds * 1000, &AuctionManager::AsyncUpdate);
}
