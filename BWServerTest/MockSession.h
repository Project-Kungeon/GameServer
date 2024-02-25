#pragma once
#include "pch.h"

class MockSession : public Session
{
public:
	MockSession(asio::io_context& io_context, Room& room) : Session(io_context, room) {};
	MOCK_METHOD(void, Send, (asio::mutable_buffer& buffer), (override));
};