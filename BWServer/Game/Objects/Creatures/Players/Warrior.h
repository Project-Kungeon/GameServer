#pragma once
#include "Player.h"
class Warrior :
    public Player
{
public:
    Warrior();
    Warrior(float hp, float maxHp, float exp);
    virtual ~Warrior();

public:
    virtual void UseSkillQ();
    virtual void UseSkillE();
    virtual void UseSkillR();
    virtual void UseSkillLS();

public:
    void IncrParryCount();
    float GetParryCount();
    float GetQ_DamageByParryCount();

    // constant
private:
    const uint32 WARRIOR_Q_COOLTIME = 4000;
    const uint32 WARRIOR_E_COOLTIME = 4000;
    const uint32 WARRIOR_R_COOLTIME = 15000;
    const uint32 WARRIOR_LS_COOLTIME = 5000;

private:
    int parry_count = 0;

    const int MAX_PARRY_COUNT = 5;

};

