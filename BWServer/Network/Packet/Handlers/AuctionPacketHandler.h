#pragma once
#include "Auction.pb.h"

class AuctionPacketHandler
{
public:
    static bool Handle_C_SearchItem(SessionPtr& session, auction::C_SearchItem& pkt);
};
