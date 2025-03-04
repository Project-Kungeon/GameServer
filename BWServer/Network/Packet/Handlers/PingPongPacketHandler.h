#pragma once
#include "Ping.pb.h"

class PingPongPacketHandler
{
public:
	static bool Handle_C_Ping(SessionPtr& session, ping::C_Ping& pkt);
	static bool Handle_C_CompletePing(SessionPtr& session, ping::C_CompletePing& pkt);
};

