#include "pch.h"

class MockSession : public Session
{
public:
	MockSession(asio::io_context& io_context, Room& room) : Session(io_context, room) {};
	MOCK_METHOD(void, Send, (asio::mutable_buffer& buffer), (override));
};

void mock_func()
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
	EXPECT_CALL(*session, Send(::testing::_)).Times(1).WillOnce(::testing::Invoke(mock_func));
	SessionPtr sessionPtr = static_pointer_cast<Session>(session);
	// then
	bool success = LobbyPacketHandler::Handle_C_Login(sessionPtr, loginPkt);

	EXPECT_EQ(success, true);
	EXPECT_TRUE(true);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}