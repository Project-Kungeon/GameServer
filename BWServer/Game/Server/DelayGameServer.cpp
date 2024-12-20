#include "pch.h"
#include "DelayGameServer.h"

DelayGameServer::DelayGameServer(asio::io_context& io_context, int port)
    : GameServer(io_context, port)
{
}

void DelayGameServer::SetDelay(int milliseconds)
{
    delay_milliseconds = milliseconds;
}

void DelayGameServer::SetLossRate(double rate)
{
    loss_rate = rate;
}

void DelayGameServer::SetDelayWithJitter(int base_milliseconds, int jitter_milliseconds)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> jitter(-jitter_milliseconds, jitter_milliseconds);

    int total_delay = std::max(0, base_milliseconds + jitter(gen));
    SetDelay(total_delay);
}

void DelayGameServer::StartAccept()
{
	DelayGameSession* session = new DelayGameSession(_io_context);
    if (session_nums % 2 == 0)
    {
        session->SetDelay(0);
    }
    else
    {
        session->SetDelay(delay_milliseconds);
    }
	
	SessionPtr sessionPtr(session);
	_acceptor.async_accept(sessionPtr->GetSocket(), boost::bind(
		&GameServer::OnAccept,
		this,
		sessionPtr,
		boost::asio::placeholders::error
	)
	);
    session_nums++;
}

void DelayGameServer::UdpSend(asio::mutable_buffer& buffer)
{
    GameServer::UdpSend(buffer);

    //if (delay_milliseconds == 0)
    //{
    //    // 지연이 없으면 기본 동작 수행
    //    GameServer::UdpSend(buffer);
    //    return;
    //}

    //// 타이머를 사용하여 지연 구현
    //auto _buffer = std::make_shared< asio::mutable_buffer>(buffer);
    //auto _delay_timer = std::make_shared<boost::asio::steady_timer>(_udp_strand);

    //_delay_timer->expires_after(std::chrono::milliseconds(delay_milliseconds));
    //_delay_timer->async_wait(
    //    asio::bind_executor(_udp_strand,
    //        [_delay_timer, self = shared_from_this(), this, _buffer](const boost::system::error_code& error)
    //        {
    //            if (!error)
    //            {
    //                GameServer::UdpSend(_buffer);
    //            }
    //            else
    //            {
    //                spdlog::error("Timer error: {}", error.message());
    //            }
    //        }
    //    )
    //);
}

void DelayGameServer::AsyncUdpWrite(const char* message, size_t size)
{
    memcpy(_udpSendBuffer, message, size);
    int i = 0;
    // 테스트용 유니캐스트
    for (auto& endpoint : _udp_clients)
    {
        if (i % 2 == 1)
        {
            // 홀수번째 클라이언트는 손실 적용.
            bool IsPacketLoss = shouldDropPacket();
            if (IsPacketLoss)
            {
                spdlog::trace("UDP Packet Loss!");
            }
            else
            {
                // 타이머를 사용하여 지연 구현
                auto _delay_timer = std::make_shared<boost::asio::steady_timer>(_udp_strand);
                _delay_timer->expires_after(std::chrono::milliseconds(delay_milliseconds));
                _delay_timer->async_wait(
                    asio::bind_executor(_udp_strand,
                        [_delay_timer, self = shared_from_this(), this, endpoint, size](const boost::system::error_code& error)
                        {
                            if (!error)
                            {
                                _udp_socket.async_send_to(asio::buffer(_udpSendBuffer, size), endpoint,
                                    asio::bind_executor(_udp_strand, boost::bind(&GameServer::OnUdpWrite,
                                        shared_from_this(),
                                        asio::placeholders::error,
                                        asio::placeholders::bytes_transferred)
                                    ));
                            }
                            else
                            {
                                spdlog::error("Timer error: {}", error.message());
                            }
                        }
                    )
                );
            }
        }
        else
        {
            _udp_socket.async_send_to(asio::buffer(_udpSendBuffer, size), endpoint,
                asio::bind_executor(_udp_strand, boost::bind(&GameServer::OnUdpWrite,
                    shared_from_this(),
                    asio::placeholders::error,
                    asio::placeholders::bytes_transferred)
                ));
        }
        i++;
    }
    
}
