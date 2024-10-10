#pragma once
#include "Message.pb.h"
class ObjectUtils
{
public:
	static PlayerPtr CreatePlayer(GameSessionPtr session, message::PlayerType type);
	static MonsterPtr CreateMonster(message::MonsterType type);
	static ItemObjectPtr CreateItemObject(message::ItemType itemType, message::ItemTable itemTable);
	static message::ObjectInfo toObjectInfo(ObjectPtr objectPtr);
	static message::CreatureInfo toCreatureInfo(CreaturePtr creaturePtr);
	static message::MonsterInfo toMonsterInfo(MonsterPtr monsterPtr);
	static message::PlayerInfo toPlayerInfo(PlayerPtr playerPtr);
private:
	static std::atomic<unsigned int> s_idGenerator;

	// Cooltime
public:
	static const uint32 WARRIOR_Q_COOLTIME = 3000;
	static const uint32 WARRIOR_E_COOLTIME = 30000;
	static const uint32 WARRIOR_R_COOLTIME = 15000;
	static const uint32 WARRIOR_LS_COOLTIME = 10000;

	static const uint32 ASSASSIN_Q_COOLTIME = 3000;
	static const uint32 ASSASSIN_E_COOLTIME = 1000;
	static const uint32 ASSASSIN_R_COOLTIME = 30000;
	static const uint32 ASSASSIN_LS_COOLTIME = 15000;

	static const uint32 ARCHOR_Q_COOLTIME = 5000;
	static const uint32 ARCHOR_E_COOLTIME = 12000;
	static const uint32 ARCHOR_R_COOLTIME = 20000;
	static const uint32 ARCHOR_LS_COOLTIME = 15000;

	// MaxHp
public:
	static const uint32 WARRIOR_MAX_HP = 100;
	static const uint32 ASSASSIN_MAX_HP = 100;
	static const uint32 ARCHOR_MAX_HP = 80;
};

