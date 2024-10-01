#include "pch.h"
#include "RampageTree.h"
#include "Rampage.h"

RampageTree::RampageTree(std::weak_ptr<Rampage> rampage)
	: rampage(rampage),
	RootSelector(new Selector), FindPlayerSelector(new Selector), CanAttackSelector(new Selector), CanNotAttackSelector(new Selector)
{
}

RampageTree::~RampageTree()
{
	delete RootSelector;
	delete FindPlayerSelector;
	RootSelector = nullptr;
	FindPlayerSelector = nullptr;
}

void RampageTree::Init()
{
	MakeRootSelector();
	MakeFindPlayerSelector();
	MakeCanAttackSelector();
	MakeCanNotAttackSelector();
}

void RampageTree::MakeRootSelector()
{
	RootSelector->addLambda([this]() {
		if (DetectCooldown >= DETECT_COOLTIME)
		{
			DetectCooldown = 0;
			if (auto ptr = rampage.lock())
			{
				if (ptr->FindClosePlayer())
				{
					spdlog::debug("Rampage found Player {}", ptr->GetCloseTarget().lock()->GetObjectId());
					return FindPlayerSelector->execute();
				}
				// 만약 근처 플레이어를 찾지 못 했다면
				else
				{
					// 랜덤한 곳으로 이동하는 코드 TODO
				}
			}
		}
		return false;
		});
}

void RampageTree::MakeFindPlayerSelector()
{
	FindPlayerSelector->addLambda([this]()
		{
			if (RegularPatternCooldown < RP_COOLTIME) return false;
		if (auto ptr = rampage.lock())
		{
			RegularPatternCooldown = 0;
			return ptr->RegularPattern();
		}

	return false;
		});

	FindPlayerSelector->addLambda([this]()
		{
			if (auto ptr = rampage.lock())
			{
				return CanAttackSelector->execute();
			}

			return false;
		});

	FindPlayerSelector->addLambda([this]()
		{
			if (auto ptr = rampage.lock())
			{
				return CanNotAttackSelector->execute();
			}
			return false;
		});
}

void RampageTree::MakeCanAttackSelector()
{
	CanAttackSelector->addLambda([this]()
		{
			// 스킬 사용가능할 때
			if (SkillAttackCooldown >= SKILL_COOLTIME)
			{
				
				if (auto ptr = rampage.lock())
				{
					SkillAttackCooldown = 0;
					ptr->TurnToTarget(ptr->GetAggroTarget());
					if (ptr->UseSkillToAggro())
					{
						SkillAttackCooldown = 0;
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			// 스킬을 사용하지 못하고, 일반공격이 가능할 때
			else if (BasicAttackCooldown >= BA_COOLTIME)
			{
				if (auto ptr = rampage.lock())
				{
					ptr->TurnToTarget(ptr->GetCloseTarget());
					if (ptr->BasicAttack())
					{
						BasicAttackCooldown = 0;
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		});
}

void RampageTree::MakeCanNotAttackSelector()
{
	CanNotAttackSelector->addLambda([this]()
		{
			//if (auto ptr = rampage.lock())
			//{
			//	return ptr->MoveToTarget(ptr->GetCloseTarget());
			//}

			return false;
		});
}

void RampageTree::Tick(uint32 DeltaTime)
{
	if (DetectCooldown < DETECT_COOLTIME) DetectCooldown += DeltaTime;
	if (RegularPatternCooldown < RP_COOLTIME) RegularPatternCooldown += DeltaTime;
	if (SkillAttackCooldown < SKILL_COOLTIME) SkillAttackCooldown += DeltaTime;
	if (BasicAttackCooldown < BA_COOLTIME) BasicAttackCooldown += DeltaTime;
	RootSelector->execute();
}
