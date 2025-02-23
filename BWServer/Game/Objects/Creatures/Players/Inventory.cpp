#include "pch.h"
#include "Inventory.h"

Inventory::Inventory(PlayerPtr player)
	: _items(vector<Inven_Item>(40, Inven_Item(nullptr, 0)))
	, _player(player)
{
}

bool Inventory::PutItem(ItemPtr item)
{
	WRITE_LOCK;
	int empty_index = -1;
	for (int i = 0; i < 40; i++)
	{
		if (empty_index == -1 && _items[i]._item == nullptr)
		{
			// 해당 칸 비어 있을 경우
			empty_index = i;
		}
		else if (_items[i]._item != nullptr && _items[i]._item->GetItemInfo()->item_table() == item->GetItemInfo()->item_table())
		{
			// 만약 아이템 테이블이 같다면 개수 증가
			_items[i].count++;
			return true;
		}
	}

	if (empty_index != -1)
	{
		_items[empty_index] = Inven_Item(item, 1);
		return true;
	}

	return false;
}

bool Inventory::DeleteItem(uint64 item_id)
{
	WRITE_LOCK;
	return false;
}

bool Inventory::UseItem(uint64 item_id)
{
	WRITE_LOCK;
	for (int i = 0; i < 40; i++)
	{
		if (_items[i]._item != nullptr && _items[i]._item->GetItemId() == item_id)
		{
			_items[i]._item->OnUsed();
			if(--_items[i].count < 0) _items[i] = Inven_Item(nullptr, 0);
			return true;
		}
	}
	return false;
	
}

bool Inventory::MoveItem(uint64 item_id, uint64 pos)
{
	WRITE_LOCK;
	return false;
}

game::item::S_Item_OpenInventory Inventory::GetInventoryList()
{
	WRITE_LOCK;
	game::item::S_Item_OpenInventory pkt;

	if (auto player = _player.lock())
	{
		pkt.set_player_id(player->GetObjectId());
		for (auto& item : _items)
		{
			auto inventorySlot = pkt.add_slots();
			auto item_info = inventorySlot->mutable_iteminfo();

			if (item._item != nullptr)
			{
				item_info->CopyFrom(*item._item->GetItemInfo());
				inventorySlot->set_cnt(item.count);
			}
			else
			{
				item_info->set_item_id(0);
				item_info->set_item_type(message::ItemType::NONE_Item);
				item_info->set_item_table(message::ItemTable::NONE_ITEM);
				inventorySlot->set_cnt(0);
			}
		}
	}

	return pkt;
}
