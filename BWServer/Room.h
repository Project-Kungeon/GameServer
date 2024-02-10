#pragma once
#include <set>
#include "Member.h"
using namespace std;

class Room
{
public:
	void Join(MemberPtr member)
	{
		_members.insert(member); 
	}
	void Leave(MemberPtr member)
	{

	}
	void Broadcast(asio::mutable_buffer& buffer)
	{

	}

private:
	set<MemberPtr> _members;
};

