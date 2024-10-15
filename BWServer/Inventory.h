#pragma once
#include "Item.h"

struct Inven_Item
{
	ItemPtr _item;
	int count;
};

class Inventory
{
public:
	Inventory(PlayerPtr player);

public:
	bool PutItem(ItemPtr item);
	bool DeleteItem(uint64 item_id);
	bool UseItem(uint64 item_id);
	bool MoveItem(uint64 item_id, uint64 pos);

	game::item::S_Item_OpenInventory GetInventoryList();

private:
	USE_LOCK;
	vector<Inven_Item> _items;
	std::weak_ptr<Player> _player;
};

