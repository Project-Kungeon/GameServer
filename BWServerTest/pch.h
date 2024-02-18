//
// pch.h
//

#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "CorePch.h"

#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
using namespace boost;

#include "LobbyPacketHandler.h"
#include "Session.h"
#include "Room.h"