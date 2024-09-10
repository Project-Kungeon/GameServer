#include "pch.h"
#include "Assassin.h"

Assassin::Assassin()
	: Player()
{
	playerType = message::PLAYER_TYPE_ASSASSIN;
	Init();
}

Assassin::Assassin(float hp, float maxHp, float exp)
	: Player(message::PLAYER_TYPE_ASSASSIN, hp, maxHp, exp)
{
}

void Assassin::Init()
{
	Init();
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
