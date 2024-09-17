#include "pch.h"
#include "Player.h"

Player::Player()
	: Creature(),
	playerType(message::PLAYER_TYPE_NONE),
	Q_COOLTIME(1000),
	E_COOLTIME(1000),
	R_COOLTIME(1000),
	LS_COOLTIME(1000),
	skillCoolTime(new message::SkillCooltime())
{
}

Player::Player(
	message::PlayerType playerType,
	float hp,
	float maxHp,
	float exp,
	const uint32 Q_COOLTIME,
	const uint32 E_COOLTIME,
	const uint32 R_COOLTIME,
	const uint32 LS_COOLTIME)
	: Creature(message::CREATURE_TYPE_PLAYER, hp, maxHp, exp),
	playerType(playerType),
	Q_COOLTIME(Q_COOLTIME),
	E_COOLTIME(E_COOLTIME),
	R_COOLTIME(R_COOLTIME),
	LS_COOLTIME(LS_COOLTIME),
	skillCoolTime(new message::SkillCooltime())
{
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

void Player::SetQ_Cooltime(uint32 cooltime)
{
	GetWriteLock();
	skillCoolTime->set_q_cooltime(cooltime);
}

void Player::SetE_Cooltime(uint32 cooltime)
{
	GetWriteLock();
	skillCoolTime->set_e_cooltime(cooltime);
}

void Player::SetR_Cooltime(uint32 cooltime)
{
	GetWriteLock();
	skillCoolTime->set_r_cooltime(cooltime);
}

void Player::SetLS_Cooltime(uint32 cooltime)
{
	GetWriteLock();
	skillCoolTime->set_ls_cooltime(cooltime);
}
