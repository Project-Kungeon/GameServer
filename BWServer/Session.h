#pragma once

#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio/buffer.hpp>
#include "Room.h"
#include "Member.h"
#include "Packet.h"
#include "Message.pb.h"
#include "ServerPacketHandler.h"

using boost::asio::ip::tcp;
using namespace boost;

class Session;
typedef std::shared_ptr<Session> SessionPtr;

class Session
	: public Member
	, public std::enable_shared_from_this<Session>
{
public:
	Session(asio::io_context& io_context, Room& room);
	SessionPtr GetSessionPtr();

	void Start();
	tcp::socket& GetSocket();

	virtual void Send(asio::mutable_buffer& buffer);

protected:
	void AsyncRead();
	void OnRead(const boost::system::error_code& err, size_t size);
	void AsyncWrite(const char* message, size_t size);
	void OnWrite(const boost::system::error_code& err, size_t size);
	void HandlePacket(char* ptr, size_t size);

	virtual void OnConnected() {};
	virtual void OnDisconnected() {};


private:
	tcp::socket _socket;
	const static int RecvBufferSize = 2048;
	char _recvBuffer[RecvBufferSize];
	const static int SendBufferSize = 2048;
	char _sendBuffer[SendBufferSize];

	Room& _room;
	asio::strand<asio::io_context::executor_type> _strand;
};

