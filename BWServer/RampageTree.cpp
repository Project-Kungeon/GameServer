#include "pch.h"
#include "RampageTree.h"
#include "Rampage.h"
#include "RandomUtil.h"

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
	// 플레이어 찾기
	RootSelector->addLambda([this]() {
		if (DetectCooldown >= DETECT_COOLTIME)
		{
			DetectCooldown = 0;
			if (auto ptr = rampage.lock())
			{
				if (ptr->IsDead()) return false;
				if (ptr->FindClosePlayer())
				{
					spdlog::trace("Rampage found Player {}", ptr->GetCloseTarget().lock()->GetObjectId());

					bool result = FindPlayerSelector->execute();

					return result;
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

	// 못 찾았다면.. 랜덤 움직이기
	RootSelector->addLambda([this]() {
		if (auto ptr = rampage.lock())
		{
			if (ptr->IsDead()) return false;
			WaitCooldown = 3000;
			spdlog::trace("Rampage didnt find Player... Find Random Pos");
			int rand_x = RandomUtil::GetRandom(-250.0f, 250.0f);
			int rand_y = RandomUtil::GetRandom(-250.0f, 250.0f);
			int rand_z = RandomUtil::GetRandom(-250.0f, 250.0f);
			ptr->MoveToPos(rand_x, rand_y, rand_z);
			return true;
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
				if (ptr->IsDead()) return false;
				RegularPatternCooldown = 0;
				bool result = ptr->RegularPattern();
				if (result)
				{
					WaitCooldown = 4000;
				}

				return result;
			}

			return false;
		});

	FindPlayerSelector->addLambda([this]()
		{
			if (auto ptr = rampage.lock())
			{
				if (ptr->IsDead()) return false;
				return CanAttackSelector->execute();
			}

			return false;
		});

	FindPlayerSelector->addLambda([this]()
		{
			if (auto ptr = rampage.lock())
			{
				if (ptr->IsDead()) return false;
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
					if (ptr->IsDead()) return false;
					SkillAttackCooldown = 0;
					ptr->TurnToTarget(ptr->GetAggroTarget());
					if (ptr->UseSkillToAggro())
					{
						SkillAttackCooldown = 0;
						WaitCooldown = 3000;
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			// 스킬을 사용하지 못하고, 일반공격이 가능할 때
			if (auto ptr = rampage.lock())
			{
				if (ptr->IsDead()) return false;
				ptr->TurnToTarget(ptr->GetCloseTarget());
				if (ptr->BasicAttack())
				{
					WaitCooldown = 1500;
					return true;
				}
				else
				{
					return false;
				}
			}
		});
}

void RampageTree::MakeCanNotAttackSelector()
{
	CanNotAttackSelector->addLambda([this]()
		{
			if (auto ptr = rampage.lock())
			{
				if (ptr->IsDead()) return false;
				return ptr->MoveToTarget();
			}

			return false;
		});
}

void RampageTree::Tick(uint32 DeltaTime)
{
	if (DetectCooldown < DETECT_COOLTIME) DetectCooldown += DeltaTime;
	if (RegularPatternCooldown < RP_COOLTIME) RegularPatternCooldown += DeltaTime;
	if (SkillAttackCooldown < SKILL_COOLTIME) SkillAttackCooldown += DeltaTime;
	if (WaitCooldown > 0)
	{
		WaitCooldown -= DeltaTime;
		if (WaitCooldown < 0) WaitCooldown = 0;
		return;
	}
	if (auto rampagePtr = rampage.lock())
	{
		if (rampagePtr->isMoving) return;
	}
	RootSelector->execute();
}
