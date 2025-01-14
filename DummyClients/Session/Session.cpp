#include "pch.h"
#include "Session.h"

std::atomic<unsigned long long> Session::packet_generated = 0;
std::atomic<uint64> Session::_email_id = 0;

Session::Session(asio::io_context& io_context, const std::string& host, int port)
	: _socket(io_context)
	, _strand(asio::make_strand(io_context))
{
	_endpoint = tcp::endpoint(asio::ip::make_address(host), port);
	memset(_recvBuffer, 0, RecvBufferSize);
	memset(_sendBuffer, 0, SendBufferSize);
}

SessionPtr Session::GetSessionPtr()
{
	return static_pointer_cast<Session>(shared_from_this());
}

void Session::Connect()
{
	_socket.async_connect(_endpoint, boost::bind(&Session::OnConnected, this, asio::placeholders::error));
}

tcp::socket& Session::GetSocket()
{
	return _socket;
}

void Session::Send(asio::mutable_buffer& buffer)
{
	AsyncWrite(static_cast<const char*>(buffer.data()), buffer.size());
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

void Session::AsyncHeaderRead()
{
	spdlog::trace("Header Reading..");
	memset(_headerBuffer, 0, HeaderSize);
	boost::asio::async_read(_socket, asio::buffer(_headerBuffer, HeaderSize),
		asio::bind_executor(
			_strand, [this](boost::system::error_code ec, std::size_t length)
			{
				OnHeaderRead(ec, length);
			}
	));
}

void Session::AsyncBodyRead()
{
	spdlog::trace("Body Reading..");
	std::shared_ptr<char[]> bufferPtr = std::make_shared<char[]>(header.Length);
	memset(bufferPtr.get(), 0, header.Length);

	boost::asio::async_read(_socket, asio::buffer(bufferPtr.get(), header.Length),
		asio::bind_executor(
			_strand, [this, bufferPtr](boost::system::error_code ec, std::size_t length)
			{
				OnBodyRead(ec, bufferPtr, length);
			}
	));
}

void Session::OnHeaderRead(const boost::system::error_code& err, size_t size)
{
	if (!err)
	{
		asio::mutable_buffer buffer = asio::buffer(_headerBuffer, HeaderSize);
		PacketUtil::ParseHeader(buffer, &header, _offset);
		AsyncBodyRead();
	}
	else
	{
		
	}
}

void Session::OnBodyRead(const boost::system::error_code& err, std::shared_ptr<char[]> bufferPtr, size_t size)
{
	if (!err)
	{
		std::string addr = GetSocket().remote_endpoint().address().to_string();
		spdlog::trace("OnRead IP: {}, Size: {}", addr, size);
		SessionPtr session = this->GetSessionPtr();
		GPacketHandler[header.Code](session, bufferPtr, header, _offset);
		_offset = 0;
		Session::packet_generated.fetch_add(1);
		AsyncHeaderRead();
	}
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
	memcpy(_sendBuffer, message, size);
	asio::async_write(_socket,
		asio::buffer(_sendBuffer, size),
		asio::bind_executor(_strand, boost::bind(&Session::OnWrite,
			shared_from_this(),
			asio::placeholders::error,
			asio::placeholders::bytes_transferred)
		)
	);
}

void Session::OnWrite(const boost::system::error_code& err, size_t size)
{
	if (!err)
	{

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
	//ClientPacketHandler::HandlePacket(session, ptr, size);
}

void Session::OnConnected(const boost::system::error_code& err)
{
	if (!err)
	{
		spdlog::trace("Connected!");
		account::login::C_Login loginPkt;
		uint64 email_id = _email_id.load();
		_email_id.fetch_add(1);
		loginPkt.add_email("test" + std::to_string(email_id) + "@test.com");
		loginPkt.add_password("test123");

		const size_t requiredSize = PacketUtil::RequiredSize(loginPkt);

		char* rawBuffer = new char[requiredSize];
		auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
		PacketUtil::Serialize(sendBuffer, message::HEADER::LOGIN_REQ, loginPkt);
		this->Send(sendBuffer);
		AsyncHeaderRead();
	}
	else
	{
		spdlog::error("{}", err.message());
	}
}
