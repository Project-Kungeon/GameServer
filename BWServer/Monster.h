#pragma once
class Monster : public Creature
{
public:
	Monster();
	Monster(message::MonsterType monsterType, float hp, float maxHp, float dropExp);
	virtual ~Monster();

public:
	virtual void Tick(uint32 DeltaTime);

private:
	message::MonsterType monsterType;
	float dropExp;
};

