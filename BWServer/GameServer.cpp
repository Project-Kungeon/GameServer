#include "pch.h"
#include "GameServer.h"

GameServer::GameServer(asio::io_context& io_context, int port)
	: _acceptor(io_context, tcp::endpoint(tcp::v4(), port))
	, _io_context(io_context)
{}

void GameServer::StartAccept()
{
	Session* session = new Session(_io_context, _room);
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
