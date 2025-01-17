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
using BufferPtr = boost::shared_ptr<char[]>;

#define USING_SHARED_PTR(name)	using name##Ptr = std::shared_ptr<class name>;


USING_SHARED_PTR(GameServer);
USING_SHARED_PTR(Session);
USING_SHARED_PTR(GameSession);
USING_SHARED_PTR(DelayGameSession);
USING_SHARED_PTR(Object);
USING_SHARED_PTR(Player);
USING_SHARED_PTR(Warrior);
USING_SHARED_PTR(Creature);
USING_SHARED_PTR(Monster);
USING_SHARED_PTR(Rampage);
USING_SHARED_PTR(Room);
USING_SHARED_PTR(GameRoom);
USING_SHARED_PTR(Inventory);
USING_SHARED_PTR(Item);
USING_SHARED_PTR(ItemObject);
USING_SHARED_PTR(AuctionItem);
USING_SHARED_PTR(AuctionManager);


USING_SHARED_PTR(Assassin);
USING_SHARED_PTR(Archor);