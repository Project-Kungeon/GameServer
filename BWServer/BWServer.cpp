// BWServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "pch.h"

/*#include "DB/MySQLConnection.h"
#include "ServerCore/DB/DBConnectionPool.h"*/

#include "Server/DelayGameServer.h"
#include "Server/GameRoom.h"
#include "Network/Packet/Handlers/ServerPacketHandler.h"


#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

int main()
{
    try
    {
        sql::Driver* driver = get_driver_instance();
        const string server1 = "tcp://127.0.0.1:3306";
        const string name1 = "root";
        const string password1 = "1342";
        std::unique_ptr<sql::Connection> conn(driver->connect(server1, name1, password1));
    }
    
    catch (sql::SQLException& e) {
        std::cout << "# ERR: SQLException" << std::endl;
        std::cout << "Error code: " << e.getErrorCode() << std::endl;    // MySQL 에러 코드
        std::cout << "SQL State: " << e.getSQLState() << std::endl;      // SQL State 코드
        std::cout << "Error msg: " << e.what() << std::endl;             // 에러 메시지
    }
    std::string password = "test123";
    std::string hash = BCrypt::generateHash(password);
    
    std::cout << "Hash: " << hash << std::endl;
    std::cout << "Verify: " << BCrypt::validatePassword(password, hash) << std::endl;
    
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

    

    /*std::shared_ptr<active911::MySQLConnectionFactory>connection_factory(new active911::MySQLConnectionFactory
        ("localhost:3306", "root", "1342"));
    std::shared_ptr<active911::ConnectionPool<active911::MySQLConnection>> GConnectionPool(new active911::ConnectionPool<active911::MySQLConnection>(5, connection_factory));*/

    
    //ASSERT_CRASH(GDBConnectionPool->Connect(10, L"DRIVER={MariaDB ODBC 3.2 Driver};SERVER=localhost;PORT=3306;DATABASE=GameDB;UID=root;PWD=1342;"));
    spdlog::info("Server Start {}", port);

    // For UDP TEST
    // GRoom[0]->RegisterGameServer(game_server);

    //MonsterPtr monster = ObjectUtils::CreateMonster(message::MONSTER_TYPE_RAMPAGE);
    //GRoom[0]->SpawnMonster(monster);

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
}
