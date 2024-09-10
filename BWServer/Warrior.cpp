#include "pch.h"
#include "Warrior.h"

Warrior::Warrior()
	: Player()
{
	playerType = message::PLAYER_TYPE_WARRIOR;
	Init();
}

Warrior::Warrior(float hp, float maxHp, float exp)
	: Player(message::PLAYER_TYPE_WARRIOR, hp, maxHp, exp)
{
	Init();
}

void Warrior::Init()
{
	Q_COOLTIME = WARRIOR_Q_COOLTIME;
	E_COOLTIME = WARRIOR_E_COOLTIME;
	R_COOLTIME = WARRIOR_R_COOLTIME;
	LS_COOLTIME = WARRIOR_LS_COOLTIME;
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
