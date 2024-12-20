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

void GameServer::UdpSend(asio::mutable_buffer& buffer)
{
	AsyncUdpWrite(static_cast<const char*>(buffer.data()), buffer.size());
}

void GameServer::UdpSend(std::shared_ptr<asio::mutable_buffer> buffer)
{
	AsyncUdpWrite(static_cast<const char*>(buffer->data()), buffer->size());
}

void GameServer::AsyncUdpRead()
{
	spdlog::trace("Udp Reading..");
	memset(_udpRecvBuffer, 0, UdpRecvBufferSize);
	_udp_socket.async_receive_from(asio::buffer(_udpRecvBuffer, UdpRecvBufferSize), _remote_endpoint, asio::bind_executor(_udp_strand, boost::bind(&GameServer::OnUdpRead, this,
		asio::placeholders::error,
		asio::placeholders::bytes_transferred
	)));

}

void GameServer::OnUdpRead(const boost::system::error_code& err, size_t size)
{
	if (!err)
	{  
		//spdlog::info("OnUdpRead IP: {}, Size: {}", addr, size);
		_udp_clients.insert(_remote_endpoint);
		HandlePacket(_udpRecvBuffer, size);
		AsyncUdpRead();
	}
	else
	{
		spdlog::error("error code : {}, msg : {}", err.value(), err.message());
		AsyncUdpRead();
	}

}

void GameServer::AsyncUdpWrite(const char* message, size_t size)
{
	memcpy(_udpSendBuffer, message, size);

	// 테스트용 유니캐스트
	for (auto& endpoint : _udp_clients)
	{
		_udp_socket.async_send_to(asio::buffer(_udpSendBuffer, size), endpoint,
			asio::bind_executor(_udp_strand, boost::bind(&GameServer::OnUdpWrite,
				shared_from_this(),
				asio::placeholders::error,
				asio::placeholders::bytes_transferred)
			));
	}
	

}

void GameServer::OnUdpWrite(const boost::system::error_code& err, size_t size)
{
	if (!err)
	{

	}
	else
	{
		std::cout << "error code : " << err.value() << ", msg : " << err.message() << std::endl;
		//_room.Leave(this->shared_from_this());
	}
}

void GameServer::HandlePacket(char* ptr, size_t size)
{
	ServerPacketHandler::HandleUdpPacket(ptr, size);
}
