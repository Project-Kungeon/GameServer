#include "LobbyPacketHandler.h"

#include "Session/Session.h"

bool LobbyPacketHandler::Handle_S_Login(SessionPtr& session, account::login::S_Login& pkt)
{
    if (pkt.is_success())
    {
        account::character::select::C_CharacterList characterListPkt;

        const size_t requiredSize = PacketUtil::RequiredSize(characterListPkt);

        char* rawBuffer = new char[requiredSize];
        auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
        PacketUtil::Serialize(sendBuffer, message::HEADER::CHARACTER_LIST_REQ, characterListPkt);

        session->Send(sendBuffer);
    }
    
    return pkt.is_success();
}
