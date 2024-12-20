#pragma once

#include <sql.h>
#include <sqlext.h>
class DBConnection
{
public:
	// 연결/해제
	bool Connect(SQLHENV henv, const WCHAR* connectionString);
	void Clear();
	
	// 실행부
	bool Execute(const WCHAR* query);
	bool Fetch();
	int32 GetRowCount();
	void UnBind();

public:
	// 파라미터 및 컬럼 바인딩
	bool BindParam(SQLUSMALLINT paramIndex, SQLSMALLINT cType, SQLSMALLINT sqlType, SQLULEN len, SQLPOINTER ptr, SQLLEN* index);
	bool BindCol(SQLUSMALLINT columnIndex, SQLSMALLINT cType, SQLULEN len, SQLPOINTER value, SQLLEN* index);
	void HandleError(SQLRETURN ret);

private:
	SQLHDBC _connection = SQL_NULL_HANDLE;
	SQLHSTMT _statement = SQL_NULL_HANDLE;
};

