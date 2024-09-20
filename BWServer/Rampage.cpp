#include "pch.h"
#include "Rampage.h"

Rampage::Rampage()
	: Monster(message::MONSTER_TYPE_RAMPAGE, 1000, 1000, 100), Tree(new RampageTree(static_pointer_cast<Rampage>(shared_from_this())))
{
	Tree->Init();
}

Rampage::Rampage(float maxHp, float hp, float dropExp)
	: Monster(message::MONSTER_TYPE_RAMPAGE, maxHp, hp, dropExp), Tree(new RampageTree(static_pointer_cast<Rampage>(shared_from_this())))
{
	Tree->Init();
}

Rampage::~Rampage()
{
}

void Rampage::Tick(uint32 DeltaTime)
{
	Tree->Tick(DeltaTime);
	
}

bool Rampage::FindClosePlayer()
{
	RoomPtr roomPtr = room.load().lock();
	CloseTarget = roomPtr->FindClosePlayerBySelf(dynamic_pointer_cast<Creature>(shared_from_this()), DETECT_DISTANCE);
	/*
		플레이어 찾으면 true, 없으면 false;
	*/

	return CloseTarget.lock() != nullptr;
}

double Rampage::GetDistanceToTarget(std::weak_ptr<Creature> Target)
{
	if (auto creature = Target.lock())
	{
		Location SelfLoc = GetLocation();
		Location TargetLoc = creature->GetLocation();

		return sqrt(pow(abs((int)(SelfLoc.x - TargetLoc.x)), 2) +
			pow(abs((int)(SelfLoc.y - TargetLoc.y)), 2) +
			pow(abs((int)(SelfLoc.z - TargetLoc.z)), 2));
	}

	return -1;
}

bool Rampage::RegularPattern()
{
	if (phase == 1)
	{
		Roar();
		return true;
	}
	else if (phase == 2)
	{
		EarthQuake();
		return true;
	}
	return false;
}

bool Rampage::UseSkillToAggro()
{
	// AggroTarget이 존재한다면 스킬을 사용합니다. 쿨타임을 계산합니다.
	double distance = GetDistanceToTarget(AggroTarget);

	if (distance > 500)
	{
		ThrowAway();
		return true;
	}
	else if (distance >= 0)
	{
		EnhancedAttack();
		return true;
	}
	else
	{
		return false;
	}

	return false;

}

bool Rampage::BasicAttack()
{
	if (auto Target = CloseTarget.lock())
	{
		// TODO : BA Packet
	}

	return false;
}

bool Rampage::CanNotAttack()
{
	return false;
}

void Rampage::Roar()
{
}

void Rampage::EarthQuake()
{
}

void Rampage::TurnToTarget(std::weak_ptr<Creature> Target)
{
}

void Rampage::ThrowAway()
{
}

void Rampage::EnhancedAttack()
{
}
