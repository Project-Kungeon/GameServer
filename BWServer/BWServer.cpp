// BWServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "pch.h"
#include "GameServer.h"
#include "Room.h"
#include "ServerPacketHandler.h"
#include "TickGenerator.h"

int main()
{
    ServerPacketHandler::Init();
    Room::init();
    spdlog::set_level(spdlog::level::trace);
    spdlog::info("SpdLog Test");

    int port = 4242;
    boost::asio::io_context io_context;
    boost::asio::io_context io_context_tick;
    TickGenerator tickGenerator(io_context_tick, 45, GRoom[0]);

    GameServer server(io_context, port);
    server.StartAccept();
    spdlog::info("Server Start {}", port);
    std::cout << "Server Start " << port << '\n';

    //int count = 2;
    tickGenerator.start(nullptr);

    //std::vector<std::thread> threads;
    //for (int i = 0; i < 5; ++i) {
    //    threads.emplace_back([&io_context]() {
    //        io_context.run();
    //        });
    //}

    std::thread t(boost::bind(&boost::asio::io_context::run, &io_context));

    std::thread t1(boost::bind(&boost::asio::io_context::run, &io_context_tick));
    //std::thread t2(boost::bind(&boost::asio::io_context::run, &io_context_tick));
    io_context_tick.run();

    t.join();
    t1.join();
    //t2.join();
}
