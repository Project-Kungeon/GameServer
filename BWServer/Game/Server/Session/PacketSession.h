#pragma once
#include "Session/FixedSession.h"
#include "Ping.pb.h"

using SessionPtr = std::shared_ptr<class PacketSession>;

class PacketSession : public FixedSession
{
public:
    PacketSession(asio::io_context& ioc) : FixedSession(ioc) {};
    ~PacketSession() override;
    virtual SessionPtr GetSessionPtr() { return static_pointer_cast<PacketSession>(shared_from_this()); }

public:
    virtual void AsyncWrite(const BufferPooledVector& data, size_t size) override;
    void Start();

    virtual void SendPacket(google::protobuf::Message& msg, const short packetCode);
    virtual void HandlePing(const ping::C_Ping& pkt);
    virtual void HandleCompletePing(const ping::C_CompletePing& pkt);

protected:
    void OnPacket() override;

    // 핑 체크
protected:
    struct RTTStats
    {
        uint64 client_send_time;
        uint64 server_receive_time;
        uint64 server_send_time;
        uint64 client_receive_time;

        void PrintRttStats() const
        {
            uint64 total_rtt = client_receive_time - client_send_time;
            uint64 server_processing_time = server_send_time - server_receive_time;
            uint64 network_rtt = total_rtt - server_processing_time;
            spdlog::trace("Total RTT : {}", total_rtt);
        }
    };
    RTTStats _rtt_stats;

public:
    uint64 GetTotalRtt() { return _rtt_stats.client_receive_time - _rtt_stats.client_send_time; }
};
