#pragma once
#include "Monster.h"
class Rampage :
    public Monster
{
public:
    Rampage();
    Rampage(float maxHp, float hp, float dropExp);
    virtual ~Rampage();


    // Set&Get
public:

public:
    virtual void Tick(uint32 DeltaTime);
    bool isAttacking() { GetReadLock(); return isAttacking; }

private:
    bool FindClosePlayer();

private:
    // 가장 가까운 타겟 & 나에게 피해를 많이 입힌 타겟(어그로)
    std::weak_ptr<Creature> CloseTarget;
    std::weak_ptr<Creature> AggroTarget;

    // Attacking Status
    bool isAttacking = false;

    // Timer For Behavior
    uint32 DetectCooldown= 0;
    uint32 BasicAttackCooldown = 0;

    // const
private:
    const uint32 DETECT_COOLTIME = 990;
    const uint32 BA_COOLTIME = 2970;

    const float DETECT_DISTANCE = 20.0;

};

