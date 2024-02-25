
#pragma
#include "pch.h"
#include "MockSession.h"

void mock_func1()
{

}

TEST(LoginTest, Success)
{
	// given
	asio::io_context _io_context;
	Room room;
	std::shared_ptr<MockSession> session = std::make_shared<MockSession>(_io_context, room);
	message::C_Login loginPkt;

	// when
	EXPECT_CALL(*session, Send(::testing::_)).Times(1).WillOnce(::testing::Invoke(mock_func1));
	SessionPtr sessionPtr = static_pointer_cast<Session>(session);
	// then
	bool success = LobbyPacketHandler::Handle_C_Login(sessionPtr, loginPkt);

	EXPECT_EQ(success, true);
	EXPECT_TRUE(true);
}