#include "pch.h"
#include "Assassin.h"

Assassin::Assassin()
	: Player()
{
	playerType = message::PLAYER_TYPE_ASSASSIN;
}

Assassin::Assassin(float hp, float maxHp, float exp)
	: Player(message::PLAYER_TYPE_ASSASSIN, hp, maxHp, exp)
{
}

Assassin::~Assassin()
{
}
