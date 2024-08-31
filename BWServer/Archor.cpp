#include "pch.h"
#include "Archor.h"

Archor::Archor()
	: Player()
{
	playerType = message::PLAYER_TYPE_ARCHER;
}

Archor::Archor(float hp, float maxHp, float exp)
	: Player(message::PLAYER_TYPE_ARCHER, hp, maxHp, exp)
{
}

void Archor::Init()
{
	Q_COOLTIME = ARCHOR_Q_COOLTIME;
	E_COOLTIME = ARCHOR_E_COOLTIME;
	R_COOLTIME = ARCHOR_R_COOLTIME;
	LS_COOLTIME = ARCHOR_LS_COOLTIME;
}

Archor::~Archor()
{
}

void Archor::EnableR()
{
	R_Time_Remaining = R_DURATION;
	R_Mode = true;
}

void Archor::DisableR()
{
	R_Time_Remaining = 0;
	R_Mode = false;
}

void Archor::EnableLS()
{
	LS_Time_Remaining = LS_DURATION;
	LS_Mode = true;
}

void Archor::DisbleLS()
{
	LS_Time_Remaining = 0;
	LS_Mode = false;
}

void Archor::UseSkillQ()
{
	Player::UseSkillQ();
}

void Archor::UseSkillE()
{
	Player::UseSkillE();
}

void Archor::UseSkillR()
{
	Player::UseSkillR();
	EnableR();
}

void Archor::UseSkillLS()
{
	Player::UseSkillLS();
	EnableLS();
}
