#pragma once
#include "pch.h"
#include "Util/Selector.h"

class RampageTree
{
public:
    RampageTree(std::weak_ptr<Rampage> rampage);
    virtual ~RampageTree();

public:
    void Init();
    void MakeRootSelector();
    void MakeFindPlayerSelector();
    void MakeCanAttackSelector();
    void MakeCanNotAttackSelector();
    void Tick(uint32 DeltaTime);

private:
    Selector* RootSelector;
    Selector* FindPlayerSelector;
    Selector* CanAttackSelector;
    Selector* CanNotAttackSelector;

    std::weak_ptr<Rampage> rampage;

    // Timer For Behavior
    uint32 DetectCooldown = 0;
    uint32 RegularPatternCooldown = 0;
    uint32 CloseRanagePatternCooldown = 0;  
    uint32 SkillAttackCooldown = 0;

    int32 WaitCooldown = 0;

    // const
private:
    const uint32 DETECT_COOLTIME = 990;
    const uint32 RP_COOLTIME = 9900;
    const uint32 CR_COOLTIME = 9900;
    const uint32 SKILL_COOLTIME = 9900;

    const uint32 RP_WAIT_TIME = 3970;
    const uint32 CR_WAIT_TIME = 2980;
    const uint32 BA_WAIT_TIME = 1495;
    
};
