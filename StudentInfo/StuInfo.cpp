// StuInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentInfo.h"
#include "StuInfo.h"
#include "afxdialogex.h"


// StuInfo 对话框

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
	//获取数据库
	db = d;
	count = 0;
	AlterOrAdd = -1;
	//从数据库初始化m_Infos,用于取上一条，下一条，第一条，末一条
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


// StuInfo 消息处理程序


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
		// 执行 sql 语句。    
		// mysql_query() 的返回值份很多情形， 进行判断使要注意。    
		if (mysql_query(&db.m_sqlCon, select) == 0)
		{
			//AfxMessageBox(_T("查询数据成功!"));
			MYSQL_RES *res = mysql_store_result(&db.m_sqlCon); //读取将查询结果   
			MYSQL_FIELD *field = mysql_fetch_fields(res); //获取所有列名
			int field_count = mysql_field_count(&db.m_sqlCon); //获取列数


															   //遍历输出每一行数据  
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
			AfxMessageBox(_T("查询数据失败!"));
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
		// 执行 sql 语句。    
		// mysql_query() 的返回值份很多情形， 进行判断使要注意。    
		if (mysql_query(&db.m_sqlCon, select) == 0)
		{
			//AfxMessageBox(_T("查询数据成功!"));
			MYSQL_RES *res = mysql_store_result(&db.m_sqlCon); //读取将查询结果   
			MYSQL_FIELD *field = mysql_fetch_fields(res); //获取所有列名
			int field_count = mysql_field_count(&db.m_sqlCon); //获取列数


															   //遍历输出每一行数据  
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
			AfxMessageBox(_T("查询数据失败!"));
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
		MessageBox(_T("已经是第一条"), _T("提示"), MB_OK);
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
		MessageBox(_T("已经是最后一条"), _T("提示"), MB_OK);
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
		MessageBox(_T("点击保存，保存信息;\n点击取消，取消操作"), _T("提示"), MB_OK);
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
		MessageBox(_T("请将信息填写完整"), _T("提示"), MB_OK);
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
			MessageBox(_T("学号不能更改"), _T("提示"), MB_OK);
			return;
		}
		MessageBox(_T("点击保存，保存信息;\n点击取消，取消操作"), _T("提示"), MB_OK);
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
		MessageBox(_T("请将信息填写完整"), _T("提示"), MB_OK);
	}
}


void StuInfo::OnBnClickedDelete()
{
	if (MessageBox(_T("是否要删除"), _T("提示"), MB_OKCANCEL) == IDOK)
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
			// 执行 sql 语句。    
			// mysql_query() 的返回值份很多情形， 进行判断使要注意。    
			if (mysql_query(&db.m_sqlCon, update) == 0)
			{
				m_Num = _T("");
				m_Name = _T("");
				m_Sex = _T("");
				m_BirthDate = _T("");
				m_StartSchDate = _T("");
				m_Profession = _T("");
				UpdateData(FALSE);
				MessageBox(_T("删除成功"), _T("提示"), MB_OK);
				reflash();
			}
			else
				MessageBox(_T("删除失败"), _T("提示"), MB_OK);
		}
		else
		{
			MessageBox(_T("要删除谁?"), _T("提示"), MB_OK);
		}
	}
	
}


void StuInfo::OnBnClickedSave()
{
	mysql_set_character_set(&db.m_sqlCon, "GB2312");
	if (AlterOrAdd == 0)//添加
	{
		char insert[1000];
		sprintf_s(insert, "insert into Student(number, name, sex, birthdate,startschool, profession) values (\'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\')"
			, num, name, sex, birdate, scdate, profess);
		// 执行 sql 语句。    
		// mysql_query() 的返回值份很多情形， 进行判断使要注意。    
		if (mysql_query(&db.m_sqlCon, insert) == 0)
		{
			MessageBox(_T("插入成功"), _T("提示"), MB_OK);
			reflash();
		}
		else
			MessageBox(_T("插入失败"), _T("提示"), MB_OK);
	}
	else if (AlterOrAdd == 1) //更新
	{
		char update[1000];
		sprintf_s(update, "update Student set name = \'%s\', sex= \'%s\', birthdate= \'%s\',startschool= \'%s\', profession= \'%s\' where number = \'%s\'"
			, name, sex, birdate, scdate, profess, num);
		// 执行 sql 语句。    
		// mysql_query() 的返回值份很多情形， 进行判断使要注意。    
		if (mysql_query(&db.m_sqlCon, update) == 0)
		{
			MessageBox(_T("更新成功"), _T("提示"), MB_OK);
			reflash();
		}
		else
			MessageBox(_T("更新失败"), _T("提示"), MB_OK);
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
	MessageBox(_T("取消操作"), _T("提示"), MB_OK);
}


void StuInfo::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void StuInfo::reflash()
{
	mysql_set_character_set(&db.m_sqlCon, "GB2312");
	char select[1000];
	sprintf_s(select, "select *from Student");
	// 执行 sql 语句。    
	// mysql_query() 的返回值份很多情形， 进行判断使要注意。    
	if (mysql_query(&db.m_sqlCon, select) == 0)
	{
		m_Infos.clear();
		//AfxMessageBox(_T("查询数据成功!"));
		MYSQL_RES *res = mysql_store_result(&db.m_sqlCon); //读取将查询结果   
		MYSQL_FIELD *field = mysql_fetch_fields(res); //获取所有列名
		int field_count = mysql_field_count(&db.m_sqlCon); //获取列数
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
