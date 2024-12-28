#include "ClientPacketHandler.h"
#include "LobbyPacketHandler.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(SessionPtr& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
{
    return false;
}

void ClientPacketHandler::Init()
{
    for (int i = 0; i < UINT16_MAX; i++)
        GPacketHandler[i] = Handle_INVALID;

    GPacketHandler[message::HEADER::LOGIN_RES] = [](SessionPtr& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        return HandlePacket<account::login::S_Login>(LobbyPacketHandler::Handle_S_Login, session, buffer, header, offset);
    };
}
