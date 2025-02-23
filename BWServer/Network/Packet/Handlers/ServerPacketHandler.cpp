#include "pch.h"
#include "ServerPacketHandler.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];
UdpPacketHandlerFunc GUdpPacketHandler[UINT16_MAX];

bool Handle_INVALID(SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
{
	spdlog::error("Packets not registered with the handler.");
	return false;
}

bool UdpHandle_INVALID(asio::mutable_buffer& buffer, int& offset)
{
	spdlog::error("Packets not registered with the handler.");
	return false;
}
