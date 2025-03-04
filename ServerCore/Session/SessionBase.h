#pragma once
#include <google/protobuf/message.h>

#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/pool/pool_alloc.hpp>

using boost::asio::ip::tcp;
using boost::asio::ip::udp;
using namespace boost;

namespace
{
    using BufferAllocator = pool_allocator<char>;
    using BufferPooledVector = std::vector<char, BufferAllocator>;

}

class SessionBase : public std::enable_shared_from_this<SessionBase>
{
public:
    SessionBase(asio::io_context& io_context) : _socket(io_context), _strand(asio::make_strand(io_context)) {};
    virtual ~SessionBase() {};
    tcp::socket& GetSocket() { return _socket; }

    void DelaySend(BufferPooledVector& buffer, size_t size, uint64 delay_milliseconds)
    {
        DelayAsyncWrite(buffer, size, delay_milliseconds);
    }
    void Send(BufferPooledVector& buffer, size_t size)
    {
        AsyncWrite(buffer, size);
    };



protected:
    virtual void AsyncRead() = 0;
    virtual void AsyncWrite(const BufferPooledVector& data, size_t size) = 0;
    virtual void DelayAsyncWrite(BufferPooledVector& buffer, size_t size, uint64 delay_milliseconds) = 0;
    virtual void OnRead(const boost::system::error_code& error, size_t bytes_transferred) = 0;
    virtual void OnWrite(const boost::system::error_code& error, size_t bytes_transferred) = 0;

    virtual void OnConnected() {};
    virtual void OnDisConnected() {};

protected:
    tcp::socket _socket;
    asio::strand<asio::io_context::executor_type> _strand;

};
