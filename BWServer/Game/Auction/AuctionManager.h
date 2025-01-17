#pragma once
#include "Types.h"

class AuctionManager : public JobQueue
{
public:
    AuctionManager(asio::io_context& io_context);
    ~AuctionManager();
    
    bool applyItem(PlayerPtr player, auction::S_PutItem& pkt);
    bool purchaseItem(PlayerPtr player, auction::S_PurchaseItem& pkt);
    static void Init(asio::io_context& io_context);
    
private:
    void InitItems();
    void AsyncUpdate();
    void MakeTimerUpdate(uint64 seconds);
    
private:
    // 옥션 아이템마다 strand 지정을 위한 io context 참조
    asio::io_context& _io_context;
    unordered_map<message::ItemTable, AuctionItemPtr> _AuctionItems;
};

extern AuctionManagerPtr GAuctionManager;