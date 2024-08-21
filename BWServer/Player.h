#pragma once
#include "Creature.h"
class Player : public Creature
{
public:
	Player();
	Player(message::PlayerType playerType, float hp, float maxHp, float exp);
	virtual ~Player();

public:
	std::weak_ptr<GameSession> session;

public:
	message::PlayerType playerType;
	message::SkillCooltime* skillCoolTime;
};

