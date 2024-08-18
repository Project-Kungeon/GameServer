#pragma once
#include "Message.pb.h"
#include "Skill.pb.h"
#include "Packet.h"

// 핸들러 모음
#include "LobbyPacketHandler.h"
#include "RoomPacketHandler.h"
#include "BattlePacketHandler.h"

using PacketHandlerFunc = std::function<bool(SessionPtr&, asio::mutable_buffer&, int&)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];


bool Handle_INVALID(SessionPtr& session, asio::mutable_buffer& buffer, int& offset);

class ServerPacketHandler
{
public:
	static void Init()
	{
		for (int i = 0; i < UINT16_MAX; i++)
			GPacketHandler[i] = Handle_INVALID;

		GPacketHandler[message::HEADER::LOGIN_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			return HandlePacket<message::C_Login>(LobbyPacketHandler::Handle_C_Login, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::ENTER_ROOM_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			return HandlePacket<message::C_EnterRoom>(RoomPacketHandler::Handle_C_EnterRoom, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::PLAYER_MOVE_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			return HandlePacket<message::C_Move>(RoomPacketHandler::Handle_C_Move, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::PLAYER_ATTACK_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			return HandlePacket<message::C_Attack>(BattlePacketHandler::Handle_C_Attack, session, buffer, offset);
		};

		// Warrior
		GPacketHandler[message::HEADER::WARRIOR_ATTACK_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			return HandlePacket<skill::C_Warrior_Attack>(BattlePacketHandler::Handle_C_WarriorAttack, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::WARRIOR_E_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			return HandlePacket<skill::C_Warrior_E>(BattlePacketHandler::Handle_C_WarriorE, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::WARRIOR_R_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			return HandlePacket<skill::C_Warrior_R>(BattlePacketHandler::Handle_C_WarriorR, session, buffer, offset);
		};

		// Assassin
		GPacketHandler[message::HEADER::ASSASSIN_ATTACK_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			return HandlePacket<skill::C_ASSASSIN_Attack>(BattlePacketHandler::Handle_C_AssassinAttack, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::ASSASSIN_Q_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			return HandlePacket<skill::C_ASSASSIN_Q>(BattlePacketHandler::Handle_C_AssassinQ, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::ASSASSIN_R_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			return HandlePacket<skill::C_ASSASSIN_R>(BattlePacketHandler::Handle_C_AssassinR, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::ASSASSIN_LS_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			return HandlePacket<skill::C_ASSASSIN_LS>(BattlePacketHandler::Handle_C_AssassinLS, session, buffer, offset);
		};
		

	}

	static bool HandlePacket(SessionPtr& session, char* ptr, size_t size)
	{
		PacketHeader header;
		asio::mutable_buffer buffer = asio::buffer(ptr, size);
		int offset = 0;
		PacketUtil::ParseHeader(buffer, &header, offset);

		return GPacketHandler[header.Code](session, buffer, offset);
	}

private:
	template<typename PacketType, typename ProcessFunc>
	static bool HandlePacket(ProcessFunc func, SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
	{
		PacketType pkt;
		if (!PacketUtil::Parse(pkt, buffer, buffer.size() - offset, offset)) return false;

		return func(session, pkt);
	}
	
};