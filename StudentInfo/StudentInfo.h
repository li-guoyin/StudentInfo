
// StudentInfo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CStudentInfoApp: 
// �йش����ʵ�֣������ StudentInfo.cpp
//

class CStudentInfoApp : public CWinApp
{
public:
	CStudentInfoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CStudentInfoApp theApp;
