#include "pch.h"
#include "BattlePacketHandler.h"

bool BattlePacketHandler::Handle_C_Attack(SessionPtr& session, message::C_Attack& pkt)
{
	// TODO : 결과 반환받고 S_Attack 전송할 예정
	GRoom[0]->HandleAttack(pkt);
	return false;
}
