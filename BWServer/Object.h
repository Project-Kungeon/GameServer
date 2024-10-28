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

	void SetMovementInfo(double x, double y)
	{
		movement_x = x;
		movement_y = y;
	}

	void SetYawInfo(float camera_yaw, float controller_yaw)
	{
		this->camera_yaw = camera_yaw;
		this->controller_yaw = controller_yaw;
	}


public:
	message::ObjectInfo*	objectInfo;
	message::PosInfo*		posInfo;
	double movement_x;
	double movement_y;
	float controller_yaw;
	float camera_yaw;
	atomic<std::weak_ptr<Room>> room;

public:
	Location GetLocation() 
	{
		GetReadLock(); 
		Location loc(posInfo->x(), posInfo->y(), posInfo->z());
		return loc;
	}

	void SetPosInfo(message::PosInfo NewPosInfo)
	{
		posInfo->CopyFrom(NewPosInfo);
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
