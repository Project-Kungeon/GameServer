#pragma once
#include "pch.h"

class LobbyPacketHandler
{
public:
    static bool Handle_S_Login(SessionPtr& session, account::login::S_Login& pkt);
};