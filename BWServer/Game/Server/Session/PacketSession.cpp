#include "pch.h"
#include "PacketSession.h"

#include "Packet/Handlers/ServerPacketHandler.h"

PacketSession::~PacketSession()
{}

void PacketSession::AsyncWrite(const BufferPooledVector& data, size_t size)
{
    FixedSession::AsyncWrite(data, size);
}

void PacketSession::Start()
{
    AsyncRead();
}

void PacketSession::SendPacket(google::protobuf::Message& msg, const short packetCode)
{
    auto bufSize = PacketUtil::RequiredSize(msg);
    BufferPooledVector vector_buffer(bufSize);
    PacketUtil::Serialize(asio::buffer(vector_buffer), packetCode, msg);
    Send(vector_buffer, bufSize);
}


void PacketSession::HandlePing(const ping::C_Ping& pkt)
{
    // 서버 -> 클라 통신 시간 기록
    uint64 server_receive_time = TimeUtils::GetSystemTimestamoMillisec();

    _rtt_stats.client_send_time = pkt.client_send_time();
    _rtt_stats.server_receive_time = server_receive_time;

    // Pong 메세지 만들기
    ping::S_Pong PongPkt;
    PongPkt.set_client_send_time(pkt.client_send_time());
    PongPkt.set_sequence_number(pkt.sequence_number());
    PongPkt.set_server_receive_time(server_receive_time);

    uint64 server_send_time = TimeUtils::GetSystemTimestamoMillisec();
    PongPkt.set_server_send_time(server_send_time);
    _rtt_stats.server_send_time = server_send_time;
    
    SendPacket(PongPkt, message::HEADER::SESSION_PONG_RES);
    
}

void PacketSession::HandleCompletePing(const ping::C_CompletePing& pkt)
{
    // 핑 - 퐁해서 얻은 결과를 클라이언트가 서버에게 전달해줌.
    _rtt_stats.client_receive_time = pkt.client_receive_time();

    // RTT 계산결과 trace로 출력
    _rtt_stats.PrintRttStats();
}

void PacketSession::OnPacket()
{

    /*std::string addr = GetSocket().remote_endpoint().address().to_string();
    spdlog::trace("OnRead IP: {}, Size: {}", addr, size);*/
    
    SessionPtr session = this->GetSessionPtr();
    ServerPacketHandler::HandlePacket(session, _header, reinterpret_cast<char*>(_recvBodyBuffer.data()), _recvBodyBuffer.size());
    _offset = 0;
    
}
