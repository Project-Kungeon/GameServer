#include "pch.h"
#include "ItemObject.h"

ItemObject::ItemObject()
	: Object(message::OBJECT_TYPE_ITEM)
	, _itemType(message::ItemType::NONE_Item)
	, _itemTable(message::ItemTable::GENERAL_HEALTH_POSION)
{
}

ItemObject::ItemObject(message::ItemType itemType, message::ItemTable itemTable)
	: Object(message::OBJECT_TYPE_ITEM)
	, _itemType(itemType)
	, _itemTable(itemTable)
{
}

bool ItemObject::OnPickedUp(PlayerPtr player)
{
	
	return true;
}

void ItemObject::Disapear()
{
	if (auto roomPtr = room.load().lock())
	{
		// TODO Room에서 아이템 삭제하도록 해야 함.
		// TODO Broadcast하여 아이템을 월드 내에서 삭제
		roomPtr->DoAsync(&Room::Leave, shared_from_this());

	}
}
