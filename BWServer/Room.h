#pragma once
#include "Member.h"
using namespace std;



class Room
{
public:
	void init();
	bool Join(ObjectPtr object);
	bool Leave(ObjectPtr object);
	void Broadcast(asio::mutable_buffer& buffer, unsigned int exceptId);

	bool HandleEnterPlayer(PlayerPtr player);
	bool HandleLeavePlayer(PlayerPtr player);
	void HandleMovePlayer(PlayerPtr player);

private:
	bool AddObject(ObjectPtr object);
	bool RemoveObject(unsigned int objectId);

private:
	set<MemberPtr> _members;
	unordered_map<unsigned int, ObjectPtr> _objects;
};

extern RoomPtr GRoom[UINT16_MAX];