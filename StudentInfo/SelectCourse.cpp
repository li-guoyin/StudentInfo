// SelectCourse.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentInfo.h"
#include "SelectCourse.h"
#include "afxdialogex.h"


// SelectCourse �Ի���

IMPLEMENT_DYNAMIC(SelectCourse, CDialogEx)

SelectCourse::SelectCourse(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SELECTCOURSE, pParent)
	, m_SearchNum(_T(""))
	, m_SearchName(_T(""))
	, m_StuNum(_T(""))
	, m_CouNum(_T(""))
	, m_CouName(_T(""))
	, m_Grade(_T(""))
{

}

SelectCourse::SelectCourse(Database d, CWnd * pParent)
	: CDialogEx(IDD_SELECTCOURSE, pParent)
	, m_SearchNum(_T(""))
	, m_SearchName(_T(""))
	, m_StuNum(_T(""))
	, m_CouNum(_T(""))
	, m_CouName(_T(""))
	, m_Grade(_T(""))
{
	db = d;
	AlterOrAdd = -1;
}

SelectCourse::~SelectCourse()
{
}

void SelectCourse::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_SearchNum);
	DDX_Text(pDX, IDC_EDIT2, m_SearchName);
	DDX_Text(pDX, IDC_EDIT3, m_StuNum);
	DDX_Text(pDX, IDC_EDIT4, m_CouNum);
	DDX_Text(pDX, IDC_EDIT5, m_CouName);
	DDX_Text(pDX, IDC_EDIT6, m_Grade);
}


BEGIN_MESSAGE_MAP(SelectCourse, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &SelectCourse::OnBnClickedSearch)
	ON_BN_CLICKED(IDC_BUTTON4, &SelectCourse::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_BUTTON2, &SelectCourse::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_BUTTON3, &SelectCourse::OnBnClickedAlter)
	ON_BN_CLICKED(IDC_BUTTON5, &SelectCourse::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &SelectCourse::OnBnClickedButton6)
END_MESSAGE_MAP()


// SelectCourse ��Ϣ�������


void SelectCourse::OnBnClickedSearch()
{
	UpdateData(TRUE);
	mysql_set_character_set(&db.m_sqlCon, "GB2312");

	char* num = m_SearchNum.GetBuffer();
	m_SearchNum.ReleaseBuffer();
	char* name = m_SearchName.GetBuffer();
	m_SearchName.ReleaseBuffer();
	char select[1000];
	sprintf_s(select, "select *from selectcourse where stunumber = \'%s\' and counumber = \'%s\'", num, name);
	// ִ�� sql ��䡣    
	// mysql_query() �ķ���ֵ�ݺܶ����Σ� �����ж�ʹҪע�⡣    
	if (mysql_query(&db.m_sqlCon, select) == 0)
	{
		//AfxMessageBox(_T("��ѯ���ݳɹ�!"));
		MYSQL_RES *res = mysql_store_result(&db.m_sqlCon); //��ȡ����ѯ���   
		MYSQL_FIELD *field = mysql_fetch_fields(res); //��ȡ��������
		int field_count = mysql_field_count(&db.m_sqlCon); //��ȡ����
		MYSQL_ROW row;
		while (row = mysql_fetch_row(res))
		{
			m_StuNum.Format("%s", row[0]);
			m_CouNum.Format("%s", row[1]);
			m_Grade.Format("%s", row[2]);
		}
		//���ݿγ�id��γ���
		char* counum = m_CouNum.GetBuffer();
		m_CouNum.ReleaseBuffer();
		char select1[1000];
		sprintf_s(select1, "select nameCou from Course where numberCourse = \'%s\'", counum);
		if (mysql_query(&db.m_sqlCon, select1) == 0)
		{
			//AfxMessageBox(_T("��ѯ���ݳɹ�!"));
			MYSQL_RES *res = mysql_store_result(&db.m_sqlCon); //��ȡ����ѯ���   
			MYSQL_FIELD *field = mysql_fetch_fields(res); //��ȡ��������
			int field_count = mysql_field_count(&db.m_sqlCon); //��ȡ����
			MYSQL_ROW row;
			while (row = mysql_fetch_row(res))
			{
				m_CouName.Format("%s", row[0]);
			}
		}
		UpdateData(FALSE);
	}
	else {
		AfxMessageBox(_T("��ѯ����ʧ��!"));
	}
}


void SelectCourse::OnBnClickedDelete()
{
	if (MessageBox(_T("�Ƿ�Ҫɾ��"), _T("��ʾ"), MB_OKCANCEL) == IDOK)
	{
		UpdateData(TRUE);
		if (!m_StuNum.IsEmpty() && !m_CouNum.IsEmpty())
		{
			mysql_set_character_set(&db.m_sqlCon, "GB2312");

			char* stunum = m_StuNum.GetBuffer();
			m_StuNum.ReleaseBuffer();
			char* counum = m_CouNum.GetBuffer();
			m_CouNum.ReleaseBuffer();
			char update[1000];
			sprintf_s(update, "delete from selectcourse where stunumber = \'%s\' and counumber = \'%s\'"
				, stunum, counum);
			// ִ�� sql ��䡣    
			// mysql_query() �ķ���ֵ�ݺܶ����Σ� �����ж�ʹҪע�⡣    
			if (mysql_query(&db.m_sqlCon, update) == 0)
			{
				m_StuNum = _T("");
				m_CouNum = _T("");
				m_Grade = _T("");
				m_CouName = _T("");
				UpdateData(FALSE);
				MessageBox(_T("ɾ���ɹ�"), _T("��ʾ"), MB_OK);
			}
			else
				MessageBox(_T("ɾ��ʧ��"), _T("��ʾ"), MB_OK);
		}
		else
		{
			MessageBox(_T("Ҫɾ��˭?"), _T("��ʾ"), MB_OK);
		}
	}
	
}


void SelectCourse::OnBnClickedAdd()
{
	UpdateData(TRUE);
	if (!m_StuNum.IsEmpty() && !m_CouNum.IsEmpty() && !m_Grade.IsEmpty())
	{
		stunum = m_StuNum.GetBuffer();
		m_StuNum.ReleaseBuffer();
		counum = m_CouNum.GetBuffer();
		m_CouNum.ReleaseBuffer();
		grade = m_Grade.GetBuffer();
		m_Grade.ReleaseBuffer();
		AlterOrAdd = 0;
		MessageBox(_T("������棬������Ϣ;\n���ȡ����ȡ������"), _T("��ʾ"), MB_OK);
	}
	else
	{
		MessageBox(_T("�뽫��Ϣ��д����"), _T("��ʾ"), MB_OK);
	}
}


void SelectCourse::OnBnClickedAlter()
{
	CString oldnum = m_StuNum;
	CString oldnum2 = m_CouNum;
	UpdateData(TRUE);
	if (!m_StuNum.IsEmpty() && !m_CouNum.IsEmpty())
	{
		if (oldnum != m_StuNum ||oldnum2 != m_CouNum)
		{
			MessageBox(_T("�γ�ID��ѧ��ID���ܸ���"), _T("��ʾ"), MB_OK);
			return;
		}
		stunum = m_StuNum.GetBuffer();
		m_StuNum.ReleaseBuffer();
		counum = m_CouNum.GetBuffer();
		m_CouNum.ReleaseBuffer();
		grade = m_Grade.GetBuffer();
		m_Grade.ReleaseBuffer();
		AlterOrAdd = 1;
		MessageBox(_T("������棬������Ϣ;\n���ȡ����ȡ������"), _T("��ʾ"), MB_OK);
	}
	else
	{
		MessageBox(_T("�뽫��Ϣ��д����"), _T("��ʾ"), MB_OK);
	}
}

//����
void SelectCourse::OnBnClickedButton5()
{
	mysql_set_character_set(&db.m_sqlCon, "GB2312");
	if (AlterOrAdd == 0)
	{
		char insert[1000];
		sprintf_s(insert, "insert into selectcourse(stunumber, counumber, grade) values (\'%s\', \'%s\', \'%s\')"
			, stunum, counum, grade);
		// ִ�� sql ��䡣    
		// mysql_query() �ķ���ֵ�ݺܶ����Σ� �����ж�ʹҪע�⡣    
		if (mysql_query(&db.m_sqlCon, insert) == 0)
		{
			MessageBox(_T("����ɹ�"), _T("��ʾ"), MB_OK);
		}
		else
			MessageBox(_T("����ʧ��"), _T("��ʾ"), MB_OK);
	}
	else if (AlterOrAdd == 1)
	{
		char update[1000];
		sprintf_s(update, "update selectcourse set grade= \'%s\' where stunumber = \'%s\' and counumber = \'%s\'"
			, grade, stunum, counum);
		// ִ�� sql ��䡣    
		// mysql_query() �ķ���ֵ�ݺܶ����Σ� �����ж�ʹҪע�⡣    
		if (mysql_query(&db.m_sqlCon, update) == 0)
		{
			MessageBox(_T("���³ɹ�"), _T("��ʾ"), MB_OK);
		}
		else
			MessageBox(_T("����ʧ��"), _T("��ʾ"), MB_OK);
	}
}

//ȡ��
void SelectCourse::OnBnClickedButton6()
{
	stunum = "";
	counum = "";
	grade = "";
	AlterOrAdd = -1;
	MessageBox(_T("ȡ������"), _T("��ʾ"), MB_OK);
}
