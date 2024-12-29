#include "pch.h"
#include "Test/StressTest.h"

int main()
{
    ClientPacketHandler::Init();
    try {
        StressTest test("127.0.0.1", 4242, 100); // 1000명의 동시 접속 테스트
        test.Run();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
