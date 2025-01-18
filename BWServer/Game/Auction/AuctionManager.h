#pragma once
#include "Types.h"

class AuctionManager
{
public:
    AuctionManager(asio::io_context& io_context);
    ~AuctionManager();

    void SearchItem(PlayerPtr player, auction::C_SearchItem& pkt);
    bool ApplyItem(PlayerPtr player, auction::S_PutItem& pkt);
    bool PurchaseItem(PlayerPtr player, auction::S_PurchaseItem& pkt);
    static void Init(asio::io_context& io_context);
    
private:
    // 옥션 아이템마다 strand 지정을 위한 io context 참조
    asio::io_context& _io_context;
    unordered_map<message::ItemTable, AuctionItemPtr> _AuctionItems;
};

extern AuctionManagerPtr GAuctionManager;