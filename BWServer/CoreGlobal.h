#pragma once
#include "ServerCore/DB/DBConnectionPool.h"
DBConnectionPool* GDBConnectionPool = nullptr;

class CoreGlobal
{
public:
	CoreGlobal()
	{
		spdlog::info("Init ConnectionPool...");
		GDBConnectionPool = new DBConnectionPool();
	}

	~CoreGlobal()
	{
		delete GDBConnectionPool;
	}
} GCoreGlobal;