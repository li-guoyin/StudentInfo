#pragma once
#include "mysql.h"
#include "winsock.h"
class Database
{
public:
	Database();
	~Database();
	bool Connect();
public:
	MYSQL m_sqlCon;
};

