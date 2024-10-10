#pragma once
#include "Player.h"
class Item
{
public:
	Item();
	Item(uint64 itemId, message::ItemType itemType, message::ItemTable itemTable);

	virtual ~Item();

public:
	virtual void OnUsed(PlayerPtr player);
	
private:
	message::ItemInfo* ItemInfo;
};

