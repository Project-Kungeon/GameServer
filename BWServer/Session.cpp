#include "pch.h"
#include "Session.h"

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

void Session::AsyncRead()
{
	std::cout << "Reading.." << '\n';
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
	ServerPacketHandler::HandlePacket(session, ptr, size);


	//asio::mutable_buffer buffer = asio::buffer(ptr, size);
	//int offset = 0;
	//PacketHeader header;
	//PacketUtil::ParseHeader(buffer, &header, offset);

	//std::cout << "HandlePacket : " << message::MessageCode_Name(header.Code) << '\n';
	//switch (header.Code)
	//{
	//case message::MessageCode::LOGIN_REQ:
	//	LobbyPacketHandler::Handle_C_Login(session, buffer, header, offset);
	//	//HandleLoginReq(buffer, header, offset);
	//	break;
	//default:
	//	break;
	//}
}
