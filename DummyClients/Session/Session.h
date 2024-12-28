#pragma once

#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio/buffer.hpp>

using boost::asio::ip::tcp;
using boost::asio::ip::udp;
using namespace boost;

class Session;
typedef std::shared_ptr<Session> SessionPtr;

class Session : public std::enable_shared_from_this<Session>
{
public:
	Session(asio::io_context& io_context, const std::string& host, int port);
	SessionPtr GetSessionPtr();

	void Connect();
	tcp::socket& GetSocket();
	virtual void Send(asio::mutable_buffer& buffer);

	virtual void HandlePing(const ping::C_Ping& pkt);
	virtual void HandleCompletePing(const ping::C_CompletePing& pkt);

protected:
	virtual void AsyncRead();
	virtual void OnRead(const boost::system::error_code& err, size_t size);
	virtual void AsyncWrite(const char* message, size_t size);
	virtual void OnWrite(const boost::system::error_code& err, size_t size);
	virtual void HandlePacket(char* ptr, size_t size);

	virtual void OnConnected(const boost::system::error_code& err);
	virtual void OnDisconnected() {};

private:
	uint64 _session_id;
	
protected:
	tcp::socket _socket;
	const static int RecvBufferSize = 2048;
	char _recvBuffer[RecvBufferSize];
	const static int SendBufferSize = 2048;
	char _sendBuffer[SendBufferSize];

	asio::strand<asio::io_context::executor_type> _strand;
	tcp::endpoint _endpoint;

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

