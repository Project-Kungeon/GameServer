#include "pch.h"
#include "Session.h"

std::atomic<unsigned long long> Session::packet_generated = 0;

Session::Session(asio::io_context& io_context)
	: _socket(io_context)
	, _strand(asio::make_strand(io_context))
{
	memset(_recvBuffer, 0, RecvBufferSize);
	memset(_sendBuffer, 0, SendBufferSize);
}

SessionPtr Session::GetSessionPtr()
{
	return static_pointer_cast<Session>(shared_from_this());
}

void Session::Start()
{
	//_room.Join(this->shared_from_this());
	AsyncRead();
}

tcp::socket& Session::GetSocket()
{
	return _socket;
}

void Session::Send(asio::mutable_buffer& buffer)
{
	AsyncWrite(static_cast<const char*>(buffer.data()), buffer.size());
}

void Session::Send(std::shared_ptr<char[]> data, std::size_t size)
{
	//AsyncWrite(data, size);
}

void Session::Send(BufferPtr data, std::size_t size)
{
	AsyncWrite(data, size);
}

void Session::DelaySend(asio::mutable_buffer& buffer, uint64 delay_milliseconds)
{
	DelayAsyncWrite(static_cast<const char*>(buffer.data()), buffer.size(), delay_milliseconds);
}

void Session::HandlePing(const ping::C_Ping& pkt)
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

	const size_t requiredSize = PacketUtil::RequiredSize(PongPkt);
	char* rawBuffer = new char[requiredSize];
	auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
	PacketUtil::Serialize(sendBuffer, message::HEADER::SESSION_PONG_RES, PongPkt);

	Send(sendBuffer);
}

void Session::HandleCompletePing(const ping::C_CompletePing& pkt)
{
	// 핑 - 퐁해서 얻은 결과를 클라이언트가 서버에게 전달해줌.
	_rtt_stats.client_receive_time = pkt.client_receive_time();

	// RTT 계산결과 trace로 출력
	_rtt_stats.PrintRttStats();
}

void Session::AsyncRead()
{
	spdlog::trace("Tcp Reading..");
	memset(_recvBuffer, 0, RecvBufferSize);
	_socket.async_read_some(asio::buffer(_recvBuffer, RecvBufferSize), asio::bind_executor(_strand, boost::bind(&Session::OnRead, shared_from_this(),
		asio::placeholders::error,
		asio::placeholders::bytes_transferred
	)));
}

void Session::OnRead(const boost::system::error_code& err, size_t size)
{
	//std::cout << "OnRead : " << size << '\n';
	if (!err)
	{
		std::string addr = GetSocket().remote_endpoint().address().to_string();
		spdlog::info("OnRead IP: {}, Size: {}", addr, size);
		HandlePacket(_recvBuffer, size);
		AsyncRead();
	}
	else
	{
		spdlog::error("error code : {}, msg : {}", err.value(), err.message());
	}
}

void Session::AsyncWrite(const char* message, size_t size)
{
	// memcpy(_sendBuffer, message, size);
	asio::async_write(_socket,
		asio::buffer(message, size),
		asio::bind_executor(_strand, boost::bind(&Session::OnWrite,
			shared_from_this(),
			asio::placeholders::error,
			asio::placeholders::bytes_transferred)
		)
	);
}

/*
void Session::AsyncWrite(std::shared_ptr<char[]> message, size_t size)
{
	asio::async_write(_socket,
		asio::buffer(message.get(), size),
		asio::bind_executor(_strand, boost::bind(&Session::OnWrite,
			shared_from_this(),
			message,
			asio::placeholders::error,
			asio::placeholders::bytes_transferred)
		)
	);
}
*/

void Session::AsyncWrite(BufferPtr message, size_t size)
{
	auto self = GetSessionPtr();
	asio::async_write(_socket,
		asio::buffer(message.get(), size),
		asio::bind_executor(_strand,
			[self, message](boost::system::error_code ec, std::size_t length)
			{
				// message를 람다 캡처한 이유는 비동기 IO가 끝날 때까지 생명 유지를 해야 되기 때문이다.
				self->OnWrite(message, ec, length);
			})
	);
}

void Session::OnWrite(BufferPtr message, const boost::system::error_code& err, size_t size)
{
	if (!err)
	{
		packet_generated.fetch_add(1);
	}
	else
	{
		std::cout << "error code : " << err.value() << ", msg : " << err.message() << std::endl;
		//_room.Leave(this->shared_from_this());
	}
}

/*void Session::OnWrite(std::shared_ptr<char[]> message, const boost::system::error_code& err, size_t size)
{
	if (!err)
	{
		
	}
	else
	{
		std::cout << "error code : " << err.value() << ", msg : " << err.message() << std::endl;
		//_room.Leave(this->shared_from_this());
	}
}*/

void Session::OnWrite(const boost::system::error_code& err, size_t size)
{
	if (!err)
	{
		packet_generated.fetch_add(1);
	}
	else
	{
		std::cout << "error code : " << err.value() << ", msg : " << err.message() << std::endl;
		//_room.Leave(this->shared_from_this());
	}
}

void Session::HandlePacket(char* ptr, size_t size)
{
	SessionPtr session = this->GetSessionPtr();
	ServerPacketHandler::HandlePacket(session, ptr, size);
}

void Session::DelayAsyncWrite(const char* message, size_t size, uint64 delay_milliseconds)
{
	// 타이머를 사용하여 지연 구현
	auto _delay_timer = std::make_shared<boost::asio::steady_timer>(_strand);

	_delay_timer->expires_after(std::chrono::milliseconds(MAX_OUT_GOING_LATENCY > delay_milliseconds ? delay_milliseconds : MAX_OUT_GOING_LATENCY));
	_delay_timer->async_wait(
		asio::bind_executor(_strand,
			[_delay_timer, self = shared_from_this(), this, message, size](const boost::system::error_code& error)
			{
				if (!error)
				{
					AsyncWrite(message, size);
				}
				else
				{
					spdlog::error("Timer error: {}", error.message());
				}
			}
		)
	);
}