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

void Player::UseSkillQ()
{
	skillCoolTime->set_q_cooltime(Q_COOLTIME);
}

void Player::UseSkillE()
{
	skillCoolTime->set_e_cooltime(E_COOLTIME);
}

void Player::UseSkillR()
{
	skillCoolTime->set_r_cooltime(R_COOLTIME);
}

void Player::UseSkillLS()
{
	skillCoolTime->set_ls_cooltime(LS_COOLTIME);
}
