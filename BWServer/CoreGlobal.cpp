#include "pch.h"
#include "CoreGlobal.h"

sw::redis::Redis* GRedis = nullptr;

class CoreGlobal
{
public:
    CoreGlobal()
    {
		GRedis = new sw::redis::Redis("tcp://127.0.0.1:6379");
    }

    ~CoreGlobal()
    {
		delete GRedis;
    	GRedis = nullptr;
    }
};

CoreGlobal GCoreGlobal;