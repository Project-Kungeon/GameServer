#pragma once
#include "Object.h"

class Creature : public Object
{
public:
	Creature();
	Creature(message::CreatureType creatuerType, float hp, float maxHp, float exp);
	virtual ~Creature();

public:
	void Damaged(CreaturePtr attacker, float damage);
	bool IsDead();

	// Set&Get
public:
	float GetHp() { return hp; }
	float GetMaxHp() { return maxHp; }
	


public:
	message::CreatureType creatureType;
	float hp;
	float maxHp;
	float exp;

private:
	bool dead = false;

};

