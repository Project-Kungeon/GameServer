#include "pch.h"
#include "TimeUtils.h"

uint64 TimeUtils::GetSystemTimestamoMillisec()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}
