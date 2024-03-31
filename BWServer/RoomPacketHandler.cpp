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

	return true;
}

bool RoomPacketHandler::Handle_C_Move(SessionPtr& session, message::C_Move& pkt)
{
	// cast into GameSession ( for getting object info)
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);

	// if is not lock.. get player
	PlayerPtr player = gameSession->player.load();
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if(room == nullptr) return false;

	// noti this player's moveinfo for all clients 
	room->HandleMove(pkt);
	

	return false;
}
