#include "pch.h"
#include "ItemObject.h"

ItemObject::ItemObject()
	: Object()
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

void ItemObject::OnPickedUp(PlayerPtr player)
{
	// 1. 해당 플레이어의 인벤토리에 아이템 등록
	// 2. 사라지게 한다.
	InventoryPtr inventory = player->GetLoadedInventory();
	
	inventory->PutItem(ItemUtils::CreateItem(static_pointer_cast<ItemObject>(shared_from_this())));
	this->Disapear();
}

void ItemObject::Disapear()
{
	if (auto roomPtr = room.load().lock())
	{
		// TODO Room에서 아이템 삭제하도록 해야 함.
		// TODO Broadcast하여 아이템을 월드 내에서 삭제

	}
}
