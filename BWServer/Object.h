#pragma once
#include "Room.h"
#include <memory>

class Object : public std::enable_shared_from_this<Object>
{
public:
	Object();
	virtual ~Object();

	bool IsPlayer() { return _isPlayer; }

public:
	message::ObjectInfo*	objectInfo;
	message::PosInfo*		posInfo;

public:
	atomic<std::weak_ptr<Room>> room;




protected:
	bool _isPlayer = false;
};

