#pragma once
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
using namespace boost;

class Member
{
public:
	Member() {};
	virtual ~Member() {};
	virtual void Send(asio::mutable_buffer& buffer) abstract;
};

typedef boost::shared_ptr<Member> MemberPtr;