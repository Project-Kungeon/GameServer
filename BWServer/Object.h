#pragma once
class Object : public boost::enable_shared_from_this<Object>
{
public:
	Object();
	virtual ~Object();

	bool IsPlayer() { return IsPlayer; }

public:
	message::ObjectInfo*	objectInfo;
	message::PosInfo*		posInfo;

public:
	atomic<boost::weak_ptr<Room>> room;


protected:
	bool _isPlayer = false;
};

