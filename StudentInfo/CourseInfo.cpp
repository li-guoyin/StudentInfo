// CourseInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentInfo.h"
#include "CourseInfo.h"
#include "afxdialogex.h"


// CourseInfo 对话框

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
	//从数据库初始化m_Infos,用于取上一条，下一条，第一条，末一条
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


// CourseInfo 消息处理程序


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
		AfxMessageBox(_T("查询数据失败!"));
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
		MessageBox(_T("点击保存，保存信息;\n点击取消，取消操作"), _T("提示"), MB_OK);
		AlterOrAdd = 0;
	}
	else
	{
		MessageBox(_T("请将信息填写完整"), _T("提示"), MB_OK);
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
			MessageBox(_T("课程号不能更改"), _T("提示"), MB_OK);
			return;
		}
		num = m_Num.GetBuffer();
		m_SearchNum.ReleaseBuffer();
		name = m_Name.GetBuffer();
		m_SearchName.ReleaseBuffer();
		credit = m_Credit.GetBuffer();
		m_Credit.ReleaseBuffer();
		MessageBox(_T("点击保存，保存信息;\n点击取消，取消操作"), _T("提示"), MB_OK);
		AlterOrAdd = 1;
		
	}
	else
	{
		MessageBox(_T("请将信息填写完整"), _T("提示"), MB_OK);
	}
}


void CourseInfo::OnBnClickedDelete()
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
			sprintf_s(update, "delete from Course where numberCourse = \'%s\'"
				, num);
			// 执行 sql 语句。    
			// mysql_query() 的返回值份很多情形， 进行判断使要注意。    
			if (mysql_query(&db.m_sqlCon, update) == 0)
			{
				m_Num = _T("");
				m_Name = _T("");
				m_Credit = _T("");
				UpdateData(FALSE);
				MessageBox(_T("删除成功"), _T("提示"), MB_OK);
				reflash();
			}
			else
				MessageBox(_T("删除失败"), _T("提示"), MB_OK);
		}
		else
		{
			MessageBox(_T("要删除什么课程?"), _T("提示"), MB_OK);
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
		MessageBox(_T("已经是第一条"), _T("提示"), MB_OK);
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
		MessageBox(_T("已经是最后一条"), _T("提示"), MB_OK);
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
			CourseInfos * cou = new CourseInfos;
			cou->num.Format("%s", row[0]);
			cou->name.Format("%s", row[1]);
			cou->credit.Format("%s", row[2]);
			m_Infos.push_back(cou);
		}
	}
}

//保存
void CourseInfo::OnBnClickedButton9()
{
	mysql_set_character_set(&db.m_sqlCon, "GB2312");
	if (AlterOrAdd == 0)
	{
		char insert[1000];
		sprintf_s(insert, "insert into Course(numberCourse, nameCou, credit) values (\'%s\', \'%s\', \'%s\')"
			, num, name, credit);
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
	else if (AlterOrAdd == 1)
	{
		char update[1000];
		sprintf_s(update, "update Course set nameCou = \'%s\', credit= \'%s\' where numberCourse = \'%s\'"
			, name, credit,num);
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

//取消
void CourseInfo::OnBnClickedButton10()
{
	num = "";
	name = "";
	credit = "";
	AlterOrAdd = -1;
	MessageBox(_T("取消操作"), _T("提示"), MB_OK);
}
