#pragma once
#include "GameSession.h"
class DelayGameSession :
    public GameSession
{
public:
    DelayGameSession(asio::io_context& io_context);
    virtual void AsyncWrite(const char* message, size_t size) override;

public:
    // 지연 시간 설정
    void SetDelay(int milliseconds);

    // 변동 지연 시간 설정
    void SetDelayWithJitter(int base_milliseconds, int jitter_milliseconds);
private:
    int delay_milliseconds;
    
};

inline DelayGameSessionPtr CreateDelaySession(asio::io_context& io_context, int delay_ms)
{
    auto session = std::make_shared<DelayGameSession>(io_context);
    session->SetDelay(delay_ms);
    return session;
}