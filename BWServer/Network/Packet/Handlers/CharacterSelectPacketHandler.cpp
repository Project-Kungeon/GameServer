#include "pch.h"
#include "CharacterSelectPacketHandler.h"
#include "DB/MySQLConnection.h"
#include "DB/ConnectionPool.h"

//bool CharacterSelectPacketHandler::Handle_C_CharacterList(SessionPtr& session,
//    account::character::select::C_CharacterList)
//{
//    GameSessionPtr game_session = static_pointer_cast<GameSession>(session);
//    uint64 user_pk = game_session->user_pk();
//    if (user_pk == NULL) return false;
//    
//    std::shared_ptr<active911::MySQLConnection> conn = GConnectionPool->borrow();
//    std::shared_ptr<sql::Connection> sql_conn = conn->sql_connection;
//    sql_conn->setSchema("GameDB");
//	
//    std::unique_ptr<sql::PreparedStatement> pstmt(sql_conn->prepareStatement("SELECT * FROM character_list WHERE user_pk = ?"));
//    pstmt->setUInt64(1, game_session->user_pk());  // 1은 첫 번째 물음표(?)를 의미합니다
//    std::unique_ptr<sql::ResultSet> results(pstmt->executeQuery());
//
//    account::character::select::S_CharacterList pkt;
//    
//    while (results->next())
//    {
//        
//    }
//
//    return true;
//}
//
//bool CharacterSelectPacketHandler::Handle_C_SelectCharacter(SessionPtr& session,
//    account::character::select::C_SelectCharacter)
//{
//
//    return true;
//}
