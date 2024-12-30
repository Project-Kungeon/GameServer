#pragma once
#include "pch.h"
#include "build/Message.pb.h"

class RoomPacketHandler
{
public:
    static bool Handle_S_EnterRoom(SessionPtr& session, message::S_EnterRoom& pkt);
};
