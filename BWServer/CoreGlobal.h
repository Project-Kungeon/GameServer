#pragma once
#include "DB/ConnectionPool.h"
#include "DB/MySQLConnection.h"

class CoreGlobal
{
public:
	CoreGlobal()
	{
		//std::shared_ptr<active911::MySQLConnectionFactory>connection_factory(new active911::MySQLConnectionFactory
		//("localhost:3306", "root", "1342"));
		//active911::ConnectionPool<active911::MySQLConnection>::Init(5, connection_factory);
		//GConnectionPool = new active911::ConnectionPool<active911::MySQLConnection>(5, connection_factory);
	}

	~CoreGlobal()
	{
		
	}
} GCoreGlobal;