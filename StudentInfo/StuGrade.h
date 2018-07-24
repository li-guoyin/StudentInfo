#pragma once
#include "afxcmn.h"
#include "Database.h"


// StuGrade �Ի���

class StuGrade : public CDialogEx
{
	DECLARE_DYNAMIC(StuGrade)

public:
	StuGrade(CWnd* pParent = NULL);   // ��׼���캯��
	StuGrade(Database d,CWnd* pParent = NULL);
	virtual ~StuGrade();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUGRADE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_Num;
	CListCtrl m_GradeList;
	afx_msg void OnBnClickedSearch();

private:
	int m_CouNum;
	float m_Credit;
	float m_AveGrade;
	float m_AllGrade;
	Database db;
	CString stunum, coursenum, grade, credit;
public:
//	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	int m_CourseNumber;
	float m_CreditNumber;
	float m_AveGradeNumber;
};
