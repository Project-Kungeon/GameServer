#pragma once
class RoomPacketHandler
{
public:
	static bool UdpHandle_C_Move(message::C_Move& pkt);
	static bool Handle_C_EnterRoom(SessionPtr& session, message::C_EnterRoom& pkt);
	static bool Handle_C_Move(SessionPtr& session, message::C_Move& pkt);
};

