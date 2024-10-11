#include "pch.h"
#include "Item.h"

Item::Item()
	: _player(std::weak_ptr<Player>())
{
	itemInfo = new message::ItemInfo();
	itemInfo->set_item_id(0);
	itemInfo->set_item_type(message::ItemType::NONE_Item);
	itemInfo->set_item_table(message::ItemTable::NONE_ITEM);
}

Item::Item(uint64 itemId, PlayerPtr player, message::ItemType itemType, message::ItemTable itemTable)
	: _player(player)
{
	itemInfo = new message::ItemInfo();
	itemInfo->set_item_id(itemId);
	itemInfo->set_item_type(itemType);
	itemInfo->set_item_table(itemTable);
}

Item::~Item()
{
	delete itemInfo;
	itemInfo = nullptr;
}

void Item::OnUsed()
{
	if (auto player = _player.lock())
	{
		switch (itemInfo->item_table())
		{
		case message::GENERAL_HEALTH_POSION:
			if (auto room = player->room.load().lock())
			{
				room->DoAsync(&Room::BroadcastHealCreature, static_pointer_cast<Creature>(player), 25.0f);
			}
			break;
		default:
			break;
		}
	}
}
