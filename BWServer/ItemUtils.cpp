#include "pch.h"
#include "ItemUtils.h"

atomic<unsigned int> ItemUtils::s_idGenerator = 1;

ItemPtr ItemUtils::CreateItem(message::ItemType itemType, message::ItemTable itemTable)
{
	const unsigned int newId = s_idGenerator.fetch_add(1);
	ItemPtr new_item = std::make_shared<Item>(newId, itemType, itemTable);

	return new_item;
}

ItemPtr ItemUtils::CreateItem(ItemObjectPtr itemObject)
{
	return ItemUtils::CreateItem(itemObject->GetItemType(), itemObject->GetItemTable());
}

