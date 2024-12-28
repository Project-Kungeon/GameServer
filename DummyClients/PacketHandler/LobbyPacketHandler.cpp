#include "LobbyPacketHandler.h"

bool LobbyPacketHandler::Handle_S_Login(SessionPtr& session, account::login::S_Login& pkt)
{
    return pkt.is_success();
}
