#pragma once

class AuctionManager
{
public:
    AuctionManager(asio::io_context& io_context);
    ~AuctionManager();
    
    bool registerItem(auction::S_PutItem& pkt);
    bool purchaseItem(auction::S_PurchaseItem& pkt);
private:
    USE_LOCK;
    // 옥션 아이템마다 strand 지정을 위한 io context 참조
    asio::io_context& _io_context;
    map<uint64, AuctionItemPtr> _AuctionItems;
};

extern std::shared_ptr<AuctionManager> GAuctionManager;