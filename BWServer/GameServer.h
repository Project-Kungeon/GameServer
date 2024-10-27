#pragma once
#include "pch.h"
#include "TickGenerator.h"

class GameServer : public std::enable_shared_from_this<GameServer>
{
public:
	GameServer(asio::io_context& io_context, int port);
	void StartAccept();
	void OnAccept(SessionPtr session, const boost::system::error_code& err);

public:
	virtual void AsyncUdpRead();
	virtual void OnUdpRead(const boost::system::error_code& err, size_t size);
	virtual void AsyncUdpWrite(const char* message, size_t size);
	virtual void OnUdpWrite(const boost::system::error_code& err, size_t size);

	virtual void HandlePacket(char* ptr, size_t size);

private:
	tcp::acceptor _acceptor;
	asio::io_context& _io_context;

private:
	udp::socket _udp_socket;
	const static int UdpRecvBufferSize = 2048;
	char _udpRecvBuffer[UdpRecvBufferSize];
	const static int UdpSendBufferSize = 2048;
	char _udpSendBuffer[UdpSendBufferSize];
	asio::strand<asio::io_context::executor_type> _udp_strand;
};

typedef std::shared_ptr<GameServer> GameServerPtr;