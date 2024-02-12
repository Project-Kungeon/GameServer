#include "pch.h"
#include "ServerPacketHandler.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
{
	return false;
}
