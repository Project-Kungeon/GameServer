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

bool BattlePacketHandler::Handle_C_AssassinAttack(SessionPtr& session, skill::C_ASSASSIN_Q& pkt)
{
	return false;
}

bool BattlePacketHandler::Handle_C_AssassinQ(SessionPtr& session, skill::C_ASSASSIN_Q& pkt)
{
	return false;
}

bool BattlePacketHandler::Handle_C_AssassinR(SessionPtr& session, skill::C_ASSASSIN_R& pkt)
{
	return false;
}

bool BattlePacketHandler::Handle_C_AssassinLS(SessionPtr& session, skill::C_ASSASSIN_LS& pkt)
{
	return false;
}
