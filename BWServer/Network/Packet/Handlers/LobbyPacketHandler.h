#pragma once
#include "Login.pb.h"

class LobbyPacketHandler
{
public:
	//static bool Handle_C_Login(SessionPtr& session, message::C_Login& pkt);
	static bool Handle_C_Login(SessionPtr& session, account::login::C_Login& pkt);
	
	//static bool Handle_C_Register(SessionPtr& session, account::login::C_Register& pkt);
};

