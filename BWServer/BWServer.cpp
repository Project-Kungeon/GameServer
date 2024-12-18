// BWServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "pch.h"
#include "DelayGameServer.h"
#include "GameRoom.h"
#include "ServerPacketHandler.h"
#include "Monster.h"
#include "Warrior.h"

int main()
{
    boost::asio::io_context io_context;
    ServerPacketHandler::Init();
    GameRoom::init(io_context);
    spdlog::set_level(spdlog::level::trace);

    int port = 4242;
    
    boost::asio::io_context io_context_tick;

    //GameServer* server = new GameServer(io_context, port);
    //GameServerPtr game_server(server);
    //game_server->StartAccept();
    GameServer* server = new GameServer(io_context, port);
    GameServerPtr game_server(server);
    game_server->StartAccept();


    spdlog::info("Server Start {}", port);

    // For UDP TEST
    GRoom[0]->RegisterGameServer(game_server);

    MonsterPtr monster = ObjectUtils::CreateMonster(message::MONSTER_TYPE_RAMPAGE);
    GRoom[0]->SpawnMonster(monster);

    //ItemObjectPtr itemObject = ObjectUtils::CreateItemObject(message::ItemType::Consumable, message::ItemTable::GENERAL_HEALTH_POSION);
    //GRoom[0]->SpawnObject(itemObject);
    //int count = 2;
    GRoom[0]->DoAsync(&Room::HandleTick, (uint32)22);

    std::vector<std::thread> thread_pool;
    for (int i = 0; i < 5; ++i) {
        thread_pool.emplace_back([&io_context]() {
            io_context.run();
            });
    }

    for (auto& thread : thread_pool) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    //std::thread t(boost::bind(&boost::asio::io_context::run, &io_context));

    //std::thread t1(boost::bind(&boost::asio::io_context::run, &io_context_tick));

    //t.join();
    //t1.join();
}
