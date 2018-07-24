// CourseInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentInfo.h"
#include "CourseInfo.h"
#include "afxdialogex.h"


// CourseInfo �Ի���

IMPLEMENT_DYNAMIC(CourseInfo, CDialogEx)

CourseInfo::CourseInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COURSE, pParent)
	, m_SearchName(_T(""))
	, m_Num(_T(""))
	, m_Name(_T(""))
	, m_Credit(_T(""))
	, m_SearchNum(_T(""))
{

}

CourseInfo::CourseInfo(Database d, CWnd * pParent)
	: CDialogEx(IDD_COURSE, pParent)
	, m_SearchName(_T(""))
	, m_Num(_T(""))
	, m_Name(_T(""))
	, m_Credit(_T(""))
	, m_SearchNum(_T(""))
{
	db = d;
	count = 0;
	AlterOrAdd = -1;
	//�����ݿ��ʼ��m_Infos,����ȡ��һ������һ������һ����ĩһ��
	reflash();
}

CourseInfo::~CourseInfo()
{
}

void CourseInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, m_SearchNUM);
	DDX_Text(pDX, IDC_EDIT2, m_SearchName);
	DDX_Text(pDX, IDC_EDIT3, m_Num);
	DDX_Text(pDX, IDC_EDIT4, m_Name);
	DDX_Text(pDX, IDC_EDIT5, m_Credit);
	DDX_Text(pDX, IDC_EDIT1, m_SearchNum);
}


BEGIN_MESSAGE_MAP(CourseInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CourseInfo::OnBnClickedSearch)
	ON_BN_CLICKED(IDC_BUTTON2, &CourseInfo::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_BUTTON3, &CourseInfo::OnBnClickedAlter)
	ON_BN_CLICKED(IDC_BUTTON4, &CourseInfo::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_BUTTON5, &CourseInfo::OnBnClickedFirst)
	ON_BN_CLICKED(IDC_BUTTON6, &CourseInfo::OnBnClickedUP)
	ON_BN_CLICKED(IDC_BUTTON7, &CourseInfo::OnBnClickedNext)
	ON_BN_CLICKED(IDC_BUTTON8, &CourseInfo::OnBnClickedEnd)
	ON_BN_CLICKED(IDC_BUTTON9, &CourseInfo::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CourseInfo::OnBnClickedButton10)
END_MESSAGE_MAP()


// CourseInfo ��Ϣ�������


void CourseInfo::OnBnClickedSearch()
{
	UpdateData(TRUE);
	mysql_set_character_set(&db.m_sqlCon, "GB2312");

	char* num = m_SearchNum.GetBuffer();
	m_SearchNum.ReleaseBuffer();
	char* name = m_SearchName.GetBuffer();
	m_SearchName.ReleaseBuffer();
	char select[1000];
	sprintf_s(select, "select *from Course where numberCourse  = \'%s\' and nameCou = \'%s\'", num, name);
	// ִ�� sql ��䡣    
	// mysql_query() �ķ���ֵ�ݺܶ����Σ� �����ж�ʹҪע�⡣    
	if (mysql_query(&db.m_sqlCon, select) == 0)
	{
		//AfxMessageBox(_T("��ѯ���ݳɹ�!"));
		MYSQL_RES *res = mysql_store_result(&db.m_sqlCon); //��ȡ����ѯ���   
		MYSQL_FIELD *field = mysql_fetch_fields(res); //��ȡ��������
		int field_count = mysql_field_count(&db.m_sqlCon); //��ȡ����


														   //�������ÿһ������  
		MYSQL_ROW row;
		while (row = mysql_fetch_row(res))
		{
			m_Num.Format("%s", row[0]);
			m_Name.Format("%s", row[1]);
			m_Credit.Format("%s", row[2]);
		}
		int it;
		for (it = 0; it<m_Infos.size(); it++)
		{
			if (m_Infos[it]->num == m_Num)
			{
				count = it;
				break;
			}

		}
		UpdateData(FALSE);
	}
	else {
		AfxMessageBox(_T("��ѯ����ʧ��!"));
	}
}


void CourseInfo::OnBnClickedAdd()
{
	UpdateData(TRUE);
	if (!m_Num.IsEmpty() && !m_Name.IsEmpty() && !m_Credit.IsEmpty())
	{
		num = m_Num.GetBuffer();
		m_SearchNum.ReleaseBuffer();
		name = m_Name.GetBuffer();
		m_SearchName.ReleaseBuffer();
		credit = m_Credit.GetBuffer();
		m_Credit.ReleaseBuffer();
		MessageBox(_T("������棬������Ϣ;\n���ȡ����ȡ������"), _T("��ʾ"), MB_OK);
		AlterOrAdd = 0;
	}
	else
	{
		MessageBox(_T("�뽫��Ϣ��д����"), _T("��ʾ"), MB_OK);
	}
}


void CourseInfo::OnBnClickedAlter()
{
	CString oldnum = m_Num;
	UpdateData(TRUE);
	if (!m_Num.IsEmpty() && !m_Name.IsEmpty() && !m_Credit.IsEmpty())
	{
		if (oldnum != m_Num)
		{
			MessageBox(_T("�γ̺Ų��ܸ���"), _T("��ʾ"), MB_OK);
			return;
		}
		num = m_Num.GetBuffer();
		m_SearchNum.ReleaseBuffer();
		name = m_Name.GetBuffer();
		m_SearchName.ReleaseBuffer();
		credit = m_Credit.GetBuffer();
		m_Credit.ReleaseBuffer();
		MessageBox(_T("������棬������Ϣ;\n���ȡ����ȡ������"), _T("��ʾ"), MB_OK);
		AlterOrAdd = 1;
		
	}
	else
	{
		MessageBox(_T("�뽫��Ϣ��д����"), _T("��ʾ"), MB_OK);
	}
}


void CourseInfo::OnBnClickedDelete()
{
	if (MessageBox(_T("�Ƿ�Ҫɾ��"), _T("��ʾ"), MB_OKCANCEL) == IDOK)
	{
		UpdateData(TRUE);
		if (!m_Num.IsEmpty())
		{
			mysql_set_character_set(&db.m_sqlCon, "GB2312");

			char* num = m_Num.GetBuffer();
			m_Num.ReleaseBuffer();

			char update[1000];
			sprintf_s(update, "delete from Course where numberCourse = \'%s\'"
				, num);
			// ִ�� sql ��䡣    
			// mysql_query() �ķ���ֵ�ݺܶ����Σ� �����ж�ʹҪע�⡣    
			if (mysql_query(&db.m_sqlCon, update) == 0)
			{
				m_Num = _T("");
				m_Name = _T("");
				m_Credit = _T("");
				UpdateData(FALSE);
				MessageBox(_T("ɾ���ɹ�"), _T("��ʾ"), MB_OK);
				reflash();
			}
			else
				MessageBox(_T("ɾ��ʧ��"), _T("��ʾ"), MB_OK);
		}
		else
		{
			MessageBox(_T("Ҫɾ��ʲô�γ�?"), _T("��ʾ"), MB_OK);
		}
	}
	
}


void CourseInfo::OnBnClickedFirst()
{
	count = 0;
	m_Num = m_Infos[count]->num;
	m_Name = m_Infos[count]->name;
	m_Credit= m_Infos[count]->credit;
	UpdateData(FALSE);
}


void CourseInfo::OnBnClickedUP()
{
	count -= 1;
	if (count <= 0)
	{
		count = 0;
	}
	m_Num = m_Infos[count]->num;
	m_Name = m_Infos[count]->name;
	m_Credit = m_Infos[count]->credit;
	UpdateData(FALSE);
	if (count == 0)
		MessageBox(_T("�Ѿ��ǵ�һ��"), _T("��ʾ"), MB_OK);
}


void CourseInfo::OnBnClickedNext()
{
	count += 1;
	if (count >= m_Infos.size() - 1)
	{
		count = m_Infos.size() - 1;
	}
	m_Num = m_Infos[count]->num;
	m_Name = m_Infos[count]->name;
	m_Credit = m_Infos[count]->credit;
	UpdateData(FALSE);
	if (count == m_Infos.size() - 1)
		MessageBox(_T("�Ѿ������һ��"), _T("��ʾ"), MB_OK);
}


void CourseInfo::OnBnClickedEnd()
{
	count = m_Infos.size() - 1;
	m_Num = m_Infos[count]->num;
	m_Name = m_Infos[count]->name;
	m_Credit = m_Infos[count]->credit;
	UpdateData(FALSE);
}

void CourseInfo::reflash()
{
	mysql_set_character_set(&db.m_sqlCon, "GB2312");
	char select[1000];
	sprintf_s(select, "select *from Course");
	// ִ�� sql ��䡣    
	// mysql_query() �ķ���ֵ�ݺܶ����Σ� �����ж�ʹҪע�⡣    
	if (mysql_query(&db.m_sqlCon, select) == 0)
	{
		m_Infos.clear();
		//AfxMessageBox(_T("��ѯ���ݳɹ�!"));
		MYSQL_RES *res = mysql_store_result(&db.m_sqlCon); //��ȡ����ѯ���   
		MYSQL_FIELD *field = mysql_fetch_fields(res); //��ȡ��������
		int field_count = mysql_field_count(&db.m_sqlCon); //��ȡ����
		MYSQL_ROW row;
		while (row = mysql_fetch_row(res))
		{
			CourseInfos * cou = new CourseInfos;
			cou->num.Format("%s", row[0]);
			cou->name.Format("%s", row[1]);
			cou->credit.Format("%s", row[2]);
			m_Infos.push_back(cou);
		}
	}
}

//����
void CourseInfo::OnBnClickedButton9()
{
	mysql_set_character_set(&db.m_sqlCon, "GB2312");
	if (AlterOrAdd == 0)
	{
		char insert[1000];
		sprintf_s(insert, "insert into Course(numberCourse, nameCou, credit) values (\'%s\', \'%s\', \'%s\')"
			, num, name, credit);
		// ִ�� sql ��䡣    
		// mysql_query() �ķ���ֵ�ݺܶ����Σ� �����ж�ʹҪע�⡣    
		if (mysql_query(&db.m_sqlCon, insert) == 0)
		{
			MessageBox(_T("����ɹ�"), _T("��ʾ"), MB_OK);
			reflash();
		}
		else
			MessageBox(_T("����ʧ��"), _T("��ʾ"), MB_OK);
	}
	else if (AlterOrAdd == 1)
	{
		char update[1000];
		sprintf_s(update, "update Course set nameCou = \'%s\', credit= \'%s\' where numberCourse = \'%s\'"
			, name, credit,num);
		// ִ�� sql ��䡣    
		// mysql_query() �ķ���ֵ�ݺܶ����Σ� �����ж�ʹҪע�⡣    
		if (mysql_query(&db.m_sqlCon, update) == 0)
		{
			MessageBox(_T("���³ɹ�"), _T("��ʾ"), MB_OK);
			reflash();
		}
		else
			MessageBox(_T("����ʧ��"), _T("��ʾ"), MB_OK);
	}
	
}

//ȡ��
void CourseInfo::OnBnClickedButton10()
{
	num = "";
	name = "";
	credit = "";
	AlterOrAdd = -1;
	MessageBox(_T("ȡ������"), _T("��ʾ"), MB_OK);
}
