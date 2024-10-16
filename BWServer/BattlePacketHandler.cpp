#include "pch.h"
#include "BattlePacketHandler.h"

bool BattlePacketHandler::Handle_C_Attack(SessionPtr& session, message::C_Attack& pkt)
{
	// TODO : 결과 반환받고 S_Attack 전송할 예정
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player 
	PlayerPtr player = gameSession->player.load();
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if (room == nullptr) return false;

	room->DoAsync(&Room::HandleAttack, pkt);
	return true;
}

bool BattlePacketHandler::Handle_C_WarriorAttack(SessionPtr& session, skill::C_Warrior_Attack& pkt)
{
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player 
	PlayerPtr player = gameSession->player.load();
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if (room == nullptr) return false;

	room->DoAsync(&Room::HandleWarriorAttack, pkt);
	return true;
}

bool BattlePacketHandler::Handle_C_WarriorQ(SessionPtr& session, skill::C_Warrior_Q& pkt)
{
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player 
	PlayerPtr player = gameSession->player.load();
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if (room == nullptr) return false;

	room->DoAsync(&Room::HandleWarriorQ, pkt);
	return true;
}

bool BattlePacketHandler::Handle_C_WarriorQ_Hit(SessionPtr& session, skill::C_Warrior_Q_Hit& pkt)
{
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player 
	PlayerPtr player = gameSession->player.load();
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if (room == nullptr) return false;

	room->DoAsync(&Room::HandleWarriorQ_Hit, pkt);
	return true;
}

bool BattlePacketHandler::Handle_C_WarriorR(SessionPtr& session, skill::C_Warrior_R& pkt)
{
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player 
	PlayerPtr player = gameSession->player.load();
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if (room == nullptr) return false;

	room->DoAsync(&Room::HandleWarriorR, pkt);
	return true;
}

bool BattlePacketHandler::Handle_C_WarriorE(SessionPtr& session, skill::C_Warrior_E& pkt)
{
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player 
	PlayerPtr player = gameSession->player.load();
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if (room == nullptr) return false;

	room->DoAsync(&Room::HandleWarriorE, pkt);
	return true;
}

bool BattlePacketHandler::Handle_C_WarriorE_Success(SessionPtr& session, skill::C_Warrior_E_Success& pkt)
{
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player 
	PlayerPtr player = gameSession->player.load();
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if (room == nullptr) return false;

	room->DoAsync(&Room::HandleWarriorE_Success, pkt);
	return true;
}

bool BattlePacketHandler::Handle_C_WarriorLS(SessionPtr& session, skill::C_Warrior_LS& pkt)
{
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player 
	PlayerPtr player = gameSession->player.load();
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if (room == nullptr) return false;

	room->DoAsync(&Room::HandleWarriorLS, pkt);

	return true;
}

bool BattlePacketHandler::Handle_C_AssassinAttack(SessionPtr& session, skill::C_ASSASSIN_Attack& pkt)
{
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player 
	PlayerPtr player = gameSession->player.load();
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if (room == nullptr) return false;

	room->DoAsync(&Room::HandleAssassinAttack, pkt);
	return true;
}

bool BattlePacketHandler::Handle_C_AssassinQ(SessionPtr& session, skill::C_ASSASSIN_Q& pkt)
{
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player 
	PlayerPtr player = gameSession->player.load();
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if (room == nullptr) return false;

	room->DoAsync(&Room::HandleAssassinQ, pkt);
	return true;
}

bool BattlePacketHandler::Handle_C_AssassinR(SessionPtr& session, skill::C_ASSASSIN_R& pkt)
{
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player 
	PlayerPtr player = gameSession->player.load();
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if (room == nullptr) return false;
	
	room->DoAsync(&Room::HandleAssassinR, pkt);
	return true;
}

bool BattlePacketHandler::Handle_C_AssassinLS(SessionPtr& session, skill::C_ASSASSIN_LS& pkt)
{
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player 
	PlayerPtr player = gameSession->player.load();
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if (room == nullptr) return false;

	room->DoAsync(&Room::HandleAssassinLS, pkt);
	return true;
}

bool BattlePacketHandler::Handle_C_AssassinE(SessionPtr& session, skill::C_Assassin_E& pkt)
{
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player 
	PlayerPtr player = gameSession->player.load();
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if (room == nullptr) return false;

	room->DoAsync(&Room::HandleAssassinE, pkt);
	return true;
}

bool BattlePacketHandler::Handle_C_ArchorAttack(SessionPtr& session, skill::C_Archor_Attack& pkt)
{
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player 
	PlayerPtr player = gameSession->player.load();
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if (room == nullptr) return false;

	room->DoAsync(&Room::HandleArchorAttack, pkt);

	return true;
}

bool BattlePacketHandler::Handle_C_ArchorQ_Charging(SessionPtr& session, skill::C_Archor_Q_Charging& pkt)
{
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player 
	PlayerPtr player = gameSession->player.load();
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if (room == nullptr) return false;

	room->DoAsync(&Room::HandleArchorQ_Charging, pkt);

	return true;
}

bool BattlePacketHandler::Handle_C_ArchorQ_Shot(SessionPtr& session, skill::C_Archor_Q_Shot& pkt)
{
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player 
	PlayerPtr player = gameSession->player.load();
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if (room == nullptr) return false;

	room->DoAsync(&Room::HandleArchorQ_Shot, pkt);

	return true;
}

bool BattlePacketHandler::Handle_C_ArchorE(SessionPtr& session, skill::C_Archor_E& pkt)
{
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player 
	PlayerPtr player = gameSession->player.load();
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if (room == nullptr) return false;

	room->DoAsync(&Room::HandleArchorE, pkt);

	return true;
}

bool BattlePacketHandler::Handle_C_ArchorR(SessionPtr& session, skill::C_Archor_R& pkt)
{
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player 
	PlayerPtr player = gameSession->player.load();
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if (room == nullptr) return false;

	room->DoAsync(&Room::HandleArchorR, pkt);

	return true;
}

bool BattlePacketHandler::Handle_C_ArchorLS(SessionPtr& session, skill::C_Archor_LS& pkt)
{
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	if (!gameSession->isEnterGame) return false;

	// if is not lock.. get player 
	PlayerPtr player = gameSession->player.load();
	if (player == nullptr) return false;

	RoomPtr room = player->room.load().lock();
	if (room == nullptr) return false;

	room->DoAsync(&Room::HandleArchorLS, pkt);

	return true;
}
