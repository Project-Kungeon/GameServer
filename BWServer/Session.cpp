#include "pch.h"
#include "Session.h"

Session::Session(asio::io_context& io_context, Room& room)
	: _socket(io_context)
	, _room(room)
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
	_room.Join(this->shared_from_this());
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
	std::cout << "OnRead : " << size << '\n';
	if (!err)
	{
		HandlePacket(_recvBuffer, size);
		AsyncRead();
	}
	else
	{
		std::cout << "error code : " << err.value() << ", msg : " << err.message() << std::endl;
		//_room.Leave(this->shared_from_this());
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
		_room.Leave(this->shared_from_this());
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

void Session::HandleLoginReq(asio::mutable_buffer& buffer, const PacketHeader& header, int& offset)
{
	std::cout << "Receive LoginReq";
	message::LoginReq msg;
	PacketUtil::Parse(msg, buffer, buffer.size(), offset);

	message::LoginRes res;
	res.set_result(true);
	const size_t requiredSize = PacketUtil::RequiredSize(res);

	char* rawBuffer = new char[requiredSize];
	auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
	PacketUtil::Serialize(sendBuffer, message::MessageCode::LOGIN_RES, res);
	this->Send(sendBuffer);
}