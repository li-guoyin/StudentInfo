// SelectCourse.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentInfo.h"
#include "SelectCourse.h"
#include "afxdialogex.h"


// SelectCourse 对话框

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


// SelectCourse 消息处理程序


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
	// 执行 sql 语句。    
	// mysql_query() 的返回值份很多情形， 进行判断使要注意。    
	if (mysql_query(&db.m_sqlCon, select) == 0)
	{
		//AfxMessageBox(_T("查询数据成功!"));
		MYSQL_RES *res = mysql_store_result(&db.m_sqlCon); //读取将查询结果   
		MYSQL_FIELD *field = mysql_fetch_fields(res); //获取所有列名
		int field_count = mysql_field_count(&db.m_sqlCon); //获取列数
		MYSQL_ROW row;
		while (row = mysql_fetch_row(res))
		{
			m_StuNum.Format("%s", row[0]);
			m_CouNum.Format("%s", row[1]);
			m_Grade.Format("%s", row[2]);
		}
		//根据课程id查课程名
		char* counum = m_CouNum.GetBuffer();
		m_CouNum.ReleaseBuffer();
		char select1[1000];
		sprintf_s(select1, "select nameCou from Course where numberCourse = \'%s\'", counum);
		if (mysql_query(&db.m_sqlCon, select1) == 0)
		{
			//AfxMessageBox(_T("查询数据成功!"));
			MYSQL_RES *res = mysql_store_result(&db.m_sqlCon); //读取将查询结果   
			MYSQL_FIELD *field = mysql_fetch_fields(res); //获取所有列名
			int field_count = mysql_field_count(&db.m_sqlCon); //获取列数
			MYSQL_ROW row;
			while (row = mysql_fetch_row(res))
			{
				m_CouName.Format("%s", row[0]);
			}
		}
		UpdateData(FALSE);
	}
	else {
		AfxMessageBox(_T("查询数据失败!"));
	}
}


void SelectCourse::OnBnClickedDelete()
{
	if (MessageBox(_T("是否要删除"), _T("提示"), MB_OKCANCEL) == IDOK)
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
			// 执行 sql 语句。    
			// mysql_query() 的返回值份很多情形， 进行判断使要注意。    
			if (mysql_query(&db.m_sqlCon, update) == 0)
			{
				m_StuNum = _T("");
				m_CouNum = _T("");
				m_Grade = _T("");
				m_CouName = _T("");
				UpdateData(FALSE);
				MessageBox(_T("删除成功"), _T("提示"), MB_OK);
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
		MessageBox(_T("点击保存，保存信息;\n点击取消，取消操作"), _T("提示"), MB_OK);
	}
	else
	{
		MessageBox(_T("请将信息填写完整"), _T("提示"), MB_OK);
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
			MessageBox(_T("课程ID及学生ID不能更改"), _T("提示"), MB_OK);
			return;
		}
		stunum = m_StuNum.GetBuffer();
		m_StuNum.ReleaseBuffer();
		counum = m_CouNum.GetBuffer();
		m_CouNum.ReleaseBuffer();
		grade = m_Grade.GetBuffer();
		m_Grade.ReleaseBuffer();
		AlterOrAdd = 1;
		MessageBox(_T("点击保存，保存信息;\n点击取消，取消操作"), _T("提示"), MB_OK);
	}
	else
	{
		MessageBox(_T("请将信息填写完整"), _T("提示"), MB_OK);
	}
}

//保存
void SelectCourse::OnBnClickedButton5()
{
	mysql_set_character_set(&db.m_sqlCon, "GB2312");
	if (AlterOrAdd == 0)
	{
		char insert[1000];
		sprintf_s(insert, "insert into selectcourse(stunumber, counumber, grade) values (\'%s\', \'%s\', \'%s\')"
			, stunum, counum, grade);
		// 执行 sql 语句。    
		// mysql_query() 的返回值份很多情形， 进行判断使要注意。    
		if (mysql_query(&db.m_sqlCon, insert) == 0)
		{
			MessageBox(_T("插入成功"), _T("提示"), MB_OK);
		}
		else
			MessageBox(_T("插入失败"), _T("提示"), MB_OK);
	}
	else if (AlterOrAdd == 1)
	{
		char update[1000];
		sprintf_s(update, "update selectcourse set grade= \'%s\' where stunumber = \'%s\' and counumber = \'%s\'"
			, grade, stunum, counum);
		// 执行 sql 语句。    
		// mysql_query() 的返回值份很多情形， 进行判断使要注意。    
		if (mysql_query(&db.m_sqlCon, update) == 0)
		{
			MessageBox(_T("更新成功"), _T("提示"), MB_OK);
		}
		else
			MessageBox(_T("更新失败"), _T("提示"), MB_OK);
	}
}

//取消
void SelectCourse::OnBnClickedButton6()
{
	stunum = "";
	counum = "";
	grade = "";
	AlterOrAdd = -1;
	MessageBox(_T("取消操作"), _T("提示"), MB_OK);
}
