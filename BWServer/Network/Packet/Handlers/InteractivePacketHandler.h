#pragma once
class InteractivePacketHandler
{
public:
	static bool Handle_C_Item_PickedUp(SessionPtr& session, game::item::C_Item_PickedUp& pkt);
	static bool Handle_C_Item_ConsumeableUsed(SessionPtr& session, game::item::C_Item_ConsumeableUsed& pkt);
	static bool Handle_C_Item_OpenInventory(SessionPtr& session, game::item::C_Item_OpenInventory& pkt);
};

