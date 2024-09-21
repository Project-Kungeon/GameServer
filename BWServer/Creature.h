#pragma once
#include "Object.h"

class Creature : public Object
{
public:
	Creature();
	Creature(message::CreatureType creatuerType, float hp, float maxHp, float exp);
	virtual ~Creature();

public:
	virtual void Damaged(CreaturePtr attacker, float damage);
	bool IsDead();

	// Set&Get
public:
	const message::CreatureType GetCreatureType() { return creatureType; }
	const float GetHp() { GetReadLock(); return hp; }
	const float GetMaxHp() { GetReadLock(); return maxHp; }
	const float GetExp() { GetReadLock(); return exp; }

public:
	virtual void Tick(uint32 DeltaTime);
	


private:
	message::CreatureType creatureType;
	float hp;
	float maxHp;
	float exp;

private:
	bool dead = false;

};

