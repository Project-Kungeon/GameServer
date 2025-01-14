#pragma once

// 플레이어가 해당 아이템을 경매에 올렸을 때, 개수와 가격, 올린 시각
// 가격, 올린 시각 기준으로 정렬하면 될듯
struct ItemOwnerData
{
    uint64 character_id;
    int64 price;
    int64 quantity;
    uint64 created_at;
    
};

class AuctionItem
{
public:
    AuctionItem();
    AuctionItem(auction::C_PutItem& pkt);
    ~AuctionItem();

public:

private:
    // 아이템 품목
    message::ItemTable item_table;

    // 총 가격 & 개수
    
    
    // 등록한 플레이어, 개수, 가격
    priority_queue<ItemOwnerData> owner_data_pq;
    
    // 동기화 처리
    asio::strand<asio::io_context::executor_type> strand;
};
