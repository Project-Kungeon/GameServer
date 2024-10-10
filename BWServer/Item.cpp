#include "pch.h"
#include "Item.h"

Item::Item()
{
}

Item::Item(uint64 itemId, message::ItemType itemType, message::ItemTable itemTable)
{
	ItemInfo = new message::ItemInfo();
	ItemInfo->set_item_id(itemId);
	ItemInfo->set_item_type(itemType);
	ItemInfo->set_item_table(itemTable);
}

Item::~Item()
{
	delete ItemInfo;
	ItemInfo = nullptr;
}

void Item::OnUsed(PlayerPtr player)
{
}
