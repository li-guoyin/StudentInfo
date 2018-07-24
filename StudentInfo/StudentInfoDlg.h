
// StudentInfoDlg.h : 头文件
//

#pragma once
#include "Database.h"
#include "StuInfo.h"
#include "CourseInfo.h"
#include "SelectCourse.h"
#include "StuGrade.h"

// CStudentInfoDlg 对话框
class CStudentInfoDlg : public CDialogEx
{
// 构造
public:
	CStudentInfoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDENTINFO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStuInfo();
	afx_msg void OnBnClickedCourseInfo();
	afx_msg void OnBnClickedSelectCourse();
	afx_msg void OnBnClickedStuGrade();
	afx_msg void OnBnClickedCancel();
private:
	Database db;
	StuInfo * m_StuInfo;
	CourseInfo * m_CourceInfo;
	SelectCourse * m_SelectCourse;
	StuGrade *m_StuGrade;
};
