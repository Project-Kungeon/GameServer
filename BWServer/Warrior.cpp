#include "pch.h"
#include "Warrior.h"

Warrior::Warrior()
	: Player(
		message::PLAYER_TYPE_WARRIOR,
		ObjectUtils::WARRIOR_MAX_HP,
		ObjectUtils::WARRIOR_MAX_HP,
		0,
		ObjectUtils::WARRIOR_Q_COOLTIME,
		ObjectUtils::WARRIOR_E_COOLTIME,
		ObjectUtils::WARRIOR_R_COOLTIME,
		ObjectUtils::WARRIOR_LS_COOLTIME)
{
}

Warrior::Warrior(float hp, float maxHp, float exp)
	: Player(
		message::PLAYER_TYPE_WARRIOR,
		hp,
		maxHp,
		exp,
		ObjectUtils::WARRIOR_Q_COOLTIME,
		ObjectUtils::WARRIOR_E_COOLTIME,
		ObjectUtils::WARRIOR_R_COOLTIME,
		ObjectUtils::WARRIOR_LS_COOLTIME)
{
}

Warrior::~Warrior()
{
}

void Warrior::UseSkillQ()
{
	Player::UseSkillQ();
}

void Warrior::UseSkillE()
{
	Player::UseSkillE();
}

void Warrior::UseSkillR()
{
	Player::UseSkillR();
}

void Warrior::UseSkillLS()
{
	Player::UseSkillLS();
}
