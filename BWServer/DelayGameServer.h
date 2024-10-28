#pragma once
#include "GameServer.h"
class DelayGameServer :
    public GameServer
{
public:
    DelayGameServer(asio::io_context& io_context, int port);

public:
    // 지연 시간 설정
    void SetDelay(int milliseconds);
    void SetLossRate(double rate);

    // 변동 지연 시간 설정
    void SetDelayWithJitter(int base_milliseconds, int jitter_milliseconds);

public:
    virtual void StartAccept() override;

    virtual void UdpSend(asio::mutable_buffer& buffer) override;
    virtual void AsyncUdpWrite(const char* message, size_t size) override;

private:
    bool shouldDropPacket() {
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        return dist(random_engine) < loss_rate;
    }

private:
    int delay_milliseconds;
    double loss_rate;
    std::mt19937 random_engine;
};

