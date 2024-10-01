#pragma once
#include "pch.h"
#include "TickGenerator.h"

class GameServer
{
public:
	GameServer(asio::io_context& io_context, int port);
	void StartAccept();
	void OnAccept(SessionPtr session, const boost::system::error_code& err);

private:
	tcp::acceptor _acceptor;
	asio::io_context& _io_context;
};

typedef std::shared_ptr<GameServer> GameServerPtr;