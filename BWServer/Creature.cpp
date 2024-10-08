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

void Creature::Damaged(CreaturePtr attacker, float damage)
{
	GetWriteLock();
	spdlog::info("{} attacks {}", attacker->GetObjectId(), this->GetObjectId());
	this->hp -= damage;

	if (IsDead())
	{
		RoomPtr roomptr = room.load().lock();
		roomptr->HandleDeath(static_pointer_cast<Creature>(shared_from_this()));
	}
}

bool Creature::IsDead()
{

	if (!dead && hp <= 0)
	{
		dead = true;
		spdlog::info("{} is dead..", this->GetObjectId());
		return true;
	}
	
	return false;
}

void Creature::Tick(uint32 DeltaTime)
{
	Object::Tick(DeltaTime);
}
