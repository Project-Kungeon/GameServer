#include "LobbyPacketHandler.h"
#include "Session/Session.h"

bool LobbyPacketHandler::Handle_S_Login(SessionPtr& session, account::login::S_Login& pkt)
{
    if (pkt.is_success())
    {
        account::character::select::C_CharacterList characterListPkt;

        const size_t requiredSize = PacketUtil::RequiredSize(characterListPkt);

        char* rawBuffer = new char[requiredSize];
        auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
        PacketUtil::Serialize(sendBuffer, message::HEADER::CHARACTER_LIST_REQ, characterListPkt);

        session->Send(sendBuffer);
    }
    
    return pkt.is_success();
}

bool LobbyPacketHandler::Handle_S_CharacterList(SessionPtr& session, account::character::select::S_CharacterList& pkt)
{
    // 부하테스트는 무조건 첫번째 캐릭터를 가져온다.
    auto& characterList = pkt.character_info_list();
    if (!characterList.empty())
    {
        account::character::select::C_SelectCharacter selectCharacterPkt;
        selectCharacterPkt.set_character_pk(characterList[0].pk());
        const size_t requiredSize = PacketUtil::RequiredSize(selectCharacterPkt);
        char* rawBuffer = new char[requiredSize];
        auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
        PacketUtil::Serialize(sendBuffer, message::HEADER::CHARACTER_SELECT_REQ, selectCharacterPkt);

        session->Send(sendBuffer);
    }
    return true;
}
