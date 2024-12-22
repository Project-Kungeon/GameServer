#include "pch.h"
#include "LobbyPacketHandler.h"

#include "DB/DBBind.h"
#include "DB/DBConnectionPool.h"

/*bool LobbyPacketHandler::Handle_C_Login(SessionPtr& session, message::C_Login& pkt)
{
	// Deserialize Request Packet
	spdlog::info("Player Login!");

	// Serialize Response Packet
	message::S_Login sLogin;
	//sLogin.add
	message::ObjectInfo* player = sLogin.add_players();
	
	message::PosInfo* posInfo = player->mutable_pos_info();
	posInfo->set_x(RandomUtil::GetRandom(0.f, 100.f));
	posInfo->set_y(RandomUtil::GetRandom(0.f, 100.f));
	posInfo->set_z(RandomUtil::GetRandom(0.f, 100.f));
	posInfo->set_yaw(RandomUtil::GetRandom(0.f, 45.f));

	sLogin.set_success(true);

	const size_t requiredSize = PacketUtil::RequiredSize(sLogin);

	char* rawBuffer = new char[requiredSize];
	auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
	PacketUtil::Serialize(sendBuffer, message::HEADER::LOGIN_RES, sLogin);

	session->Send(sendBuffer);

	return true;
}*/
bool LobbyPacketHandler::Handle_C_Login(SessionPtr& session, account::login::C_Login& pkt)
{
	/*
	DBConnection* dbConn = GDBConnectionPool->Pop();
	DBBind<1, 1> dbBind(*dbConn, L"SELECT Id FROM [Users] WHERE email = (?)");

	WCHAR name[100];
	MultiByteToWideChar(CP_UTF8, 0, pkt.email().at(0).c_str(), -1, name, 100);
	dbBind.BindParam(0, name);

	long id = 0;
	dbBind.BindCol(0, OUT id);
	dbBind.Execute();
	*/

	return false;
}

/*bool LobbyPacketHandler::Handle_C_Register(SessionPtr& session, account::login::C_Register& pkt)
{
	return false;
}*/
