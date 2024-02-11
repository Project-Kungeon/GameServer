#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include "Packet.h"

using namespace std;
using namespace boost;

class LobbyPakcetHandler
{
private:
	LobbyPakcetHandler() {}
	LobbyPakcetHandler(const LobbyPakcetHandler& ref) {}
	LobbyPakcetHandler& operator=(const LobbyPakcetHandler& ref) {}
	~LobbyPakcetHandler() {}

public:
	void Handle_C_Login(asio::mutable_buffer& buffer, const PacketHeader& header, int& offset);
	void Handle_C_EnterRoom(asio::mutable_buffer& buffer, const PacketHeader& header, int& offset);

	static LobbyPakcetHandler& getInstance()
	{
		static LobbyPakcetHandler lph;
		return lph;
	}


};