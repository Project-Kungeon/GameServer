#pragma once
#include "Message.pb.h"
#include "Skill.pb.h"
#include "Item.pb.h"
#include "Login.pb.h"
#include "Auction.pb.h"
#include "Ping.pb.h"

// 핸들러 모음
#include "LobbyPacketHandler.h"
#include "RoomPacketHandler.h"
#include "BattlePacketHandler.h"
#include "InteractivePacketHandler.h"
#include "PingPongPacketHandler.h"
#include "CharacterSelectPacketHandler.h"
#include "AuctionPacketHandler.h"
#include "Server/Session/PacketSession.h"

using PacketHandlerFunc = std::function<bool(SessionPtr&, asio::mutable_buffer&, int&)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

using UdpPacketHandlerFunc = std::function<bool(asio::mutable_buffer&, int&)>;
extern UdpPacketHandlerFunc GUdpPacketHandler[UINT16_MAX];

bool Handle_INVALID(SessionPtr& session, asio::mutable_buffer& buffer, int& offset);
bool UdpHandle_INVALID(asio::mutable_buffer& buffer, int& offset);

class ServerPacketHandler
{
public:
	static void Init()
	{
		for (int i = 0; i < UINT16_MAX; i++)
		{
			GPacketHandler[i] = Handle_INVALID;
			GUdpPacketHandler[i] = UdpHandle_INVALID;
		}
		// TCP
		GPacketHandler[message::HEADER::LOGIN_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_Login");
			return ParsePacket<account::login::C_Login>(LobbyPacketHandler::Handle_C_Login, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::ENTER_ROOM_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_EnterRoom");
			return ParsePacket<message::C_EnterRoom>(RoomPacketHandler::Handle_C_EnterRoom, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::CHARACTER_LIST_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_CharacterList");
			return ParsePacket<account::character::select::C_CharacterList>(CharacterSelectPacketHandler::Handle_C_CharacterList, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::CHARACTER_SELECT_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_SelectCharacter");
			return ParsePacket<account::character::select::C_SelectCharacter>(CharacterSelectPacketHandler::Handle_C_SelectCharacter, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::PLAYER_MOVE_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_Move");
			return ParsePacket<message::C_Move>(RoomPacketHandler::Handle_C_Move, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::PLAYER_ATTACK_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_Attack");
			return ParsePacket<message::C_Attack>(BattlePacketHandler::Handle_C_Attack, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::SESSION_PING_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_Ping");
			return ParsePacket<ping::C_Ping>(PingPongPacketHandler::Handle_C_Ping, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::SESSION_COMPLETE_PING_RES] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_CompletePing");
			return ParsePacket<ping::C_CompletePing>(PingPongPacketHandler::Handle_C_CompletePing, session, buffer, offset);
		};

		// Warrior
		GPacketHandler[message::HEADER::WARRIOR_ATTACK_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_Warrior_Attack");
			return ParsePacket<skill::C_Warrior_Attack>(BattlePacketHandler::Handle_C_WarriorAttack, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::WARRIOR_Q_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_Warrior_Q");
			return ParsePacket<skill::C_Warrior_Q>(BattlePacketHandler::Handle_C_WarriorQ, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::WARRIOR_Q_HIT_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_Warrior_Q_Hit");
			return ParsePacket<skill::C_Warrior_Q_Hit>(BattlePacketHandler::Handle_C_WarriorQ_Hit, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::WARRIOR_E_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_Warrior_E");
			return ParsePacket<skill::C_Warrior_E>(BattlePacketHandler::Handle_C_WarriorE, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::WARRIOR_E_SUCCESS_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_Warrior_E_Success");
			return ParsePacket<skill::C_Warrior_E_Success>(BattlePacketHandler::Handle_C_WarriorE_Success, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::WARRIOR_R_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_Warrior_R");
			return ParsePacket<skill::C_Warrior_R>(BattlePacketHandler::Handle_C_WarriorR, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::WARRIOR_LS_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_Warrior_LS");
			return ParsePacket<skill::C_Warrior_LS>(BattlePacketHandler::Handle_C_WarriorLS, session, buffer, offset);
		};

		// Assassin
		GPacketHandler[message::HEADER::ASSASSIN_ATTACK_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_ASSASSIN_Attack");
			return ParsePacket<skill::C_ASSASSIN_Attack>(BattlePacketHandler::Handle_C_AssassinAttack, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::ASSASSIN_Q_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_ASSASSIN_Q");
			return ParsePacket<skill::C_ASSASSIN_Q>(BattlePacketHandler::Handle_C_AssassinQ, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::ASSASSIN_R_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_ASSASSIN_R");
			return ParsePacket<skill::C_ASSASSIN_R>(BattlePacketHandler::Handle_C_AssassinR, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::ASSASSIN_LS_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_ASSASSIN_LS");
			return ParsePacket<skill::C_ASSASSIN_LS>(BattlePacketHandler::Handle_C_AssassinLS, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::ASSASSIN_E_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_Assassin_E");
			return ParsePacket<skill::C_Assassin_E>(BattlePacketHandler::Handle_C_AssassinE, session, buffer, offset);
		};
		
		// Archor
		GPacketHandler[message::HEADER::ARCHOR_ATTACK_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_Archor_Attack");
			return ParsePacket<skill::C_Archor_Attack>(BattlePacketHandler::Handle_C_ArchorAttack, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::ARCHOR_Q_CHARGING_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_Archor_Q_Charging");
			return ParsePacket<skill::C_Archor_Q_Charging>(BattlePacketHandler::Handle_C_ArchorQ_Charging, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::ARCHOR_Q_SHOT_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_Archor_Q_Shot");
			return ParsePacket<skill::C_Archor_Q_Shot>(BattlePacketHandler::Handle_C_ArchorQ_Shot, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::ARCHOR_E_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_Archor_E");
			return ParsePacket<skill::C_Archor_E>(BattlePacketHandler::Handle_C_ArchorE, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::ARCHOR_R_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_Archor_R");
			return ParsePacket<skill::C_Archor_R>(BattlePacketHandler::Handle_C_ArchorR, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::ARCHOR_LS_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_Archor_LS");
			return ParsePacket<skill::C_Archor_LS>(BattlePacketHandler::Handle_C_ArchorLS, session, buffer, offset);
		};

		GPacketHandler[message::HEADER::ITEM_PICKED_UP_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_ItemPickedUp");
			return ParsePacket<game::item::C_Item_PickedUp>(InteractivePacketHandler::Handle_C_Item_PickedUp, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::ITEM_CONSUMEABLE_USED_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_Item_ConsumeableUsed");
			return ParsePacket<game::item::C_Item_ConsumeableUsed>(InteractivePacketHandler::Handle_C_Item_ConsumeableUsed, session, buffer, offset);
		};
		GPacketHandler[message::HEADER::ITEM_OPENINVENTORY] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
			{
				spdlog::trace("Handle C_Item_OpenInventory");
				return ParsePacket<game::item::C_Item_OpenInventory>(InteractivePacketHandler::Handle_C_Item_OpenInventory, session, buffer, offset);
			};
		GPacketHandler[message::HEADER::AUCTION_SEARCH_REQ] = [](SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
		{
			spdlog::trace("Handle C_SearchItem");
			return ParsePacket<auction::C_SearchItem>(AuctionPacketHandler::Handle_C_SearchItem, session, buffer, offset);
		};
	}

	/*static bool HandlePacket(SessionPtr& session, char* ptr, size_t size)
	{
		PacketHeader header;
		asio::mutable_buffer buffer = asio::buffer(ptr, size);
		int offset = 0;
		PacketUtil::ParseHeader(buffer, &header, offset);

		return GPacketHandler[header.Code](session, buffer, offset);
	}*/

	static bool HandlePacket(SessionPtr& session, const PacketHeader& header, char* ptr, size_t size)
	{
		asio::mutable_buffer buffer = asio::buffer(ptr, size);
		int offset = 4;

		return GPacketHandler[header.Code](session, buffer, offset);
	}

	static bool HandleUdpPacket(char* ptr, size_t size)
	{
		PacketHeader header;
		asio::mutable_buffer buffer = asio::buffer(ptr, size);
		int offset = 0;
		PacketUtil::ParseHeader(buffer, &header, offset);

		return GUdpPacketHandler[header.Code](buffer, offset);
	}

private:
	// Will be deprecated
	template<typename PacketType, typename ProcessFunc>
	static bool ParsePacket(ProcessFunc func, SessionPtr& session, asio::mutable_buffer& buffer, int& offset)
	{
		PacketType pkt;
		if (!PacketUtil::Parse(pkt, buffer, buffer.size(), offset))
		{
			return false;
		}

		return func(session, pkt);
	}

	template<typename PacketType, typename ProcessFunc>
	static bool UdpHandlePacket(ProcessFunc func, asio::mutable_buffer& buffer, int& offset)
	{
		PacketType pkt;
		if (!PacketUtil::Parse(pkt, buffer, buffer.size(), offset)) return false;

		return func(pkt);
	}
	
};