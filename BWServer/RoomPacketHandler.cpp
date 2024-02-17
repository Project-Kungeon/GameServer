#include "pch.h"
#include "RoomPacketHandler.h"

bool RoomPacketHandler::Handle_C_EnterRoom(SessionPtr& session, message::C_EnterRoom& pkt)
{
	// Deserialize Request Packet
	int idx = pkt.playerindex();

	// Serialize Response Packet

	return false;
}
