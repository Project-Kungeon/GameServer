#pragma once
#include "Member.h"
#include "Message.pb.h"
using namespace std;

class Room
{
public:
	static void init();
	bool Join(ObjectPtr object);
	bool Leave(ObjectPtr object);
	void Broadcast(asio::mutable_buffer& buffer, uint64 exceptId);

	bool HandleEnterPlayer(PlayerPtr player);
	bool HandleLeavePlayer(PlayerPtr player);
	void HandleMove(message::C_Move pkt);

private:
	bool AddObject(ObjectPtr object);
	bool RemoveObject(uint64 objectId);

private:
	set<MemberPtr> _members;
	unordered_map<uint64, ObjectPtr> _objects;
};

extern RoomPtr GRoom[UINT16_MAX];