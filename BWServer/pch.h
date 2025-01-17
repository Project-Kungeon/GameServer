#pragma once
#define WIN32_LEAN_AND_MEAN	// 사용하지 않는 윈도우 헤더 제외
#define _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING

#ifdef _DEBUG
#pragma comment(lib, "MySQL\\Debug\\mysqlcppconn.lib")
#else
#pragma comment(lib, "MySQL\\Release\\mysqlcppconn.lib")
#endif

#pragma comment(lib, "bcrypt.lib")

#include "CorePch.h"