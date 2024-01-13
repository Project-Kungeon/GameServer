#pragma once
#include "Session.h"

class GameServer
{
public:
	GameServer(asio::io_context& io_context, int port)
		: _acceptor(io_context, tcp::endpoint(tcp::v4(), port))
		, _io_context(io_context)
	{}

	void StartAccept()
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

	void OnAccept(SessionPtr session, const boost::system::error_code& err)
	{
		if (!err)
		{
			std::cout << "Connected " << '\n';
			session->Start();
		}
		StartAccept();
	}

private:
	tcp::acceptor _acceptor;
	Room _room;
	asio::io_context& _io_context;
};