#pragma once
class BattlePacketHandler
{
public:
	static bool Handle_C_Attack(SessionPtr& session, message::C_Attack& pkt);
	static bool Handle_C_WarriorAttack(SessionPtr& session, skill::C_Warrior_Attack& pkt);
	
	static bool Handle_C_WarriorQ(SessionPtr& session, skill::C_Warrior_Q& pkt);
	static bool Handle_C_WarriorQ_Hit(SessionPtr& session, skill::C_Warrior_Q_Hit& pkt);

	static bool Handle_C_WarriorR(SessionPtr& session, skill::C_Warrior_R& pkt);
	static bool Handle_C_WarriorE(SessionPtr& session, skill::C_Warrior_E& pkt);
	static bool Handle_C_WarriorE_Success(SessionPtr& session, skill::C_Warrior_E_Success& pkt);
	static bool Handle_C_WarriorLS(SessionPtr& session, skill::C_Warrior_LS& pkt);
	

	static bool Handle_C_AssassinAttack(SessionPtr& session, skill::C_ASSASSIN_Attack& pkt);
	static bool Handle_C_AssassinQ(SessionPtr& session, skill::C_ASSASSIN_Q& pkt);
	static bool Handle_C_AssassinR(SessionPtr& session, skill::C_ASSASSIN_R& pkt);
	static bool Handle_C_AssassinLS(SessionPtr& session, skill::C_ASSASSIN_LS& pkt);
	static bool Handle_C_AssassinE(SessionPtr& session, skill::C_Assassin_E& pkt);

	static bool Handle_C_ArchorAttack(SessionPtr& session, skill::C_Archor_Attack& pkt);
	static bool Handle_C_ArchorQ_Charging(SessionPtr& session, skill::C_Archor_Q_Charging& pkt);
	static bool Handle_C_ArchorQ_Shot(SessionPtr& session, skill::C_Archor_Q_Shot& pkt);
	static bool Handle_C_ArchorE(SessionPtr& session, skill::C_Archor_E& pkt);
	static bool Handle_C_ArchorR(SessionPtr& session, skill::C_Archor_R& pkt);
	static bool Handle_C_ArchorLS(SessionPtr& session, skill::C_Archor_LS& pkt);
};

