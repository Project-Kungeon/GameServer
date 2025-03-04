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

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "CoreGlobal.h"
#include "Util/RandomUtil.h"
#include "Util/ObjectUtils.h"
#include "Util/MathUtils.h"
#include "Util/ItemUtils.h"
#include "Util/TimeUtils.h"
#include "Util/SqlUtils.h"
#include "Server/Session/PacketSession.h"
#include "Server/Session/GameSession.h"
#include "Server/Session/DelayGameSession.h"

#include "spdlog/spdlog.h" 
#include "spdlog/sinks/basic_file_sink.h" 
#include "spdlog/sinks/rotating_file_sink.h" 
#include "spdlog/sinks/daily_file_sink.h"

#include "mysql/mysql_connection.h"
#include "mysql/cppconn/driver.h"
#include "mysql/cppconn/exception.h"
#include "mysql/cppconn/resultset.h"
#include "mysql/cppconn/prepared_statement.h"
#include "mysql/cppconn/statement.h"

#include <bcrypt/Lib_BCrypt.hpp>
