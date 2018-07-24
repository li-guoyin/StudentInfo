// StuInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentInfo.h"
#include "StuInfo.h"
#include "afxdialogex.h"


// StuInfo �Ի���

IMPLEMENT_DYNAMIC(StuInfo, CDialogEx)

StuInfo::StuInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_StuInfo, pParent)
	, m_SearchNum(_T(""))
	, m_SearchName(_T(""))
	, m_Name(_T(""))
	, m_Sex(_T(""))
	, m_Profession(_T(""))
	, m_BirthDate(_T(""))
	, m_StartSchDate(_T(""))
	, m_Num(_T(""))
{

}

StuInfo::StuInfo(Database d, CWnd * pParent)
	: CDialogEx(IDD_StuInfo, pParent)
	, m_SearchNum(_T(""))
	, m_SearchName(_T(""))
	, m_Name(_T(""))
	, m_Sex(_T(""))
	, m_Profession(_T(""))
	, m_BirthDate(_T(""))
	, m_StartSchDate(_T(""))
	, m_Num(_T(""))
{
	//��ȡ���ݿ�
	db = d;
	count = 0;
	AlterOrAdd = -1;
	//�����ݿ��ʼ��m_Infos,����ȡ��һ������һ������һ����ĩһ��
	reflash();
}


StuInfo::~StuInfo()
{
}

void StuInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_SearchNum);
	DDX_Text(pDX, IDC_EDIT2, m_SearchName);
	//  DDX_Control(pDX, IDC_EDIT3, m_Num);
	DDX_Text(pDX, IDC_EDIT6, m_Name);
	DDX_Text(pDX, IDC_EDIT4, m_Sex);
	DDX_Text(pDX, IDC_EDIT7, m_Profession);
	DDX_Text(pDX, IDC_EDIT5, m_BirthDate);
	DDX_Text(pDX, IDC_EDIT8, m_StartSchDate);
	DDX_Text(pDX, IDC_EDIT3, m_Num);
}


BEGIN_MESSAGE_MAP(StuInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &StuInfo::OnBnClickedSearch)
	ON_BN_CLICKED(IDC_BUTTON2, &StuInfo::OnBnClickedFirst)
	ON_BN_CLICKED(IDC_BUTTON3, &StuInfo::OnBnClickedUP)
	ON_BN_CLICKED(IDC_BUTTON4, &StuInfo::OnBnClickedNext)
	ON_BN_CLICKED(IDC_BUTTON5, &StuInfo::OnBnClickedEnd)
	ON_BN_CLICKED(IDC_BUTTON6, &StuInfo::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_BUTTON7, &StuInfo::OnBnClickedAlter)
	ON_BN_CLICKED(IDC_BUTTON8, &StuInfo::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_BUTTON9, &StuInfo::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON10, &StuInfo::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT1, &StuInfo::OnEnChangeEdit1)
END_MESSAGE_MAP()


// StuInfo ��Ϣ�������


void StuInfo::OnBnClickedSearch()
{
	UpdateData(TRUE);
	if (m_SearchNum.IsEmpty() && m_SearchName.IsEmpty())
	{
		m_Num = m_Infos[0]->num;
		m_Name = m_Infos[0]->name;
		m_Sex = m_Infos[0]->sex;
		m_BirthDate = m_Infos[0]->birthdate;
		m_StartSchDate = m_Infos[0]->startschdate;
		m_Profession = m_Infos[0]->profession;
		count = 0;
		UpdateData(FALSE);
	}
	else if (m_SearchNum.IsEmpty() || m_SearchName.IsEmpty())
	{
		//UpdateData(TRUE);
		mysql_set_character_set(&db.m_sqlCon, "GB2312");

		char* num = m_SearchNum.GetBuffer();
		m_SearchNum.ReleaseBuffer();
		char* name = m_SearchName.GetBuffer();
		m_SearchName.ReleaseBuffer();
		char select[1000];
		if (!m_SearchNum.IsEmpty() && m_SearchName.IsEmpty())
		{
			sprintf_s(select, "select *from Student where number = \'%s\'", num);
		}
		else if (m_SearchNum.IsEmpty() && !m_SearchName.IsEmpty())
		{
			sprintf_s(select, "select *from Student where name = \'%s\'", name);
		}
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
				m_Sex.Format("%s", row[2]);
				m_BirthDate.Format("%s", row[3]);
				m_StartSchDate.Format("%s", row[4]);
				m_Profession.Format("%s", row[5]);
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
	else
	{
		//UpdateData(TRUE);
		mysql_set_character_set(&db.m_sqlCon, "GB2312");

		char* num = m_SearchNum.GetBuffer();
		m_SearchNum.ReleaseBuffer();
		char* name = m_SearchName.GetBuffer();
		m_SearchName.ReleaseBuffer();
		char select[1000];
		sprintf_s(select, "select *from Student where number = \'%s\' and name = \'%s\'", num, name);
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
				m_Sex.Format("%s", row[2]);
				m_BirthDate.Format("%s", row[3]);
				m_StartSchDate.Format("%s", row[4]);
				m_Profession.Format("%s", row[5]);
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
	
}


void StuInfo::OnBnClickedFirst()
{
	m_Num = m_Infos[0]->num;
	m_Name = m_Infos[0]->name;
	m_Sex = m_Infos[0]->sex;
	m_BirthDate = m_Infos[0]->birthdate;
	m_StartSchDate = m_Infos[0]->startschdate;
	m_Profession = m_Infos[0]->profession;
	count = 0;
	UpdateData(FALSE);
}


void StuInfo::OnBnClickedUP()
{
	count -= 1;
	if (count <= 0)
	{
		count = 0;
	}
	m_Num = m_Infos[count]->num;
	m_Name = m_Infos[count]->name;
	m_Sex = m_Infos[count]->sex;
	m_BirthDate = m_Infos[count]->birthdate;
	m_StartSchDate = m_Infos[count]->startschdate;
	m_Profession = m_Infos[count]->profession;
	UpdateData(FALSE);
	if(count == 0)
		MessageBox(_T("�Ѿ��ǵ�һ��"), _T("��ʾ"), MB_OK);
}


void StuInfo::OnBnClickedNext()
{
	count += 1;
	if (count >= m_Infos.size()-1)
	{
		count = m_Infos.size() - 1;
	}
	m_Num = m_Infos[count]->num;
	m_Name = m_Infos[count]->name;
	m_Sex = m_Infos[count]->sex;
	m_BirthDate = m_Infos[count]->birthdate;
	m_StartSchDate = m_Infos[count]->startschdate;
	m_Profession = m_Infos[count]->profession;
	UpdateData(FALSE);
	if (count == m_Infos.size() - 1)
		MessageBox(_T("�Ѿ������һ��"), _T("��ʾ"), MB_OK);
}


void StuInfo::OnBnClickedEnd()
{
	count = m_Infos.size()-1;
	m_Num = m_Infos[count]->num;
	m_Name = m_Infos[count]->name;
	m_Sex = m_Infos[count]->sex;
	m_BirthDate = m_Infos[count]->birthdate;
	m_StartSchDate = m_Infos[count]->startschdate;
	m_Profession = m_Infos[count]->profession;
	UpdateData(FALSE);
}


void StuInfo::OnBnClickedAdd()
{
	UpdateData(TRUE);
	if (!m_Num.IsEmpty() && !m_Name.IsEmpty() && !m_Sex.IsEmpty() && !m_BirthDate.IsEmpty() && !m_StartSchDate.IsEmpty() && !m_Profession.IsEmpty())
	{
		MessageBox(_T("������棬������Ϣ;\n���ȡ����ȡ������"), _T("��ʾ"), MB_OK);
		num = m_Num.GetBuffer();
		m_Num.ReleaseBuffer();
		name = m_Name.GetBuffer();
		m_Name.ReleaseBuffer();
		sex = m_Sex.GetBuffer();
		m_Sex.ReleaseBuffer();
		birdate = m_BirthDate.GetBuffer();
		m_BirthDate.ReleaseBuffer();
		scdate = m_StartSchDate.GetBuffer();
		m_StartSchDate.ReleaseBuffer();
		profess = m_Profession.GetBuffer();
		m_Profession.ReleaseBuffer();
		AlterOrAdd = 0;
	}
	else
	{
		MessageBox(_T("�뽫��Ϣ��д����"), _T("��ʾ"), MB_OK);
	}
}


void StuInfo::OnBnClickedAlter()
{
	CString oldnum = m_Num;
	UpdateData(TRUE);
	if (!m_Num.IsEmpty() && !m_Name.IsEmpty() && !m_Sex.IsEmpty() && !m_BirthDate.IsEmpty() && !m_StartSchDate.IsEmpty() && !m_Profession.IsEmpty())
	{
		if (oldnum != m_Num)
		{
			MessageBox(_T("ѧ�Ų��ܸ���"), _T("��ʾ"), MB_OK);
			return;
		}
		MessageBox(_T("������棬������Ϣ;\n���ȡ����ȡ������"), _T("��ʾ"), MB_OK);
		AlterOrAdd = 1;
		num = m_Num.GetBuffer();
		m_Num.ReleaseBuffer();
		name = m_Name.GetBuffer();
		m_Name.ReleaseBuffer();
		sex = m_Sex.GetBuffer();
		m_Sex.ReleaseBuffer();
		birdate = m_BirthDate.GetBuffer();
		m_BirthDate.ReleaseBuffer();
		scdate = m_StartSchDate.GetBuffer();
		m_StartSchDate.ReleaseBuffer();
		profess = m_Profession.GetBuffer();
		m_Profession.ReleaseBuffer();
	}
	else
	{
		MessageBox(_T("�뽫��Ϣ��д����"), _T("��ʾ"), MB_OK);
	}
}


void StuInfo::OnBnClickedDelete()
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
			sprintf_s(update, "delete from Student where number = \'%s\'"
				, num);
			// ִ�� sql ��䡣    
			// mysql_query() �ķ���ֵ�ݺܶ����Σ� �����ж�ʹҪע�⡣    
			if (mysql_query(&db.m_sqlCon, update) == 0)
			{
				m_Num = _T("");
				m_Name = _T("");
				m_Sex = _T("");
				m_BirthDate = _T("");
				m_StartSchDate = _T("");
				m_Profession = _T("");
				UpdateData(FALSE);
				MessageBox(_T("ɾ���ɹ�"), _T("��ʾ"), MB_OK);
				reflash();
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


void StuInfo::OnBnClickedSave()
{
	mysql_set_character_set(&db.m_sqlCon, "GB2312");
	if (AlterOrAdd == 0)//���
	{
		char insert[1000];
		sprintf_s(insert, "insert into Student(number, name, sex, birthdate,startschool, profession) values (\'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\')"
			, num, name, sex, birdate, scdate, profess);
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
	else if (AlterOrAdd == 1) //����
	{
		char update[1000];
		sprintf_s(update, "update Student set name = \'%s\', sex= \'%s\', birthdate= \'%s\',startschool= \'%s\', profession= \'%s\' where number = \'%s\'"
			, name, sex, birdate, scdate, profess, num);
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


void StuInfo::OnBnClickedCancel()
{
	num = "";
	name = "";
	sex = "";
	birdate = "";
	scdate = "";
	profess = "";
	AlterOrAdd = -1;
	MessageBox(_T("ȡ������"), _T("��ʾ"), MB_OK);
}


void StuInfo::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void StuInfo::reflash()
{
	mysql_set_character_set(&db.m_sqlCon, "GB2312");
	char select[1000];
	sprintf_s(select, "select *from Student");
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
			StudentInfos * stu = new StudentInfos;
			stu->num.Format("%s", row[0]);
			stu->name.Format("%s", row[1]);
			stu->sex.Format("%s", row[2]);
			stu->birthdate.Format("%s", row[3]);
			stu->startschdate.Format("%s", row[4]);
			stu->profession.Format("%s", row[5]);
			m_Infos.push_back(stu);
		}
	}
}
