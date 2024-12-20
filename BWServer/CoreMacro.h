#pragma once

#define OUT

/*---------------
	  Lock
---------------*/

#define USE_MANY_LOCKS(count)	mutex _locks[count];
#define USE_LOCK				USE_MANY_LOCKS(1)
#define	WRITE_LOCK_IDX(idx)		lock_guard<mutex> lockGuard_##idx(_locks[idx]);
#define WRITE_LOCK				WRITE_LOCK_IDX(0)

/*----------------------
	  Crash
----------------------*/
#define CRASH(cause)						\
{											\
	uint32* crash = nullptr;				\
	_Analysis_assume_(crash != nullptr);	\
	*crash = 0XDEADBEEF;					\
}

#define ASSERT_CRASH(expr)					\
{											\
	if (!(expr))							\
	{										\
		CRASH("ASSERT_CRASH");				\
		_Analysis_assume_(expr);			\
	}										\
}