#include "ClientPacketHandler.h"
#include "LobbyPacketHandler.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(SessionPtr& session, std::shared_ptr<char[]> ptr, PacketHeader& header, int& offset)
{
    return false;
}

void ClientPacketHandler::Init()
{
    for (int i = 0; i < UINT16_MAX; i++)
        GPacketHandler[i] = Handle_INVALID;

    //GPacketHandler[message::HEADER::LOGIN_RES] = [](SessionPtr& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    //{
    //    return HandlePacket<account::login::S_Login>(LobbyPacketHandler::Handle_S_Login, session, buffer, header, offset);
    //};

    //GPacketHandler[message::HEADER::CHARACTER_LIST_RES] = [](SessionPtr& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    //    {
    //        return HandlePacket<account::character::select::S_CharacterList>(LobbyPacketHandler::Handle_S_CharacterList, session, buffer, header, offset);
    //    };

    //GPacketHandler[message::HEADER::CHARACTER_SELECT_RES] = [](SessionPtr& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    //    {
    //    return Handle_INVALID;
    //};

    GPacketHandler[message::HEADER::LOGIN_RES] = [](SessionPtr& session, std::shared_ptr<char[]> ptr, PacketHeader& header, int& offset)
        {
            return HandlePacket<account::login::S_Login>(LobbyPacketHandler::Handle_S_Login, session, ptr, header, offset);
        };
    GPacketHandler[message::HEADER::CHARACTER_LIST_RES] = [](SessionPtr& session, std::shared_ptr<char[]> ptr, PacketHeader& header, int& offset)
        {
            return HandlePacket<account::character::select::S_CharacterList>(LobbyPacketHandler::Handle_S_CharacterList, session, ptr, header, offset);
        };
    GPacketHandler[message::HEADER::CHARACTER_SELECT_RES] = [](SessionPtr& session, std::shared_ptr<char[]> ptr, PacketHeader& header, int& offset)
        {
            return Handle_INVALID;
        };
    GPacketHandler[message::HEADER::ENTER_ROOM_RES] = [](SessionPtr& session, std::shared_ptr<char[]> ptr, PacketHeader& header, int& offset)
        {
            return Handle_INVALID;
        };
    GPacketHandler[message::HEADER::PLAYER_MOVE_RES] = [](SessionPtr& session, std::shared_ptr<char[]> ptr, PacketHeader& header, int& offset)
        {
            return Handle_INVALID;
        };
}
