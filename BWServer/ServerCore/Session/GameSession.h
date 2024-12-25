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
	void SetUserPk(uint64 userPk) { _user_pk = userPk; }
	
private:
	std::string _session_id;
	uint64 _user_pk;

public:
	std::string session_id() const
	{
		return _session_id;
	}

	uint64 user_pk() const
	{
		return _user_pk;
	}
};

