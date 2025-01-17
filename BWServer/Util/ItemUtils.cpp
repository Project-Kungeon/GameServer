#include "pch.h"
#include "ItemUtils.h"

atomic<unsigned int> ItemUtils::s_idGenerator = 1;

ItemPtr ItemUtils::CreateItem(PlayerPtr player, message::ItemType itemType, message::ItemTable itemTable)
{
	const unsigned int newId = s_idGenerator.fetch_add(1);
	ItemPtr new_item = std::make_shared<Item>(newId, player, itemType, itemTable);

	return new_item;
}

ItemPtr ItemUtils::CreateItem(PlayerPtr player, ItemObjectPtr itemObject)
{
	return ItemUtils::CreateItem(player, itemObject->GetItemType(), itemObject->GetItemTable());
}

