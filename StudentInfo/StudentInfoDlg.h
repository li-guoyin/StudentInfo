
// StudentInfoDlg.h : ͷ�ļ�
//

#pragma once
#include "Database.h"
#include "StuInfo.h"
#include "CourseInfo.h"
#include "SelectCourse.h"
#include "StuGrade.h"

// CStudentInfoDlg �Ի���
class CStudentInfoDlg : public CDialogEx
{
// ����
public:
	CStudentInfoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDENTINFO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
