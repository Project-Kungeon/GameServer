#pragma once
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/shared_ptr.hpp>

#define USING_SHARED_PTR(name)	using name##Ptr = boost::shared_ptr<class name>;

USING_SHARED_PTR(Session);
USING_SHARED_PTR(GameSession);