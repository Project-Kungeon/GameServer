#pragma once

#include <pch.h>
#include <sql.h>
#include <sqlext.h>
enum
{
	WVARCHAR_MAX = 4000,
	BINARY_MAX = 8000
};

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
	bool BindParam(int32 paramIndex, const BYTE* bin, int32 size, SQLLEN* index);
	bool BindCol(int32 columnIndex, bool* value, SQLLEN* index);

	bool BindCol(int32 columnIndex, float* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, double* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, int8* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, int16* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, int32* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, int64* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, TIMESTAMP_STRUCT* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, WCHAR* str, int32 size, SQLLEN* index);
	bool BindCol(int32 columnIndex, BYTE* bin, int32 size, SQLLEN* index);
	bool BindCol(SQLUSMALLINT columnIndex, SQLSMALLINT cType, SQLULEN len, SQLPOINTER value, SQLLEN* index);
	void HandleError(SQLRETURN ret);

private:
	SQLHDBC _connection = SQL_NULL_HANDLE;
	SQLHSTMT _statement = SQL_NULL_HANDLE;
	
};

