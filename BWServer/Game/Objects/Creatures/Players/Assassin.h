#pragma once
#include "Player.h"
class Assassin :
    public Player
{
public:
    Assassin();
    Assassin(float hp, float maxHp, float exp);
    virtual ~Assassin();

public:
    void EnableLS();
    void DisableLS();
    bool IsClokingMode() { return isClocking; };

    virtual void UseSkillQ();
    virtual void UseSkillE();
    virtual void UseSkillR();
    virtual void UseSkillLS();

    // Constant
private:
    const uint32 ASSASSIN_Q_COOLTIME = 3000;
    //const uint32 ARCHOR_E_COOLTIME = 8000;
    const uint32 ASSASSIN_R_COOLTIME = 20000;
    const uint32 ASSASSIN_LS_COOLTIME = 8000;

private:
    bool isClocking = false;
};

