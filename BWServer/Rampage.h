#pragma once
#include "Monster.h"
#include "RampageTree.h"

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
    void Init();
    virtual void Tick(uint32 DeltaTime) override;
    virtual RampagePtr GetRampagePtr();
    bool isAttack() { GetReadLock(); return isAttacking; }
    void Damaged(CreaturePtr attacker, float damage) override;

public:
    // Detect Function
    bool FindClosePlayer();
    double GetDistanceToTarget(std::weak_ptr<Creature> Target);
    std::weak_ptr<Creature> GetCloseTarget()
    {
        GetReadLock();
        return CloseTarget;
    }
    std::weak_ptr<Creature> GetAggroTarget()
    {
        GetReadLock();
        return AggroTarget;
    }

    // Selector Function
    bool RegularPattern();
    bool UseSkillToAggro();
    bool BasicAttack();
    bool MoveToTarget();
    bool MoveToPos(int rand_x, int rand_y, int rand_z);

    // Pattern Function
    void Roar();
    void EarthQuake();
    void TurnToTarget(std::weak_ptr<Creature> Target);

    // To AggroTarget
    void ThrowAway();
    void EnhancedAttack();

public:
    bool isMoving = false;

private:
    void cleanupExpiredPointers();
    void FindTopDamageDealerToAggro();

private:
    // 가장 가까운 타겟 & 나에게 피해를 많이 입힌 타겟(어그로)
    std::weak_ptr<Creature> CloseTarget;
    std::weak_ptr<Creature> AggroTarget;
    std::shared_ptr<RampageTree> Tree;
    std::unordered_map<uint32, std::pair<std::weak_ptr<Creature>, float>> damageStats;


    // Phase
    short phase = 1;

    // Attacking Status
    bool isAttacking = false;

    
    int32 MovingTime = 0;
    

    const float DETECT_DISTANCE = 1000;

};

