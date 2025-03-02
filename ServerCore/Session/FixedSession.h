#pragma once

#include "SessionBase.h"
#include "../Packet.h"

/*
 * 버퍼 크기가 고정된 세션
 */

class FixedSession : public SessionBase
{
public:
    FixedSession(asio::io_context& io_context);
    ~FixedSession() override;

protected:
    void AsyncRead() override;
    void AsyncHeaderRead();
    void AsyncBodyRead();
    virtual void AsyncWrite(const BufferPooledVector& data, size_t size) override;
    virtual void DelayAsyncWrite(BufferPooledVector& buffer, size_t size, uint64 delay_milliseconds) override;

    void OnHeaderRead(const boost::system::error_code& error, size_t bytes_transferred);
    void OnBodyRead(const boost::system::error_code& error, size_t bytes_transferred);
    void OnHeader();
    virtual void OnPacket() = 0;
    
    void OnRead(const boost::system::error_code& error, size_t bytes_transferred) override;
    void OnWrite(const boost::system::error_code& error, size_t bytes_transferred) override;
    void OnConnected() override;    
    void OnDisConnected() override;

public:
    static BufferAllocator readBufferAllocator;
    
protected:
    PacketHeader _header;
    int _offset;
    BufferPooledVector _recvBodyBuffer;
    
private:
    const static size_t RecvBufferSize = 4;
    const static size_t SendBufferSize = 1024;
    const static size_t HeaderBufferSize = 4;
    char _recvBuffer[RecvBufferSize];
    char _sendBuffer[SendBufferSize];

    // Outgoing 최대 지연 시간
    static const uint64 MAX_OUT_GOING_LATENCY = 250;
};
