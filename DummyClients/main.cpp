#include "pch.h"
#include "Test/StressTest.h"

int main()
{
    try {
        StressTest test("127.0.0.1", 4242, 1000); // 1000명의 동시 접속 테스트
        test.Run();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
