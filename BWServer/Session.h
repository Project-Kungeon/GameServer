#pragma once
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/buffer.hpp>
#include "Room.h"
#include "Member.h"
#include "Packet.h"
#include "Message.pb.h"
#include <iostream>

using boost::asio::ip::tcp;
using namespace boost;

class Session
	: public Member
	, public boost::enable_shared_from_this<Session>
{
public:
	Session(asio::io_context& io_context, Room& room)
		: _socket(io_context)
		, _room(room)
		, _strand(asio::make_strand(io_context))
	{
		memset(_recvBuffer, 0, RecvBufferSize);
		memset(_sendBuffer, 0, SendBufferSize);
	}

	void Start()
	{
		_room.Join(this->shared_from_this());
		AsyncRead();
	}

	tcp::socket& GetSocket()
	{
		return _socket;
	}

	void Send(asio::mutable_buffer& buffer)
	{
		AsyncWrite(static_cast<const char*>(buffer.data()), buffer.size());
	}

protected:
	void AsyncRead()
	{
		std::cout << "Reading.." << '\n';
		memset(_recvBuffer, 0, RecvBufferSize);
		_socket.async_read_some(asio::buffer(_recvBuffer, RecvBufferSize), asio::bind_executor(_strand, boost::bind(&Session::OnRead, shared_from_this(),
			asio::placeholders::error,
			asio::placeholders::bytes_transferred
			)));
	}

	void OnRead(const boost::system::error_code& err, size_t size)
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

	void AsyncWrite(const char* message, size_t size)
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

	void OnWrite(const boost::system::error_code& err, size_t size)
	{
		// ������ �ڵ�
		if (!err)
		{

		}
		else
		{
			std::cout << "error code : " << err.value() << ", msg : " << err.message() << std::endl;
			_room.Leave(this->shared_from_this());
		}
	}

	void HandlePacket(char* ptr, size_t size)
	{
		asio::mutable_buffer buffer = asio::buffer(ptr, size);
		int offset = 0;
		PacketHeader header;
		PacketUtil::ParseHeader(buffer, &header, offset);

		std::cout << "HandlePacket : " << message::MessageCode_Name(header.Code) << '\n';
		switch (header.Code)
		{
		case message::MessageCode::LOGIN_REQ:
			HandleLoginReq(buffer, header, offset);
			break;
		default:
			break;
		}
	}

	void HandleLoginReq(asio::mutable_buffer& buffer, const PacketHeader& header, int& offset)
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
	



private:
	tcp::socket _socket;
	const static int RecvBufferSize = 1024;
	char _recvBuffer[RecvBufferSize];
	const static int SendBufferSize = 1024;
	char _sendBuffer[SendBufferSize];

	Room& _room;
	asio::strand<asio::io_context::executor_type> _strand;
};

typedef boost::shared_ptr<Session> SessionPtr;