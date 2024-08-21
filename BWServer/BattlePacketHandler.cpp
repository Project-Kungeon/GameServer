#include "pch.h"
#include "BattlePacketHandler.h"

bool BattlePacketHandler::Handle_C_Attack(SessionPtr& session, message::C_Attack& pkt)
{
	// TODO : 결과 반환받고 S_Attack 전송할 예정
	GRoom[0]->HandleAttack(pkt);
	return true;
}

bool BattlePacketHandler::Handle_C_WarriorAttack(SessionPtr& session, skill::C_Warrior_Attack& pkt)
{
	GRoom[0]->HandleWarriorAttack(pkt);
	return true;
}

bool BattlePacketHandler::Handle_C_WarriorR(SessionPtr& session, skill::C_Warrior_R& pkt)
{
	GRoom[0]->HandleWarriorR(pkt);
	return true;
}

bool BattlePacketHandler::Handle_C_WarriorE(SessionPtr& session, skill::C_Warrior_E& pkt)
{
	GRoom[0]->HandleWarriorE(pkt);
	return true;
}

bool BattlePacketHandler::Handle_C_AssassinAttack(SessionPtr& session, skill::C_ASSASSIN_Attack& pkt)
{
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player 
	PlayerPtr player = gameSession->player.load(memory_order_acquire);
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if (room == nullptr) return false;

	room->HandleAssassinAttack(pkt);
	return true;
}

bool BattlePacketHandler::Handle_C_AssassinQ(SessionPtr& session, skill::C_ASSASSIN_Q& pkt)
{
	GRoom[0]->HandleAssassinQ(pkt);
	return true;
}

bool BattlePacketHandler::Handle_C_AssassinR(SessionPtr& session, skill::C_ASSASSIN_R& pkt)
{
	GRoom[0]->HandleAssassinR(pkt);
	return true;
}

bool BattlePacketHandler::Handle_C_AssassinLS(SessionPtr& session, skill::C_ASSASSIN_LS& pkt)
{
	GRoom[0]->HandleAssassinLS(pkt);
	return true;
}

bool BattlePacketHandler::Handle_C_AssassinE(SessionPtr& session, skill::C_Assassin_E& pkt)
{
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player 
	PlayerPtr player = gameSession->player.load(memory_order_acquire);
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if (room == nullptr) return false;

	room->HandleAssassinE(pkt);
	return true;
}
