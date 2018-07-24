#pragma once
#include "afxwin.h"
#include "Database.h"
#include <vector>
using namespace std;

// StuInfo �Ի���
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
	StuInfo(CWnd* pParent = NULL);   // ��׼���캯��
	StuInfo(Database d,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~StuInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_StuInfo };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	// ��ѯʱ�õ�ѧ��
	CString m_SearchNum;
	// ��ѯʱ�õ�����
	CString m_SearchName;
	// ѧ��
	CString m_Num;
	// ����
	CString m_Name;
	// �Ա�
	CString m_Sex;
	// רҵ
	CString m_Profession;
	// ��������
	CString m_BirthDate;
	// ��ѧʱ��
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
