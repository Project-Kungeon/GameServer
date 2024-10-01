#pragma once
#include "pch.h"
#include "Selector.h"

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
    uint32 SkillAttackCooldown = 0;
    uint32 BasicAttackCooldown = 0;

    // const
private:
    const uint32 DETECT_COOLTIME = 990;
    const uint32 RP_COOLTIME = 3970;
    const uint32 SKILL_COOLTIME = 4960;
    const uint32 BA_COOLTIME = 1450;
};
