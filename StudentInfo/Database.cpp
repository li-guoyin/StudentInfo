#include "stdafx.h"
#include "Database.h"


Database::Database()
{
}


Database::~Database()
{
}

bool Database::Connect()
{
	mysql_init(&m_sqlCon);
	bool isconnect = mysql_real_connect(&m_sqlCon, "localhost", "root", "391269102@lgy",
		"studentInfo", 3306, NULL, 0);
	if (isconnect == false)
	{
		MessageBox(NULL, _T("数据库连接失败"), _T("提示"), MB_OK);
		return false;
	}
	else
	{
		MessageBox(NULL, _T("数据库连接成功"), _T("提示"), MB_OK);
		return true;
	}
}


