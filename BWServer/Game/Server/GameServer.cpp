#include "pch.h"
#include "GameServer.h"

GameServer::GameServer(asio::io_context& io_context, int port)
	: _acceptor(io_context, tcp::endpoint(tcp::v4(), port))
	, _io_context(io_context)
	, _udp_socket(io_context, udp::endpoint(udp::v4(), port))
	, _udp_strand(asio::make_strand(io_context))
{
	 //_tickGenerator.start(nullptr);
	/*AsyncUdpRead();*/
}

void GameServer::StartAccept()
{
	//GameSession* session = new GameSession(_io_context);
	GameSession* session = new GameSession(_io_context);
	SessionPtr sessionPtr(session);
	_acceptor.async_accept(sessionPtr->GetSocket(), boost::bind(
		&GameServer::OnAccept,
		this,
		sessionPtr,
		boost::asio::placeholders::error
	)
	);
}

void GameServer::OnAccept(SessionPtr session, const boost::system::error_code& err)
{
	if (!err)
	{
		spdlog::info("Session Connected");
		session->Start();
	}
	StartAccept();
}
