#pragma once
#include "pch.h"
#include "Player.h"
#include <memory>

class GameSession : public Session
{
public:
	GameSession(asio::io_context& io_context)
		: Session(io_context)
	{};

	virtual void OnConnected() override;
	virtual void OnDisconnected() override;

public:
	bool isEnterGame = false;
	atomic<std::shared_ptr<Player>> player;
	
};

