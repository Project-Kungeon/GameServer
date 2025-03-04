#include "pch.h"
#include "CharacterSelectPacketHandler.h"
#include "DB/MySQLConnection.h"
#include "DB/ConnectionPool.h"

bool CharacterSelectPacketHandler::Handle_C_CharacterList(SessionPtr& session,
    account::character::select::C_CharacterList pkt)
{
    GameSessionPtr game_session = static_pointer_cast<GameSession>(session);
    uint64 user_pk = game_session->user_pk();
    if (user_pk == NULL) return false;
    
    std::shared_ptr<active911::MySQLConnection> conn = GConnectionPool->borrow();
    while (conn == nullptr)
    {
        conn = GConnectionPool->borrow();
    }

    std::shared_ptr<sql::Connection> sql_conn = conn->sql_connection;

    sql_conn->setSchema("GameDB");
	
    std::unique_ptr<sql::PreparedStatement> pstmt(sql_conn->prepareStatement("SELECT pk, name, class_type FROM character_list WHERE user_pk = ?"));
    pstmt->setUInt64(1, game_session->user_pk());  // 1은 첫 번째 물음표(?)를 의미합니다
    std::unique_ptr<sql::ResultSet> results(pstmt->executeQuery());
    GConnectionPool->unborrow(conn);
    
    account::character::select::S_CharacterList characterListPkt;
    
    while (results->next())
    {
        auto* CharacterInfo = characterListPkt.add_character_info_list();
        CharacterInfo->set_pk(results->getUInt64("pk"));
        CharacterInfo->add_nickname(results->getString("name").c_str());
        CharacterInfo->set_class_type(results->getUInt64("class_type"));
    }

            
    session->SendPacket(characterListPkt, message::HEADER::CHARACTER_LIST_RES);

    return true;
}

bool CharacterSelectPacketHandler::Handle_C_SelectCharacter(SessionPtr& session,
    account::character::select::C_SelectCharacter pkt)
{
    GameSessionPtr game_session = static_pointer_cast<GameSession>(session);

    std::shared_ptr<active911::MySQLConnection> conn = GConnectionPool->borrow();
    while (conn == nullptr)
    {
        conn = GConnectionPool->borrow();
    }

    std::shared_ptr<sql::Connection> sql_conn = conn->sql_connection;
    sql_conn->setSchema("GameDB");
	
    std::unique_ptr<sql::PreparedStatement> pstmt(sql_conn->prepareStatement("SELECT pk, name, class_type FROM character_list WHERE pk = ?"));
   
    pstmt->setUInt64(1, pkt.character_pk());  // 1은 첫 번째 물음표(?)를 의미합니다
    std::unique_ptr<sql::ResultSet> results(pstmt->executeQuery());
    GConnectionPool->unborrow(conn);

    if (results->next())
    {
        message::PlayerType player_type = static_cast<message::PlayerType>(results->getUInt64("class_type"));
        PlayerPtr player = ObjectUtils::CreatePlayer(static_pointer_cast<GameSession>(session), player_type);
        // Serialize Response Packet
        GRoom[0]->DoAsync(&Room::HandleEnterPlayer, (player));
        static_pointer_cast<GameSession>(session)->isEnterGame = true;

        return true;
    }
    return false;
}
