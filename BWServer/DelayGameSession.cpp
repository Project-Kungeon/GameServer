#include "pch.h"
#include "DelayGameSession.h"

DelayGameSession::DelayGameSession(asio::io_context& io_context)
    : GameSession(io_context)
{
    delay_milliseconds = 0; // 기본값 0ms
}

void DelayGameSession::AsyncWrite(const char* message, size_t size)
{
    if (delay_milliseconds == 0)
    {
        // 지연이 없으면 기본 동작 수행
        Session::AsyncWrite(message, size);
        return;
    }

    // 메시지를 임시 버퍼에 복사
    
    const size_t message_size = size;

    // 타이머를 사용하여 지연 구현
    auto _delay_timer = std::make_shared<boost::asio::steady_timer>(_strand);

    _delay_timer->expires_after(std::chrono::milliseconds(delay_milliseconds));
    _delay_timer->async_wait(
        asio::bind_executor(_strand,
            [_delay_timer, self = shared_from_this(), this, message, size](const boost::system::error_code& error)
            {
                if (!error)
                {
                    //memcpy(_sendBuffer, message, size);
                    //// 지연 후 실제 전송
                    //spdlog::trace("DelayGameSession : {} milliseconds delayed", delay_milliseconds);
                    //asio::async_write(_socket,
                    //    asio::buffer(_sendBuffer, message_size),
                    //    asio::bind_executor(_strand,
                    //        boost::bind(&DelayGameSession::OnWrite,
                    //            shared_from_this(),
                    //            asio::placeholders::error,
                    //            asio::placeholders::bytes_transferred)
                    //    )
                    //);
                    GameSession::AsyncWrite(message, size);
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
