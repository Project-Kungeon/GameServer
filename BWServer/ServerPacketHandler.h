#pragma once
#include "Message.pb.h"
#include "Packet.h"

// 핸들러 모음
#include "LobbyPacketHandler.h"


using PacketHandlerFunc = std::function<bool(SessionPtr&, asio::mutable_buffer&, int&)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

enum : unsigned int
{
	PKT_C_LOGIN = 1000,
	PKT_S_LOGIN = 1001,
	
};

bool Handle_INVALID(SessionPtr& session, asio::mutable_buffer& buffer, int& offset);

class ServerPacketHandler
{
public:
	static void Init()
	{
		for (int i = 0; i < UINT16_MAX; i++)
			GPacketHandler[i] = Handle_INVALID;

		GPacketHandler[PKT_C_LOGIN] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			return HandlePacket<message::C_Login>(LobbyPacketHandler::Handle_C_Login, session, buffer, offset);
		};

	}

	static bool HandlePacket(SessionPtr& session, char* ptr, size_t size)
	{
		PacketHeader header;
		asio::mutable_buffer buffer = asio::buffer(ptr, size);
		int offset = 0;
		PacketUtil::ParseHeader(buffer, &header, offset);

		return GPacketHandler[header.Code](session, buffer, offset);
	}

private:
	template<typename PacketType, typename ProcessFunc>
	static bool HandlePacket(ProcessFunc func, SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
	{
		PacketType pkt;
		if (!PacketUtil::Parse(pkt, buffer, buffer.size(), offset)) return false;

		return func(session, pkt);
	}
	
};