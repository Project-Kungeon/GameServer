#pragma once
#include "MonsterPattern.pb.h"

class Monster : public Creature
{
public:
	Monster();
	Monster(message::MonsterType monsterType, float hp, float maxHp, float dropExp);
	virtual ~Monster();

public:
	virtual void Tick(uint32 DeltaTime);

	message::MonsterType GetMonsterType() { return monsterType; }

private:
	message::MonsterType monsterType;
	float dropExp;
};

