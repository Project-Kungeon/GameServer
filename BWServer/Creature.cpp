#include "pch.h"
#include "Creature.h"

Creature::Creature()
	: Object(message::OBJECT_TYPE_CREATURE)
{
	creatureType = message::CREATURE_TYPE_NONE;
	hp = 0;
	maxHp = 0;
	exp = 0;
}

Creature::Creature(message::CreatureType creatuerType, float hp, float maxHp, float exp)
	: Object(message::OBJECT_TYPE_CREATURE)
{
	this->creatureType = creatuerType;
	this->hp = hp;
	this->maxHp = maxHp;
	this->exp = exp;
}

Creature::~Creature()
{
}
