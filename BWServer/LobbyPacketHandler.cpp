#include "pch.h"
#include "RandomUtil.h"
#include "LobbyPacketHandler.h"

bool LobbyPacketHandler::Handle_C_Login(SessionPtr& session, message::C_Login& pkt)
{
	// Deserialize Request Packet


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
}