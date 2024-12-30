#include "pch.h"
#include "DelayGameServer.h"

DelayGameServer::DelayGameServer(asio::io_context& io_context, int port)
    : GameServer(io_context, port)
{
}

void DelayGameServer::SetDelay(int milliseconds)
{
    delay_milliseconds = milliseconds;
}

void DelayGameServer::SetLossRate(double rate)
{
    loss_rate = rate;
}

void DelayGameServer::SetDelayWithJitter(int base_milliseconds, int jitter_milliseconds)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> jitter(-jitter_milliseconds, jitter_milliseconds);

    int total_delay = std::max(0, base_milliseconds + jitter(gen));
    SetDelay(total_delay);
}

void DelayGameServer::StartAccept()
{
	DelayGameSession* session = new DelayGameSession(_io_context);
    if (session_nums % 2 == 0)
    {
        session->SetDelay(0);
    }
    else
    {
        session->SetDelay(delay_milliseconds);
    }
	
	SessionPtr sessionPtr(session);
	_acceptor.async_accept(sessionPtr->GetSocket(), boost::bind(
		&GameServer::OnAccept,
		this,
		sessionPtr,
		boost::asio::placeholders::error
	)
	);
    session_nums++;
}
