#pragma once
#include "Object.h"

class ItemObject :
    public Object
{
public:
    ItemObject();
    ItemObject(message::ItemType itemType, message::ItemTable itemTable);

public:
    virtual void OnPickedUp(PlayerPtr player);
    virtual void Disapear();


    // Getter / Setter
public:
    message::ItemType GetItemType() { return _itemType; };
    message::ItemTable GetItemTable() { return _itemTable; };


protected:
    message::ItemType _itemType;
    message::ItemTable _itemTable;

};

