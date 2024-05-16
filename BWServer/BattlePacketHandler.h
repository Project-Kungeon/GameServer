#pragma once
class BattlePacketHandler
{
public:
	static bool Handle_C_Attack(SessionPtr& session, message::C_Attack& pkt);

};

