#pragma once
#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

using BYTE = unsigned char;
using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

#define USING_SHARED_PTR(name)	using name##Ptr = std::shared_ptr<class name>;

USING_SHARED_PTR(Session);
USING_SHARED_PTR(GameSession);
USING_SHARED_PTR(Object);
USING_SHARED_PTR(Player);
USING_SHARED_PTR(Room);