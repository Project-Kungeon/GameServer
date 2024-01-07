#pragma once
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/buffer.hpp>
#include "Room.h"
#include "Member.h"

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
		
	}

	tcp::socket& GetSocket()
	{
		return _socket;
	}

	void Send(asio::mutable_buffer& buffer)
	{

	}

protected:
	void AsyncRead()
	{
		memset(_recvBuffer, 0, RecvBufferSize);
		_socket.async_read_some(asio::buffer(_recvBuffer, RecvBufferSize), asio::bind_executor(_strand, boost::bind(&Session::OnRead, this,
			asio::placeholders::error,
			asio::placeholders::bytes_transferred
			)));
	}

	void OnRead(const boost::system::error_code& err, size_t size)
	{
		// ������ �ڵ�
	}

	void AsyncWrite(const char* message, size_t size)
	{
		memcpy(_sendBuffer, message, size);
		asio::async_write(_socket,
			asio::buffer(_sendBuffer, size),
			asio::bind_executor(_strand, boost::bind(&Session::OnWrite,
				this,
				asio::placeholders::error,
				asio::placeholders::bytes_transferred)
			)
		);

	}

	void OnWrite(const boost::system::error_code& err, size_t size)
	{
		// ������ �ڵ�
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

