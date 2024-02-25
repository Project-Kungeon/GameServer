#pragma once
#include "pch.h"
#include "Player.h"
#include <memory>

class GameSession : public Session
{
public:
	virtual void OnConnected() override;
	virtual void OnDisconnected() override;


public:
	atomic<std::shared_ptr<Player>> player;
	
};

