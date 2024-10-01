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
	Room _room;
	asio::io_context& _io_context;
	asio::strand<asio::io_context::executor_type> _strand;
	TickGenerator _tickGenerator;
};

typedef std::shared_ptr<GameServer> GameServerPtr;