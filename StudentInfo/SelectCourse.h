#pragma once
#include "Database.h"
#include <vector>
using namespace std;

// SelectCourse 对话框
//struct SelectCouInfos
//{
//	CString stunum;
//	CString counum;
//	CString couname;
//};
class SelectCourse : public CDialogEx
{
	DECLARE_DYNAMIC(SelectCourse)

public:
	SelectCourse(CWnd* pParent = NULL);   // 标准构造函数
	SelectCourse(Database d, CWnd* pParent = NULL);
	virtual ~SelectCourse();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECTCOURSE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedAlter();
	CString m_SearchNum;
	CString m_SearchName;
	CString m_StuNum;
	CString m_CouNum;
	CString m_CouName;
	CString m_Grade;
private:
	Database db;
	char* stunum;
	char* counum;
	char* grade;
	int AlterOrAdd;
public:

	
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
};
