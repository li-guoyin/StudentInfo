#pragma once
#include "afxwin.h"
#include "Database.h"
#include <vector>
using namespace std;

// StuInfo 对话框
struct StudentInfos
{
	CString num;
	CString name;
	CString sex;
	CString birthdate;
	CString startschdate;
	CString profession;
};
class StuInfo : public CDialogEx
{
	DECLARE_DYNAMIC(StuInfo)

public:
	StuInfo(CWnd* pParent = NULL);   // 标准构造函数
	StuInfo(Database d,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~StuInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_StuInfo };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedFirst();
	afx_msg void OnBnClickedUP();
	afx_msg void OnBnClickedNext();
	afx_msg void OnBnClickedEnd();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedAlter();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEdit1();
	// 查询时用的学号
	CString m_SearchNum;
	// 查询时用的姓名
	CString m_SearchName;
	// 学号
	CString m_Num;
	// 姓名
	CString m_Name;
	// 性别
	CString m_Sex;
	// 专业
	CString m_Profession;
	// 出生日期
	CString m_BirthDate;
	// 入学时间
	CString m_StartSchDate;
private:
	Database db;
	vector<StudentInfos *> m_Infos;
	int count;
	int AlterOrAdd;

	char* num;
	char* name;
	char* sex;
	char* birdate;
	char* scdate;
	char* profess;
public:
	void reflash();
	
};
