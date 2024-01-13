// BWServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "GameServer.h"
#include "Session.h"
#include "Room.h"

int main()
{
    int port = 4242;
    boost::asio::io_context io_context;
    GameServer server(io_context, port);
    server.StartAccept();
    std::cout << "Server Start " << port << '\n';

    std::vector<thread> threads;
    int count = 2;

    for (int i = 0; i < count; i++)
    {
        threads.emplace_back([&]
        {
            io_context.run();
        });
    }

    for (auto& thread : threads)
    {
        thread.join();
    }
}
