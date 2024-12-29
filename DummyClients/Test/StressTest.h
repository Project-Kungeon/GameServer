#pragma once
#include "pch.h"
#include "Session/Session.h"

class StressTest {
public:
    StressTest(const std::string& host, int port, int num_users)
        : host_(host), port_(port), num_users_(num_users) {}

    void Run()
    {
        boost::asio::io_context io_context;
        std::vector<std::shared_ptr<Session>> sessions;

        // N명의 유저 세션 생성
        for (int i = 0; i < num_users_; ++i)
            {
            auto session = std::make_shared<Session>(io_context, host_, port_);
            sessions.push_back(session);
            session->Connect();
        }

        // 작업자 스레드 생성
        std::vector<std::thread> worker_threads;
        for (int i = 0; i < 10; i++)
            {
            worker_threads.emplace_back([&io_context]()
            {
                io_context.run();
            });
        }

        account::login::C_Login loginPkt;
        loginPkt.add_email("test@test.com");
        loginPkt.add_password("test123");

        this_thread::sleep_for(1s);

        for (const auto& session : sessions)
        {
            const size_t requiredSize = PacketUtil::RequiredSize(loginPkt);

            char* rawBuffer = new char[requiredSize];
            auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
            PacketUtil::Serialize(sendBuffer, message::HEADER::LOGIN_REQ, loginPkt);

            session->Send(sendBuffer);
        }

        // 모든 작업자 스레드 종료 대기
        for (auto& thread : worker_threads)
        {
            if(thread.joinable()) 
            {
                thread.join();
            }
        }
    }

private:
    std::string host_;
    int port_;
    int num_users_;
};
