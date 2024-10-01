#include "pch.h"
#include "Rampage.h"


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
		// TODO : BA Packet
		spdlog::debug("Rampage Basic Attack To {}", Target->GetObjectId());
		RoomPtr roomPtr = room.load(memory_order_acquire).lock();
		monster::pattern::S_Rampage_BasicAttack pkt;
		pkt.set_object_id(GetObjectId());

		const size_t requiredSize = PacketUtil::RequiredSize(pkt);
		char* rawBuffer = new char[requiredSize];
		auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
		PacketUtil::Serialize(sendBuffer, message::HEADER::RAMPAGE_BASICATTACK_RES, pkt);

		roomPtr->Broadcast(sendBuffer, -1);
	}

	return false;
}

bool Rampage::MoveToTarget(std::weak_ptr<Creature> Target)
{
	if (auto TargetPtr = Target.lock())
	{
		//TurnToTarget(Target);

		spdlog::debug("Rampage Move To {}", TargetPtr->GetObjectId());
		RoomPtr roomPtr = room.load(memory_order_acquire).lock();
		message::S_Move pkt;

		Location loc = TargetPtr->GetLocation();
		message::PosInfo* posInfo = pkt.mutable_posinfo();
		posInfo->set_object_id(GetObjectId());
		posInfo->set_state(message::MOVE_STATE_RUN);
		posInfo->set_x(loc.x);
		posInfo->set_y(loc.y);
		posInfo->set_z(loc.z);
		posInfo->set_yaw(posInfo->yaw());

		const size_t requiredSize = PacketUtil::RequiredSize(pkt);
		char* rawBuffer = new char[requiredSize];
		auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
		PacketUtil::Serialize(sendBuffer, message::HEADER::MONSTER_MOVE_RES, pkt);

		roomPtr->Broadcast(sendBuffer, -1);

		return true;
	}

	return false;
}

void Rampage::Roar()
{
	spdlog::debug("Rampage used Roar!");
	RoomPtr roomPtr = room.load(memory_order_acquire).lock();
	monster::pattern::S_Rampage_Roar pkt;
	pkt.set_object_id(GetObjectId());

	const size_t requiredSize = PacketUtil::RequiredSize(pkt);
	char* rawBuffer = new char[requiredSize];
	auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
	PacketUtil::Serialize(sendBuffer, message::HEADER::RAMPAGE_ROAR_RES, pkt);

	roomPtr->Broadcast(sendBuffer, -1);
}

void Rampage::EarthQuake()
{
	spdlog::debug("Rampage used EarthQuake!");
	RoomPtr roomPtr = room.load(memory_order_acquire).lock();
	monster::pattern::S_Rampage_EarthQuake pkt;
	pkt.set_object_id(GetObjectId());

	const size_t requiredSize = PacketUtil::RequiredSize(pkt);
	char* rawBuffer = new char[requiredSize];
	auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
	PacketUtil::Serialize(sendBuffer, message::HEADER::RAMPAGE_EARTHQUAKE_RES, pkt);

	roomPtr->Broadcast(sendBuffer, -1);
}

void Rampage::TurnToTarget(std::weak_ptr<Creature> Target)
{
	if (auto target = Target.lock())
	{
		spdlog::debug("Rampage Turned To Target {}", target->GetObjectId());
		Location SelfLoc = GetLocation();
		Location TargetLoc = target->GetLocation();
		
		float LookX = TargetLoc.x - SelfLoc.x;
		float LookY = TargetLoc.y - SelfLoc.y;
		float LookZ = 0.0f;

		float rotationMatrix[3][3];
		MathUtils::makeRotationMatrixFromX(LookX, LookY, LookZ, rotationMatrix);
		Rotator rotator = MathUtils::matrixToRotator(rotationMatrix);

		RoomPtr roomPtr = room.load(memory_order_acquire).lock();
		monster::pattern::S_TurnToTarget pkt;
		pkt.set_object_id(GetObjectId());
		pkt.set_pitch(rotator.Pitch);
		pkt.set_roll(rotator.Roll);
		pkt.set_yaw(rotator.Yaw);

		//target->posInfo->set_yaw(rotator.Yaw);

		const size_t requiredSize = PacketUtil::RequiredSize(pkt);
		char* rawBuffer = new char[requiredSize];
		auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
		PacketUtil::Serialize(sendBuffer, message::HEADER::RAMPAGE_TURNTOTARGET_RES, pkt);

		roomPtr->Broadcast(sendBuffer, -1);

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
