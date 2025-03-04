#include "pch.h"
#include "ConnectionPool.h"

active911::ConnectionPool<active911::MySQLConnection>* GConnectionPool = nullptr;
