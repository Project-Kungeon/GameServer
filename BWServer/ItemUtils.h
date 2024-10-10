#pragma once
#include "ItemObject.h"
#include "Item.h"
#include <memory>

class ItemUtils
{
public:
	static ItemPtr CreateItem(message::ItemType itemType, message::ItemTable itemTable);
	static ItemPtr CreateItem(ItemObjectPtr itemObject);

private:
	static std::atomic<unsigned int> s_idGenerator;
};

