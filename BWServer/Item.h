#pragma once
#include "Player.h"
class Item
{
public:
	Item();
	Item(uint64 itemId, PlayerPtr player, message::ItemType itemType, message::ItemTable itemTable);

	virtual ~Item();

public:
	virtual void OnUsed();

	uint64 GetItemId() { return itemInfo->item_id(); }
	message::ItemInfo* GetItemInfo() const { return itemInfo; }
	
private:
	message::ItemInfo* itemInfo;
	std::weak_ptr<Player> _player;
};

