#pragma once
class LobbyPacketHandler
{
public:
	static bool Handle_C_Login(SessionPtr& session, message::C_Login& pkt);
};

