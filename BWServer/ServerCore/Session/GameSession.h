#pragma once
#include "pch.h"
#include "Objects/Creatures/Players/Player.h"
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

public:
	void AssignSessionId();
	
private:
	std::string _session_id;

public:
	std::string session_id() const
	{
		return _session_id;
	}
};

