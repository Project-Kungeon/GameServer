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

Object::~Object()
{
	delete objectInfo;
}
