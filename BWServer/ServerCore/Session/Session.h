#pragma once

#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio/buffer.hpp>
#include "Server/Room.h"
#include "Member.h"
#include "Network/Packet/Packet.h"
#include "Message.pb.h"
#include "Ping.pb.h"
#include "Network/Packet/Handlers/ServerPacketHandler.h"

using boost::asio::ip::tcp;
using boost::asio::ip::udp;
using namespace boost;

class Session;
typedef std::shared_ptr<Session> SessionPtr;

class Session
	: public Member
	, public std::enable_shared_from_this<Session>
{
public:
	Session(asio::io_context& io_context);
	SessionPtr GetSessionPtr();
public:
	static std::atomic<unsigned long long> packet_generated;
	
	void Start();
	tcp::socket& GetSocket();
	virtual void Send(asio::mutable_buffer& buffer);
	virtual void Send(std::shared_ptr<char[]> data, std::size_t size);
	virtual void Send(BufferPtr data, std::size_t size);

	// 의도적인 딜레이
	// Outgoing 전용
	virtual void DelaySend(asio::mutable_buffer& buffer, uint64 delay_milliseconds);

	virtual void HandlePing(const ping::C_Ping& pkt);
	virtual void HandleCompletePing(const ping::C_CompletePing& pkt);

protected:
	virtual void AsyncRead();
	virtual void OnRead(const boost::system::error_code& err, size_t size);
	virtual void AsyncWrite(const char* message, size_t size);
	//virtual void AsyncWrite(std::shared_ptr<char[]> message, size_t size);
	virtual void AsyncWrite(BufferPtr message, size_t size);
	virtual void OnWrite(BufferPtr message, const boost::system::error_code& err, size_t size);
	//virtual void OnWrite(std::shared_ptr<char[]> message, const boost::system::error_code& err, size_t size);
	virtual void OnWrite(const boost::system::error_code& err, size_t size);
	virtual void HandlePacket(char* ptr, size_t size);

	virtual void OnConnected() {};
	virtual void OnDisconnected() {};

protected:
	virtual void DelayAsyncWrite(const char* message, size_t size, uint64 delay_milliseconds);

private:
	uint64 _session_id;
	
protected:
	tcp::socket _socket;
	const static int RecvBufferSize = 2048;
	char _recvBuffer[RecvBufferSize];
	const static int SendBufferSize = 2048;
	char _sendBuffer[SendBufferSize];

	asio::strand<asio::io_context::executor_type> _strand;

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

private:
	// Outgoing 최대 지연 시간
	static const uint64 MAX_OUT_GOING_LATENCY = 250;
};

