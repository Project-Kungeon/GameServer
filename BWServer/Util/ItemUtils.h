#pragma once
#include "Objects/ItemObject.h"
#include "Objects/Item.h"
#include <memory>

class ItemUtils
{
public:
	static ItemPtr CreateItem(PlayerPtr player, message::ItemType itemType, message::ItemTable itemTable);
	static ItemPtr CreateItem(PlayerPtr player, ItemObjectPtr itemObject);

private:
	static std::atomic<unsigned int> s_idGenerator;
};

