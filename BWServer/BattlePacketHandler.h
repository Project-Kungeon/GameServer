#pragma once
class BattlePacketHandler
{
public:
	static bool Handle_C_Attack(SessionPtr& session, message::C_Attack& pkt);
	static bool Handle_C_WarriorAttack(SessionPtr& session, skill::C_Warrior_Attack& pkt);

	static bool Handle_C_WarriorR(SessionPtr& session, skill::C_Warrior_R& pkt);
	static bool Handle_C_WarriorE(SessionPtr& session, skill::C_Warrior_E& pkt);
};

