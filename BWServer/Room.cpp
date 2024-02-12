#include "pch.h"
#include "Room.h"

void Room::Join(MemberPtr member)
{
	_members.insert(member);
}

void Room::Leave(MemberPtr member)
{
}

void Room::Broadcast(asio::mutable_buffer& buffer)
{
}
