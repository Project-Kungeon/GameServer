#pragma once
#include "DB/MySQLConnection.h"

class SqlUtils
{
private:
    // 다양한 파라미터 타입에 대응하여 바인딩시켜주는 함수
    template<typename T>
    static void bindParam(sql::PreparedStatement* stmt, int index, T&& value)
    {
        
        if constexpr (std::is_same_v<std::decay_t<T>, uint64>)
        {
            stmt->setUInt64(index, value);
        }
        else if constexpr (std::is_same_v<std::decay_t<T>, int64>)
        {
            stmt->setInt64(index, value);
        }
        else if constexpr (std::is_same_v<std::decay_t<T>, int32>)
        {
            stmt->setInt(index, value);
        }
        else if constexpr (std::is_same_v<std::decay_t<T>, std::string> || 
                          std::is_same_v<std::decay_t<T>, sql::SQLString>)
        {
            stmt->setString(index, value);
        }
        else if constexpr (std::is_same_v<std::decay_t<T>, double>)
        {
            stmt->setDouble(index, value);
        }
        else if constexpr (std::is_same_v<std::decay_t<T>, bool>)
        {
            stmt->setBoolean(index, value);
        }
    }

    // Args 요소 하나씩 찾아가서 BindParam 호출
    template<typename T, typename... Args>
    static void bindParams(sql::PreparedStatement* stmt, int index, T&& value, Args&&... args)
    {
        bindParam(stmt, index, std::forward<T>(value));
        if constexpr (sizeof...(args) > 0)
        {
            bindParams(stmt, index + 1, std::forward<Args>(args)...);
        }
        
    }

    
    
public:
    /* 쿼리 하나 만드는데 필요한 정보(Parameters)
     * Schema(DB 이름)
     * SqlConnectionPtr
     * DML Content
     *
     * 반환 결과(Response)
     * ResultSet
     */
    template<typename... Args>
    static std::shared_ptr<sql::ResultSet> executeQuery(
        std::shared_ptr<sql::Connection> sql_conn,
        const sql::SQLString& schema,
        const sql::SQLString& query,
        Args&&... args)
    {
        sql_conn->setSchema(schema);
        std::unique_ptr<sql::PreparedStatement> pstmt(sql_conn->prepareStatement(query));
        if constexpr (sizeof...(args) > 0)
        {
            bindParams(pstmt.get(), 1, std::forward<Args>(args)...);
        }
        return std::shared_ptr<sql::ResultSet>(pstmt->executeQuery());
    }
    
    
};



