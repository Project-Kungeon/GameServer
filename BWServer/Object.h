#pragma once
#include "Room.h"
#include <shared_mutex>
#include <memory>

struct Location
{
	float x;
	float y;
	float z;
};

class Object : public std::enable_shared_from_this<Object>
{
public:
	Object();
	Object(message::ObjectType objectType);
	virtual ~Object();
	virtual void Tick(uint32 DeltaTime);

	const bool IsPlayer()
	{ 
		std::shared_lock<std::shared_mutex> lock(mutex_);
		return _isPlayer;
	}

	// Set&Get
public:
	const uint32 GetObjectId() 
	{ 
		std::shared_lock<std::shared_mutex> lock(mutex_);
		return objectInfo->object_id(); 
	}

	const message::ObjectType GetObjectType()
	{
		return objectInfo->object_type();
	}


public:
	message::ObjectInfo*	objectInfo;
	message::PosInfo*		posInfo;
	atomic<std::weak_ptr<Room>> room;

public:
	Location GetLocation() 
	{
		GetReadLock(); 
		Location loc(posInfo->x(), posInfo->y(), posInfo->z());
		return loc;
	}

protected:
	bool _isPlayer = false;

protected:
	// 읽기 전용 뮤텍스
	std::unique_lock<std::shared_mutex> GetWriteLock() {
		return std::unique_lock<std::shared_mutex>(mutex_);
	}

	// 쓰기 전용 뮤텍스
	std::shared_lock<std::shared_mutex> GetReadLock() const {
		return std::shared_lock<std::shared_mutex>(mutex_);
	}
	
private:
	mutable std::shared_mutex mutex_;
};
