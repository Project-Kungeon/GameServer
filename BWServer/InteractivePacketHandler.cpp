#include "pch.h"
#include "InteractivePacketHandler.h"

bool InteractivePacketHandler::Handle_C_Item_PickedUp(SessionPtr& session, game::item::C_Item_PickedUp& pkt)
{
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player 
	PlayerPtr player = gameSession->player.load();
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if (room == nullptr) return false;

	room->DoAsync(&Room::HandleItemPickedUp, player, pkt);
	return true;
}

bool InteractivePacketHandler::Handle_C_Item_ConsumeableUsed(SessionPtr& session, game::item::C_Item_ConsumeableUsed& pkt)
{
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player 
	PlayerPtr player = gameSession->player.load();
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if (room == nullptr) return false;

	room->DoAsync(&Room::HandleItemConsumeableUsed, player, pkt);
	return true;
}
