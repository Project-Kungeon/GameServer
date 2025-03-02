#include "pch.h"
#include "FixedSession.h"

#include <spdlog/spdlog.h>

FixedSession::FixedSession(asio::io_context& io_context) : SessionBase(io_context)
{
    memset(_recvBuffer, 0, sizeof(_recvBuffer));
    memset(_sendBuffer, 0, sizeof(_sendBuffer));
}

FixedSession::~FixedSession()
{
}

void FixedSession::AsyncRead()
{
    AsyncHeaderRead();
}

void FixedSession::AsyncHeaderRead()
{
    // Header는 무조건 4바이트임.
    memset(_recvBuffer, 0, HeaderBufferSize);
    _offset = 0;
    asio::async_read(_socket,
        asio::buffer(_recvBuffer, HeaderBufferSize),
        asio::bind_executor(_strand,[this, self = shared_from_this()](const boost::system::error_code& error, const size_t bytes_transferred)
        {
            OnHeaderRead(error, bytes_transferred);
        }
        ));
}

void FixedSession::AsyncBodyRead()
{
    _recvBodyBuffer.clear();
    _recvBodyBuffer.resize(_header.Length);
    
    asio::async_read(_socket,
        asio::buffer(_recvBodyBuffer.data(), _recvBodyBuffer.size()),
        asio::bind_executor(_strand,[this, self = shared_from_this()](const boost::system::error_code& error, const size_t bytes_transferred)
        {
            OnBodyRead(error, bytes_transferred);
        }
        ));
}

void FixedSession::AsyncWrite(const BufferPooledVector& data, size_t size)
{
    auto data_ptr = std::make_shared<BufferPooledVector>(data);
    
    async_write(_socket,
        asio::buffer(data_ptr->data(), data_ptr->size()),
        bind_executor(_strand,[data_ptr, this, self = shared_from_this()](const boost::system::error_code& error, const size_t bytes_transferred)
        {
            OnWrite(error, bytes_transferred);
        }));
}

void FixedSession::DelayAsyncWrite(BufferPooledVector& buffer, size_t size, uint64 delay_milliseconds)
{
    auto _delay_timer = std::make_shared<boost::asio::steady_timer>(_strand);

    _delay_timer->expires_after(std::chrono::milliseconds(MAX_OUT_GOING_LATENCY > delay_milliseconds ? delay_milliseconds : MAX_OUT_GOING_LATENCY));
    _delay_timer->async_wait(
        asio::bind_executor(_strand,
            [_delay_timer, self = shared_from_this(), this, buffer, size](const boost::system::error_code& error)
            {
                if (!error)
                {
                    AsyncWrite(buffer, size);
                }
                else
                {
                    spdlog::error("Timer error: {}", error.message());
                }
            }
        )
    );
}

void FixedSession::OnHeaderRead(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (!error)
    {
        spdlog::trace("Received Header bytes {}", bytes_transferred);
        OnHeader();
    }
    else
    {
        spdlog::error("Header Read Error : {}", error.message());
    }
}

void FixedSession::OnBodyRead(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (!error)
    {
        spdlog::trace("Received Body bytes {}", bytes_transferred);
        OnPacket();
        AsyncHeaderRead();
    }
    else
    {
        spdlog::error("body Read Error : {}", error.value());
    }
}

void FixedSession::OnHeader()
{
    // Header Packet Deserializa
    asio::mutable_buffer buffer = asio::buffer(_recvBuffer, HeaderBufferSize);

    if (PacketUtil::ParseHeader(buffer, &_header, _offset))
    {
        spdlog::trace("Received Header info -> Code : {}, Length : {}", _header.Code, _header.Length);
        AsyncBodyRead();
        
    }
    else
    {
        spdlog::error("Failed to parse Header..");
    }
}

/*void FixedSession::OnPacket()
{
    // ...
    
}*/

// Will be deprecated
void FixedSession::OnRead(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (!error)
    {
        spdlog::info("Received bytes {}", bytes_transferred);
    }
    else
    {
        spdlog::error("Read Error : {}", error.value());
    }

}

void FixedSession::OnWrite(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (!error)
    {
        spdlog::trace("Write bytes {}", bytes_transferred);
    }
    else
    {
        spdlog::error("Write Error : {}", error.value());
    }
}

void FixedSession::OnConnected()
{
    SessionBase::OnConnected();
}

void FixedSession::OnDisConnected()
{
    SessionBase::OnDisConnected();
}
