#pragma once
#include "Creature.h"
class Player : public Creature
{
public:
	Player();
	virtual ~Player();

public:
	std::weak_ptr<GameSession> session;
};

