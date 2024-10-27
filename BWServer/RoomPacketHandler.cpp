#include "pch.h"
#include "ObjectUtils.h"
#include "Room.h"
#include "RoomPacketHandler.h"

bool RoomPacketHandler::UdpHandle_C_Move(message::C_Move& pkt)
{
	// UDP TEST
	GRoom[0]->DoAsync(&Room::UdpHandleMove, pkt);

	return true;
}

bool RoomPacketHandler::Handle_C_EnterRoom(SessionPtr& session, message::C_EnterRoom& pkt)
{
	// Create Player
	PlayerPtr player = ObjectUtils::CreatePlayer(static_pointer_cast<GameSession>(session), pkt.player_type());
	// Serialize Response Packet
	GRoom[0]->DoAsync(&Room::HandleEnterPlayer, (player));
	static_pointer_cast<GameSession>(session)->isEnterGame = true;

	return true;
}

bool RoomPacketHandler::Handle_C_Move(SessionPtr& session, message::C_Move& pkt)
{
	// cast into GameSession (for getting object info)
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);

	// 플레이어 정보가 들어오지 않았다면 일단 패스
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player
	PlayerPtr weak_player = gameSession->player.load();
	if (auto player = weak_player)  // weak_ptr.lock()은 shared_ptr을 반환
	{
		auto room_weak_ptr = player->room.load();
		if (auto room = room_weak_ptr.lock()) {
			// noti this player's moveinfo for all clients
			room->DoAsync(&Room::HandleMove, pkt);
			return true;
		}

	}
	return false;
}
