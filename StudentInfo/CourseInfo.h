#pragma once
#include "Database.h"
#include <vector>
using namespace std;
// CourseInfo 对话框
struct CourseInfos
{
	CString num;
	CString name;
	CString credit;
};
class CourseInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CourseInfo)

public:
	CourseInfo(CWnd* pParent = NULL);   // 标准构造函数
	CourseInfo(Database d, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CourseInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COURSE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedAlter();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedFirst();
	afx_msg void OnBnClickedUP();
	afx_msg void OnBnClickedNext();
	afx_msg void OnBnClickedEnd();
	// 查询课程号
	CString m_SearchNum;
	// 课程名
	CString m_SearchName;
	CString m_Num;
	CString m_Name;
	CString m_Credit;
private:
	Database db;
	vector<CourseInfos *> m_Infos;
	int count;
	int AlterOrAdd;

	char* num;
	char* name;
	char* credit;
public:
	void reflash();

	
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
};
