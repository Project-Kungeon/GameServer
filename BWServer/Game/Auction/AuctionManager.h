#pragma once

class AuctionManager : public JobQueue
{
public:
    AuctionManager(asio::io_context& io_context);
    ~AuctionManager();
    
    bool applyItem(PlayerPtr player, auction::S_PutItem& pkt);
    bool purchaseItem(PlayerPtr player, auction::S_PurchaseItem& pkt);

private:
    void Init();
    
private:
    // 옥션 아이템마다 strand 지정을 위한 io context 참조
    asio::io_context& _io_context;
    map<uint64, AuctionItemPtr> _AuctionItems;
};