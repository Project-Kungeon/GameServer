#include "LobbyPacketHandler.h"
#include "Message.pb.h"

void LobbyPakcetHandler::Handle_C_Login(asio::mutable_buffer& buffer, const PacketHeader& header, int& offset)
{
	// Deserialize Request Packet
	message::C_Login cLogin;
	PacketUtil::Parse(cLogin, buffer, header.Length, offset);

	// Serialize Response Packet
	message::S_Login sLogin;
	//sLogin.add

}

void LobbyPakcetHandler::Handle_C_EnterRoom(asio::mutable_buffer& buffer, const PacketHeader& header, int& offset)
{
}
