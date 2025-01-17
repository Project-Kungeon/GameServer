#pragma once

// 플레이어가 해당 아이템을 경매에 올렸을 때, 개수와 가격, 올린 시각
// 가격, 올린 시각 기준으로 정렬하면 될듯
struct ItemOwnerData
{
    uint64 auction_id;
    uint64 user_id;
    int64 price;
    int64 quantity;
    uint64 created_at;
    bool sold_out;
    
};

struct CompareAuctionItem
{
    bool operator()(const ItemOwnerData& lhs, const ItemOwnerData& rhs) const
    {
        if (lhs.price < rhs.price)
            return true;
        if (lhs.price == rhs.price)
            return lhs.created_at < rhs.created_at;
    }
};

class AuctionItem : public JobQueue
{
public:
    AuctionItem(message::ItemTable item_table, asio::io_context& io_context);
    virtual ~AuctionItem();

    
    
public:
    // Strand 큐에 적재할 메소드
    void AsyncPurchased(PlayerPtr player, uint64 price, uint64 quantity);
    void AsyncApplyed(PlayerPtr player, uint64 price, uint64 quantity);
    void AsyncRemoved(PlayerPtr player, uint64 applyed_auction_id);

public:
    void AsyncUpdate();

private:
    // 아이템 품목
    message::ItemTable item_table;
    
    // 등록한 플레이어, 개수, 가격
    priority_queue<ItemOwnerData, vector<ItemOwnerData>, CompareAuctionItem> owner_data_pq;
};
