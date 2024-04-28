#include "pch.h"
#include "ObjectUtils.h"
#include "Room.h"
#include "RoomPacketHandler.h"

bool RoomPacketHandler::Handle_C_EnterRoom(SessionPtr& session, message::C_EnterRoom& pkt)
{
	// Create Player
	PlayerPtr player = ObjectUtils::CreatePlayer(static_pointer_cast<GameSession>(session));

	// Serialize Response Packet
	bool success = GRoom[0]->HandleEnterPlayer(player);
	if (success == true)
	{
		static_pointer_cast<GameSession>(session)->isEnterGame = true;
	}

	return true;
}

bool RoomPacketHandler::Handle_C_Move(SessionPtr& session, message::C_Move& pkt)
{
	// cast into GameSession ( for getting object info)
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);

	// 플레이어 정보가 들어오지 않았다면 일단 패스
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player 
	PlayerPtr player = gameSession->player.load(memory_order_acquire);
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if(room == nullptr) return false;

	// noti this player's moveinfo for all clients 
	room->HandleMove(pkt);
	

	return true;
}
