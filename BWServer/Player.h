#pragma once
#include "Creature.h"
class Player : public Creature
{
public:
	Player();
	Player(message::PlayerType playerType, float hp, float maxHp, float exp);
	virtual ~Player();

public:
	virtual void UseSkillQ();
	virtual void UseSkillE();
	virtual void UseSkillR();
	virtual void UseSkillLS();

public:
	std::weak_ptr<GameSession> session;

public:
	message::PlayerType playerType;
	message::SkillCooltime* skillCoolTime;

	uint32 Q_COOLTIME = 1000;
	uint32 E_COOLTIME = 1000;
	uint32 R_COOLTIME = 1000;
	uint32 LS_COOLTIME = 1000;
};

