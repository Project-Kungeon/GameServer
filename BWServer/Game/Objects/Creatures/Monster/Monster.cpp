#include "pch.h"
#include "Monster.h"

Monster::Monster()
	: Creature(), dropExp(0)
{
	monsterType = message::MONSTER_TYPE_NONE;
}

Monster::Monster(message::MonsterType monsterType, float hp, float maxHp, float dropExp)
	: Creature(message::CREATURE_TYPE_MONSTER, hp, maxHp, dropExp), monsterType(monsterType), dropExp(dropExp)
{
}

Monster::~Monster()
{
}

void Monster::Tick(uint32 DeltaTime)
{
	Creature::Tick(DeltaTime);
}
