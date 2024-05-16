#pragma once
#include "Creature.h"
class Player : public Creature
{
public:
	Player();
	virtual ~Player();

public:
	message::PlayerInfo* player_info;
	std::weak_ptr<GameSession> session;
};

