#include "pch.h"
#include "Rampage.h"

Rampage::Rampage()
	: Monster(message::MONSTER_TYPE_RAMPAGE, 1000, 1000, 100)
{
}

Rampage::Rampage(float maxHp, float hp, float dropExp)
	: Monster(message::MONSTER_TYPE_RAMPAGE, maxHp, hp, dropExp)
{
}

Rampage::~Rampage()
{
}

void Rampage::Tick(uint32 DeltaTime)
{
	DetectCooldown += DeltaTime;

	// Detect Player..
	if (DetectCooldown >= DETECT_COOLTIME)
	{
		DetectCooldown = 0;
		if (FindClosePlayer())
		{
			spdlog::debug("Rampage found Player {}", CloseTarget.lock()->GetObjectId());
		}
	}

	
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
