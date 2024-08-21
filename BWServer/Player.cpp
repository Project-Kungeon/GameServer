#include "pch.h"
#include "Player.h"

Player::Player()
	: Creature()
{
	playerType = message::PLAYER_TYPE_NONE;
	skillCoolTime = new message::SkillCooltime();
}

Player::Player(message::PlayerType playerType, float hp, float maxHp, float exp)
	: Creature(message::CREATURE_TYPE_PLAYER, hp, maxHp, exp)
{
	this->playerType = playerType;
	skillCoolTime = new message::SkillCooltime();
}

Player::~Player()
{
	delete skillCoolTime;
	skillCoolTime = nullptr;
}
