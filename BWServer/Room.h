#pragma once
#include <set>
#include "Member.h"
using namespace std;

class Room
{
	void Join(MemberPtr member);
	void Leave(MemberPtr member);
	void Broadcast(asio::mutable_buffer& buffer);

private:
	set<MemberPtr> _members;
};

