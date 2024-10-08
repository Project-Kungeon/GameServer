#include "pch.h"
#include "Object.h"

Object::Object()
{
	objectInfo = new message::ObjectInfo();
	posInfo = new message::PosInfo();

	// PosInfo 할당
	objectInfo->set_allocated_pos_info(posInfo);
	objectInfo->set_object_type(message::OBJECT_TYPE_NONE);
}

Object::Object(message::ObjectType objectType)
{

	objectInfo = new message::ObjectInfo();
	posInfo = new message::PosInfo();

	// PosInfo 할당
	objectInfo->set_allocated_pos_info(posInfo);
	objectInfo->set_object_type(objectType);
}

Object::~Object()
{
	delete objectInfo;
}

void Object::Tick(uint32 DeltaTime)
{
	GetWriteLock();
}
