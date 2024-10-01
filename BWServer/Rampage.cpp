#include "pch.h"
#include "Rampage.h"
#include "Room.h"


Rampage::Rampage()
	: Monster(message::MONSTER_TYPE_RAMPAGE, 1000, 1000, 100), Tree(nullptr)
{
}
//new RampageTree(static_pointer_cast<Rampage>(shared_from_this()))

Rampage::Rampage(float maxHp, float hp, float dropExp)
	: Monster(message::MONSTER_TYPE_RAMPAGE, maxHp, hp, dropExp), Tree(nullptr)
{
}

Rampage::~Rampage()
{
}

void Rampage::Init()
{
	Tree = std::make_shared<RampageTree>(std::static_pointer_cast<Rampage>(shared_from_this()));
	Tree->Init();
}

void Rampage::Tick(uint32 DeltaTime)
{
	if(Tree)
		Tree->Tick(DeltaTime);
	
}

RampagePtr Rampage::GetRampagePtr()
{
	return static_pointer_cast<Rampage>(shared_from_this());
}

void Rampage::Damaged(CreaturePtr attacker, float damage)
{
	Monster::Damaged(attacker, damage);

	GetWriteLock();
	std::weak_ptr<Creature> weakCreature = attacker;

	uint32 object_id = attacker->GetObjectId();
	auto& statPair = damageStats[object_id];
	statPair.first = attacker;  // Update or set the weak_ptr
	statPair.second += damage;  // Accumulate damage
	FindTopDamageDealerToAggro();
}

bool Rampage::FindClosePlayer()
{
	spdlog::debug("Rampage used FindClosePlayer!");
	RoomPtr roomPtr = room.load(memory_order_acquire).lock();
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
	spdlog::debug("Rampage used RegularPattern!");
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
	// distance == -1 -> No Pointer
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
		if (auto roomPtr = room.load().lock())
		{
			spdlog::debug("Rampage Basic Attack To {}", Target->GetObjectId());
			roomPtr->DoAsync(&Room::SendRampageBasicAttack, GetRampagePtr());
			return true;
		}
	}

	return false;
}

bool Rampage::MoveToTarget(std::weak_ptr<Creature> Target)
{
	if (auto TargetPtr = Target.lock())
	{
		//TurnToTarget(Target);
		if (auto roomPtr = room.load().lock())
		{
			roomPtr->DoAsync(&Room::SendRampageMoveToTarget, GetRampagePtr(), TargetPtr);
			return true;
		}
	}

	return false;
}

void Rampage::Roar()
{
	if (auto roomPtr = room.load().lock())
	{
		spdlog::debug("Rampage used Roar!");
		roomPtr->DoAsync(&Room::SendRamapgeRoar, GetRampagePtr());
	}
}

void Rampage::EarthQuake()
{
	if (auto roomPtr = room.load().lock())
	{
		spdlog::debug("Rampage used EarthQuake!");
		roomPtr->DoAsync(&Room::SendRampageEarthQuake, GetRampagePtr());
	}
}

void Rampage::TurnToTarget(std::weak_ptr<Creature> Target)
{
	if (auto target = Target.lock())
	{
		if (auto roomPtr = room.load().lock())
		{
			spdlog::debug("Rampage Turned To Target {}", target->GetObjectId());
			roomPtr->DoAsync(&Room::SendRamapgeTurnToTarget, GetRampagePtr(), target);
		}
	}
}

void Rampage::ThrowAway()
{
	spdlog::debug("Rampage used ThrowAway");
}

void Rampage::EnhancedAttack()
{
	spdlog::debug("Rampage used EnhancedAttack");
}

void Rampage::cleanupExpiredPointers() {
	for (auto it = damageStats.begin(); it != damageStats.end(); )
	{
		if (it->second.first.expired())
		{
			it = damageStats.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Rampage::FindTopDamageDealerToAggro()
{
	if (damageStats.empty())
	{
		return;
	}

	auto topDamageDealer = std::max_element(
		damageStats.begin(), damageStats.end(),
		[](const auto& a, const auto& b)
		{
			return a.second.second < b.second.second;
		}
	);

	// weak_ptr 이니까.. 포인터가 존재하는지 검증해야 합니다.
	if (auto ptr = topDamageDealer->second.first.lock())
	{
		AggroTarget = topDamageDealer->second.first;
	}
	else
	{
		// 청소하고 다시 가져오기
		cleanupExpiredPointers();
		FindTopDamageDealerToAggro();
	}
}
