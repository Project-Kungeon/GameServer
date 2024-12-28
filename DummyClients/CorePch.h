#pragma once
#include "Types.h"
#include "CoreMacro.h"

#include <array>
#include <cmath>
#include <cstdio>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <iostream>
#include <memory>
#include <chrono>
#include <exception>
#include <deque>

#include "PacketHandler/Packet.h"
#include "build/Login.pb.h"
#include "build/Message.pb.h"
#include "build/CharacterSelect.pb.h"
#include "build/Ping.pb.h"
#include "build/Enum.pb.h"
#include "build/Struct.pb.h"

#include "PacketHandler/ClientPacketHandler.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "spdlog/spdlog.h" 
#include "spdlog/sinks/basic_file_sink.h" 
#include "spdlog/sinks/rotating_file_sink.h" 
#include "spdlog/sinks/daily_file_sink.h"

#include "Util/TimeUtils.h"