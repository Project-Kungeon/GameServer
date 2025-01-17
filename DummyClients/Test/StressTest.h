#pragma once
#include "pch.h"
#include "Session/Session.h"

class StressTest {
public:
    StressTest(const std::string& host, int port, int num_users)
        : host_(host), port_(port), num_users_(num_users)
    {
    }

    void Run()
    {
        std::vector<asio::io_context*> io_contexts;
        std::vector<std::shared_ptr<Session>> sessions;

        for (int i = 0; i < 20; i++)
        {
            io_contexts.push_back(new asio::io_context());
        }

        int cnt = 0;
        // 1000명이면, 하나의 io_context 당 50개의 세션 담당
        for (int i = 0; i < num_users_; i++)
        {
            auto session = std::make_shared<Session>(*io_contexts[i % 20], host_, port_);
            sessions.push_back(session);
            session->Connect();
            cnt++;
        if (cnt % 50 == 0)
        {
            cnt = 0;
            this_thread::sleep_for(100ms);
        }
}       std::vector<std::thread> worker_threads;
        // 1ㄷ1로 io_context run 워커스레드 시작
        for (int i = 0; i < 20; i++)
            {
            worker_threads.emplace_back([&io_contexts, i]()
            {
                io_contexts[i]->run();
            });
        }


        //boost::asio::io_context io_context;
        //std::vector<std::shared_ptr<Session>> sessions;

        //int cnt = 0;
        //this_thread::sleep_for(3s);
        //// N명의 유저 세션 생성
        //for (int i = 0; i < num_users_; i++)
        //    {
        //    auto session = std::make_shared<Session>(io_context, host_, port_);
        //    sessions.push_back(session);
        //    session->Connect();
        //    cnt++;
        //    if (cnt % 50 == 0)
        //    {
        //        cnt = 0;
        //        this_thread::sleep_for(100ms);
        //    }
        //}

        //// 작업자 스레드 생성
        //std::vector<std::thread> worker_threads;
        //for (int i = 0; i < 40; i++)
        //    {
        //    worker_threads.emplace_back([&io_context]()
        //    {
        //        io_context.run();
        //    });
        //}

        //account::login::C_Login loginPkt;
        //loginPkt.add_email("test@test.com");
        //loginPkt.add_password("test123");

        //
        //
        //for (const auto& session : sessions)
        //{
        //    const size_t requiredSize = PacketUtil::RequiredSize(loginPkt);

        //    char* rawBuffer = new char[requiredSize];
        //    auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
        //    PacketUtil::Serialize(sendBuffer, message::HEADER::LOGIN_REQ, loginPkt);

        //    session->Send(sendBuffer);
        //    
        //}

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
