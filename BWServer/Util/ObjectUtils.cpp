#include "pch.h"
#include "Objects/Creatures/Players/Assassin.h"
#include "Objects/Creatures/Players/Warrior.h"
#include "Objects/Creatures/Players/Archor.h"
#include "Objects/Creatures/Monster//Rampage.h"

atomic<unsigned int> ObjectUtils::s_idGenerator = 1;

// TODO : 클래스 타입 외 스탯 정보 등등을 불러와야 함
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

	player->InitInventory();
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
		static_pointer_cast<Rampage>(monster)->Init();
	}

	// Generate ID
	const unsigned int newId = s_idGenerator.fetch_add(1);

	monster->objectInfo->set_object_id(newId);
	monster->posInfo->set_object_id(newId);


	return monster;
}

ItemObjectPtr ObjectUtils::CreateItemObject(message::ItemType itemType, message::ItemTable itemTable)
{
	ItemObjectPtr itemObject = nullptr;
	itemObject = std::make_shared<ItemObject>(itemType, itemTable);

	// Generate ID
	const unsigned int newId = s_idGenerator.fetch_add(1);

	itemObject->objectInfo->set_object_id(newId);
	itemObject->posInfo->set_object_id(newId);

	return itemObject;
}

message::ObjectInfo ObjectUtils::toObjectInfo(ObjectPtr objectPtr)
{
	message::ObjectInfo objectInfo;
	objectInfo.CopyFrom(*objectPtr->objectInfo);
	return objectInfo;
}

message::ItemObjectInfo ObjectUtils::toItemObjectInfo(ItemObjectPtr itemObjectPtr)
{
	message::ItemObjectInfo itemObjectInfo;
	itemObjectInfo.mutable_object_info()->CopyFrom(toObjectInfo(static_pointer_cast<Object>(itemObjectPtr)));
	itemObjectInfo.set_item_type(itemObjectPtr->GetItemType());

	return itemObjectInfo;
}

message::CreatureInfo ObjectUtils::toCreatureInfo(CreaturePtr creaturePtr)
{
	message::CreatureInfo creatureInfo;
	creatureInfo.mutable_object_info()->CopyFrom(toObjectInfo(static_pointer_cast<Object>(creaturePtr)));
	creatureInfo.set_creature_type(creaturePtr->GetCreatureType());
	creatureInfo.set_hp(creaturePtr->GetHp());
	creatureInfo.set_maxhp(creaturePtr->GetMaxHp());
	creatureInfo.set_exp(creaturePtr->GetExp());

	return creatureInfo;
}

message::MonsterInfo ObjectUtils::toMonsterInfo(MonsterPtr monsterPtr)
{
	message::MonsterInfo monsterInfo;
	message::CreatureInfo* creatureInfo = monsterInfo.mutable_creature_info();

	creatureInfo->CopyFrom(toCreatureInfo(static_pointer_cast<Creature>(monsterPtr)));
	monsterInfo.set_monster_type(monsterPtr->GetMonsterType());

	return monsterInfo;
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
