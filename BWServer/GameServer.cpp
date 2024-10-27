#include "pch.h"
#include "GameServer.h"

GameServer::GameServer(asio::io_context& io_context, int port)
	: _acceptor(io_context, tcp::endpoint(tcp::v4(), port))
	, _io_context(io_context)
	, _udp_socket(io_context, udp::endpoint(udp::v4(), port))
	, _udp_strand(asio::make_strand(io_context))
{
	 //_tickGenerator.start(nullptr);
	AsyncUdpRead();
}

void GameServer::StartAccept()
{
	//GameSession* session = new GameSession(_io_context);
	DelayGameSession* session = new DelayGameSession(_io_context);
	session->SetDelay(1000);
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

void GameServer::AsyncUdpRead()
{
	spdlog::trace("Udp Reading..");
	memset(_udpRecvBuffer, 0, UdpRecvBufferSize);
	_udp_socket.async_receive(asio::buffer(_udpRecvBuffer, UdpRecvBufferSize), asio::bind_executor(_udp_strand, boost::bind(&GameServer::OnUdpRead, this,
		asio::placeholders::error,
		asio::placeholders::bytes_transferred
	)));

}

void GameServer::OnUdpRead(const boost::system::error_code& err, size_t size)
{
	if (!err)
	{
		//spdlog::info("OnUdpRead IP: {}, Size: {}", addr, size);
		HandlePacket(_udpRecvBuffer, size);
		AsyncUdpRead();
	}
	else
	{
		spdlog::error("error code : {}, msg : {}", err.value(), err.message());
	}

}

void GameServer::AsyncUdpWrite(const char* message, size_t size)
{
}

void GameServer::OnUdpWrite(const boost::system::error_code& err, size_t size)
{
}

void GameServer::HandlePacket(char* ptr, size_t size)
{
}
