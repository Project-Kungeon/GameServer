#include "pch.h"
#include "Inventory.h"

Inventory::Inventory()
	: _items(vector<ItemPtr>(40))
{
}

bool Inventory::PutItem(ItemPtr item)
{
	return false;
}

bool Inventory::DeleteItem(uint64 item_id)
{
	return false;
}

bool Inventory::UseItem(uint64 item_id)
{
	return false;
}

bool Inventory::MoveItem(uint64 item_id, uint64 pos)
{
	return false;
}
