#pragma once
#include "Room.h"
#include <memory>

class Object : public std::enable_shared_from_this<Object>
{
public:
	Object();
	Object(message::ObjectType objectType);
	virtual ~Object();

	bool IsPlayer() { return _isPlayer; }

	// Set&Get
public:
	uint32 GetObjectId() { return objectInfo->object_id(); }


public:
	message::ObjectInfo*	objectInfo;
	message::PosInfo*		posInfo;

public:
	atomic<std::weak_ptr<Room>> room;

protected:
	bool _isPlayer = false;
};

