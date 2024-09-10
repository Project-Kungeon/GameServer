#pragma once
#include "Player.h"
class Warrior :
    public Player
{
public:
    Warrior();
    Warrior(float hp, float maxHp, float exp);
    void Init();
    virtual ~Warrior();

public:
    virtual void UseSkillQ();
    virtual void UseSkillE();
    virtual void UseSkillR();
    virtual void UseSkillLS();

    // constant
private:
    const uint32 WARRIOR_Q_COOLTIME = 4000;
    const uint32 WARRIOR_E_COOLTIME = 4000;
    const uint32 WARRIOR_R_COOLTIME = 15000;
    const uint32 WARRIOR_LS_COOLTIME = 5000;

public:
    int stacks = 0;

};

