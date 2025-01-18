#include "pch.h"
#include "AuctionPacketHandler.h"

#include "Auction/AuctionManager.h"

bool AuctionPacketHandler::Handle_C_SearchItem(SessionPtr& session, auction::C_SearchItem& pkt)
{
    auto game_session = static_pointer_cast<GameSession>(session);
    GAuctionManager->SearchItem(game_session->player.load(), pkt);

    return true;
}
