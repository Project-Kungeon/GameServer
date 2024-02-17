#pragma once
#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#define USING_SHARED_PTR(name)	using name##Ptr = std::shared_ptr<class name>;

USING_SHARED_PTR(Session);
USING_SHARED_PTR(GameSession);
USING_SHARED_PTR(Player);