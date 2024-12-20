#include "pch.h"
#include "PingPongPacketHandler.h"

bool PingPongPacketHandler::Handle_C_Ping(SessionPtr& session, ping::C_Ping& pkt)
{
	session->HandlePing(pkt);
	return true;
}

bool PingPongPacketHandler::Handle_C_CompletePing(SessionPtr& session, ping::C_CompletePing& pkt)
{
	session->HandleCompletePing(pkt);
	return true;
}
