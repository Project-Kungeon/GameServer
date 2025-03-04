#include "RoomPacketHandler.h"

#include "build/Auction.pb.h"
#include "Session/Session.h"

bool RoomPacketHandler::Handle_S_EnterRoom(SessionPtr& session, message::S_EnterRoom& pkt)
{ 
    /*auction::C_SearchItem search_item;
    std::string utf8_str = u8"일반";
    search_item.set_item_name(utf8_str);
    search_item.set_page(1);

    auto str = search_item.item_name();
    
    const size_t requiredSize = PacketUtil::RequiredSize(search_item);
    char* rawBuffer = new char[requiredSize];
    auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
    PacketUtil::Serialize(sendBuffer, message::HEADER::AUCTION_SEARCH_REQ, search_item);
    session->Send(sendBuffer);*/
    
    return true;
}
