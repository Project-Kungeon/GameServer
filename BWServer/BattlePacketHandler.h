#pragma once
class BattlePacketHandler
{
public:
	static bool Handle_C_Attack(SessionPtr& session, message::C_Attack& pkt);
	static bool Handle_C_WarriorAttack(SessionPtr& session, skill::C_Warrior_Attack& pkt);

	static bool Handle_C_WarriorR(SessionPtr& session, skill::C_Warrior_R& pkt);
	static bool Handle_C_WarriorE(SessionPtr& session, skill::C_Warrior_E& pkt);

	static bool Handle_C_AssassinAttack(SessionPtr& session, skill::C_ASSASSIN_Attack& pkt);
	static bool Handle_C_AssassinQ(SessionPtr& session, skill::C_ASSASSIN_Q& pkt);
	static bool Handle_C_AssassinR(SessionPtr& session, skill::C_ASSASSIN_R& pkt);
	static bool Handle_C_AssassinLS(SessionPtr& session, skill::C_ASSASSIN_LS& pkt);
	static bool Handle_C_AssassinE(SessionPtr& session, skill::C_Assassin_E& pkt);
};

