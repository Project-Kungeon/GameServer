#pragma once
#include "Player.h"
class Archor :
    public Player
{
public:
    Archor();
    Archor(float hp, float maxHp, float exp);
    virtual ~Archor();
    virtual void Tick(uint32 DeltaTime);

public:
    void EnableR();
    void DisableR();

    void EnableLS();
    void DisbleLS();

    virtual void UseSkillQ();
    virtual void UseSkillE();
    virtual void UseSkillR();
    virtual void UseSkillLS();

public:
    uint32 R_Time_Remaining = 0;
    bool R_Mode = false;

    uint32 LS_Time_Remaining = 0;
    bool LS_Mode = false;

private:
    const uint32 R_DURATION = 2000;
    const uint32 LS_DURATION = 6000;

    

};

