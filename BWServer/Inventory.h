#pragma once
#include "Item.h"
class Inventory
{
public:
	Inventory();

public:
	bool PutItem(ItemPtr item);
	bool DeleteItem(uint64 item_id);
	bool UseItem(uint64 item_id);
	bool MoveItem(uint64 item_id, uint64 pos);

private:
	vector<ItemPtr> _items;
};

