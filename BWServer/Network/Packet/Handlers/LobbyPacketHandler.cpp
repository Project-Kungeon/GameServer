#include "pch.h"
#include "LobbyPacketHandler.h"
#include "DB/MySQLConnection.h"
#include "DB/ConnectionPool.h"

bool LobbyPacketHandler::Handle_C_Login(SessionPtr& session, account::login::C_Login& pkt)
{
	std::string email(pkt.email(0).c_str());
	
	std::shared_ptr<active911::MySQLConnection> conn = GConnectionPool->borrow();
	std::shared_ptr<sql::Connection> sql_conn = conn->sql_connection;
	sql_conn->setSchema("GameDB");
	
	std::unique_ptr<sql::PreparedStatement> pstmt(sql_conn->prepareStatement("SELECT * FROM Users WHERE email = ?"));
	pstmt->setString(1, email);  // 1은 첫 번째 물음표(?)를 의미합니다
	std::unique_ptr<sql::ResultSet> results(pstmt->executeQuery());

	bool isLogin = false;
	account::login::S_Login packet_login;
	
	if (results)
	{
		// 이메일이 존재할 경우
		if (results->next())
		{ 
			string input_password = pkt.password(0).c_str();
			string password_hash = results->getString("password");
			isLogin = BCrypt::validatePassword(input_password, password_hash);

			if (isLogin)
			{
				// 로그인 성공
				
				packet_login.set_is_success(1);
				auto game_session = static_pointer_cast<GameSession>(session);
				game_session->AssignSessionId();
				auto session_id_str = packet_login.add_session_id();
				*session_id_str = game_session->session_id();

				spdlog::info("===로그인 성공!===");
				spdlog::info("DB PK : {}", results->getUInt64("pk"));
				spdlog::info("email: {}", email);
				spdlog::info("Session ID: {0}", *session_id_str);
				
				
			}
			else
			{
				packet_login.set_is_success(0);
			}
			
		}
	}
	else
	{
		// 이메일이 존재하지 않을 경우
		packet_login.set_is_success(0);
	}
	
	GConnectionPool->unborrow(conn);
	
	const size_t requiredSize = PacketUtil::RequiredSize(packet_login);

	char* rawBuffer = new char[requiredSize];
	auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
	PacketUtil::Serialize(sendBuffer, message::HEADER::LOGIN_RES, packet_login);

	session->Send(sendBuffer);
	return true;
}

/*bool LobbyPacketHandler::Handle_C_Register(SessionPtr& session, account::login::C_Register& pkt)
{
	return false;
}*/
