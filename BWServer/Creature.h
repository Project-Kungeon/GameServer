#pragma once
#include "Object.h"

class Creature : public Object
{
public:
	Creature();
	Creature(message::CreatureType creatuerType, float hp, float maxHp, float exp);
	virtual ~Creature();

public:
	message::CreatureType creatureType;
	float hp;
	float maxHp;
	float exp;

};

