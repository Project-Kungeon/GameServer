#include "pch.h"
#include "DelayGameSession.h"

DelayGameSession::DelayGameSession(asio::io_context& io_context)
    : GameSession(io_context)
{
    delay_milliseconds = 0; // 기본값 0ms
}

void DelayGameSession::AsyncWrite(const BufferPooledVector& data, size_t size)
{
    if (delay_milliseconds == 0)
    {
        // 지연이 없으면 기본 동작 수행
        PacketSession::AsyncWrite(data, size);
        return;
    }

    // 타이머를 사용하여 지연 구현
    auto _delay_timer = std::make_shared<boost::asio::steady_timer>(_strand);

    _delay_timer->expires_after(std::chrono::milliseconds(delay_milliseconds));
    _delay_timer->async_wait(
        asio::bind_executor(_strand,
            [_delay_timer, data, size, this, self = shared_from_this()](const boost::system::error_code& error)
            {
                if (!error)
                {
                    GameSession::AsyncWrite(data, size);
                }
                else
                {
                    spdlog::error("Timer error: {}", error.message());
                }
            }
        )
    );
}

void DelayGameSession::OnRead(const boost::system::error_code& err, size_t size)
{
    auto _delay_timer = std::make_shared<boost::asio::steady_timer>(_strand);

    _delay_timer->expires_after(std::chrono::milliseconds(delay_milliseconds));
    _delay_timer->async_wait(
        asio::bind_executor(_strand,
            [_delay_timer, self = shared_from_this(), this, err, size](const boost::system::error_code& error)
            {
                if (!error)
                {
                    GameSession::OnRead(err, size);
                    
                }
                else
                {
                    spdlog::error("Timer error: {}", error.message());
                }
            }
        )
    );
}

void DelayGameSession::SetDelay(int milliseconds)
{
    delay_milliseconds = milliseconds;
}

void DelayGameSession::SetDelayWithJitter(int base_milliseconds, int jitter_milliseconds)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> jitter(-jitter_milliseconds, jitter_milliseconds);

    int total_delay = std::max(0, base_milliseconds + jitter(gen));
    SetDelay(total_delay);
}
