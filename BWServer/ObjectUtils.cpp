#include "pch.h"
#include "ObjectUtils.h"
#include "Assassin.h"
#include "Warrior.h"
#include "Archor.h"
#include "Rampage.h"

atomic<unsigned int> ObjectUtils::s_idGenerator = 1;

PlayerPtr ObjectUtils::CreatePlayer(GameSessionPtr session, message::PlayerType type)
{
	PlayerPtr player = nullptr;
	if (type == message::PLAYER_TYPE_WARRIOR)
	{
		player = std::make_shared<Warrior>();
	}
	else if (type == message::PLAYER_TYPE_ARCHER)
	{
		player = std::make_shared<Archor>();
	}
	else if (type == message::PLAYER_TYPE_ASSASSIN)
	{
		
		player = std::make_shared<Assassin>();
	}
	else
	{
		player = std::make_shared<Player>();
	}

	// Generate ID
	const unsigned int newId = s_idGenerator.fetch_add(1);

	// Generate ObjectInfo
	player->objectInfo->set_object_id(newId);
	player->posInfo->set_object_id(newId);
	
	player->session = session;
	session->player.store(player);

	return player;
}

MonsterPtr ObjectUtils::CreateMonster(message::MonsterType type)
{
	MonsterPtr monster = nullptr;
	if (type == message::MONSTER_TYPE_RAMPAGE)
	{
		monster = std::make_shared<Rampage>();
	}

	// Generate ID
	const unsigned int newId = s_idGenerator.fetch_add(1);

	monster->objectInfo->set_object_id(newId);
	monster->posInfo->set_object_id(newId);


	return monster;
}

message::ObjectInfo ObjectUtils::toObjectInfo(ObjectPtr objectPtr)
{
	message::ObjectInfo objectInfo;
	objectInfo.CopyFrom(*objectPtr->objectInfo);
	return objectInfo;
}

message::CreatureInfo ObjectUtils::toCreatureInfo(CreaturePtr creaturePtr)
{
	message::CreatureInfo creatureInfo;
	message::ObjectInfo* objectInfo = creatureInfo.mutable_object_info();
	objectInfo->CopyFrom(toObjectInfo(static_pointer_cast<Object>(creaturePtr)));
	creatureInfo.set_creature_type(creaturePtr->GetCreatureType());
	creatureInfo.set_hp(creaturePtr->GetHp());
	creatureInfo.set_maxhp(creaturePtr->GetMaxHp());
	creatureInfo.set_exp(creaturePtr->GetExp());

	return creatureInfo;
}



message::PlayerInfo ObjectUtils::toPlayerInfo(PlayerPtr playerPtr)
{
	message::PlayerInfo playerInfo;
	message::CreatureInfo* creatureInfo = playerInfo.mutable_creature_info();
	message::SkillCooltime* skillCooltime = playerInfo.mutable_skill_cooltime();
	
	creatureInfo->CopyFrom(toCreatureInfo(static_pointer_cast<Creature>(playerPtr)));
	skillCooltime->CopyFrom(*playerPtr->GetSkillCooltime());
	playerInfo.set_player_type(playerPtr->GetPlayerType());

	return playerInfo;
}
