#include "pch.h"
#include "Assassin.h"

Assassin::Assassin()
	: Player(
		message::PLAYER_TYPE_ASSASSIN,
		ObjectUtils::ASSASSIN_MAX_HP,
		ObjectUtils::ASSASSIN_MAX_HP,
		0,
		ObjectUtils::ASSASSIN_Q_COOLTIME,
		ObjectUtils::ASSASSIN_E_COOLTIME,
		ObjectUtils::ASSASSIN_R_COOLTIME,
		ObjectUtils::ASSASSIN_LS_COOLTIME)
{
}

Assassin::Assassin(float hp, float maxHp, float exp)
	: Player(
		message::PLAYER_TYPE_ASSASSIN,
		hp,
		maxHp,
		exp,
		ObjectUtils::ASSASSIN_Q_COOLTIME,
		ObjectUtils::ASSASSIN_E_COOLTIME,
		ObjectUtils::ASSASSIN_R_COOLTIME,
		ObjectUtils::ASSASSIN_LS_COOLTIME)
{
}

Assassin::~Assassin()
{
}

void Assassin::EnableLS()
{
	isClocking = true;
}

void Assassin::DisableLS()
{
	isClocking = false;
}

void Assassin::UseSkillQ()
{
	Player::UseSkillQ();
}

void Assassin::UseSkillE()
{
	Player::UseSkillE();
}

void Assassin::UseSkillR()
{
	Player::UseSkillR();
}

void Assassin::UseSkillLS()
{
	Player::UseSkillLS();
	EnableLS();
}
