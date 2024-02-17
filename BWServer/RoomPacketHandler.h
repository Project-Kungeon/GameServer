#pragma once
class RoomPacketHandler
{
public:
	static bool Handle_C_EnterRoom(SessionPtr& session, message::C_EnterRoom& pkt);
};

