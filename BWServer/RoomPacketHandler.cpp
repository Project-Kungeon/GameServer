#include "pch.h"
#include "ObjectUtils.h"
#include "Room.h"
#include "RoomPacketHandler.h"

bool RoomPacketHandler::Handle_C_EnterRoom(SessionPtr& session, message::C_EnterRoom& pkt)
{
	// Create Player
	PlayerPtr player = ObjectUtils::CreatePlayer(static_pointer_cast<GameSession>(session));

	// Serialize Response Packet
	GRoom[0]->HandleEnterPlayer(player);

	return false;
}
