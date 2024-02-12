#pragma once
#include "pch.h"

class GameSession : public Session
{
public:
	virtual void OnConnected() override;
	virtual void OnDisconnected() override;

private:
	atomic<boost::shared_ptr<Player>> player;
	
};

