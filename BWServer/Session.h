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

	void Start();
	tcp::socket& GetSocket();
	virtual void Send(asio::mutable_buffer& buffer);

protected:
	virtual void AsyncRead();
	virtual void OnRead(const boost::system::error_code& err, size_t size);
	virtual void AsyncWrite(const char* message, size_t size);
	virtual void OnWrite(const boost::system::error_code& err, size_t size);
	virtual void HandlePacket(char* ptr, size_t size);

	virtual void OnConnected() {};
	virtual void OnDisconnected() {};


protected:
	tcp::socket _socket;
	const static int RecvBufferSize = 2048;
	char _recvBuffer[RecvBufferSize];
	const static int SendBufferSize = 2048;
	char _sendBuffer[SendBufferSize];

	asio::strand<asio::io_context::executor_type> _strand;


};

