#pragma once
#include "Member.h"
using namespace std;

class Room
{
public:
	void Join(MemberPtr member);
	void Leave(MemberPtr member);
	void Broadcast(asio::mutable_buffer& buffer);

private:
	set<MemberPtr> _members;
};
typedef boost::shared_ptr<Room> RoomRef;