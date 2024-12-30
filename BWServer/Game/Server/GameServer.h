#pragma once
#include "pch.h"

struct EndpointHash 
{
	std::size_t operator()(const udp::endpoint& endpoint) const 
	{
		return std::hash<std::string>()(endpoint.address().to_string()) ^ std::hash<unsigned short>()(endpoint.port());
	}
};

class GameServer : public std::enable_shared_from_this<GameServer>
{
public:
	GameServer(asio::io_context& io_context, int port);
	virtual void StartAccept();
	virtual void OnAccept(SessionPtr session, const boost::system::error_code& err);

protected:
	tcp::acceptor _acceptor;
	asio::io_context& _io_context;

protected:
	udp::socket _udp_socket;
	const static int UdpRecvBufferSize = 2048;
	char _udpRecvBuffer[UdpRecvBufferSize];
	const static int UdpSendBufferSize = 2048;
	char _udpSendBuffer[UdpSendBufferSize];
	asio::strand<asio::io_context::executor_type> _udp_strand;
	udp::endpoint _remote_endpoint;

	// TEST : UDP 엔드포인트 집합
	std::unordered_set<udp::endpoint, EndpointHash> _udp_clients;
};

typedef std::shared_ptr<GameServer> GameServerPtr;