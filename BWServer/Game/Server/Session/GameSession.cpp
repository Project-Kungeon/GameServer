#include "pch.h"
#include "GameSession.h"

void GameSession::OnConnected()
{
}

void GameSession::OnDisConnected()
{
    PacketSession::OnDisConnected();
}


void GameSession::AssignSessionId()
{
    _session_id = boost::uuids::to_string(boost::uuids::random_generator()());
}
