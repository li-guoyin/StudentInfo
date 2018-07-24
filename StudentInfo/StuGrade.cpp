// StuGrade.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentInfo.h"
#include "StuGrade.h"
#include "afxdialogex.h"


// StuGrade 对话框

IMPLEMENT_DYNAMIC(StuGrade, CDialogEx)

StuGrade::StuGrade(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STUGRADE, pParent)
	, m_Num(_T(""))
	, m_CourseNumber(0)
	, m_CreditNumber(0)
	, m_AveGradeNumber(0)
{

}

StuGrade::StuGrade(Database d, CWnd * pParent)
	: CDialogEx(IDD_STUGRADE, pParent)
	, m_Num(_T(""))
	, m_CourseNumber(0)
	, m_CreditNumber(0)
	, m_AveGradeNumber(0)
{
	db = d;
	m_CouNum = 0;
	m_AveGrade = 0;
	m_AllGrade = 0;
	m_Credit = 0;
}

StuGrade::~StuGrade()
{
}

void StuGrade::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Num);
	DDX_Control(pDX, IDC_LIST1, m_GradeList);
	DDX_Text(pDX, IDC_COUNUM, m_CourseNumber);
	DDX_Text(pDX, IDC_CREDIT, m_CreditNumber);
	DDX_Text(pDX, IDC_AVEGRADE, m_AveGradeNumber);
}


BEGIN_MESSAGE_MAP(StuGrade, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &StuGrade::OnBnClickedSearch)
END_MESSAGE_MAP()


// StuGrade 消息处理程序


void StuGrade::OnBnClickedSearch()
{
	m_AllGrade = 0;

	UpdateData(TRUE);
	m_CourseNumber = 0;
	m_CreditNumber = 0;
	m_AveGradeNumber = 0;
	m_GradeList.DeleteAllItems();

	mysql_set_character_set(&db.m_sqlCon, "GB2312");

	char* num = m_Num.GetBuffer();
	m_Num.ReleaseBuffer();
	char select[1000];
	sprintf_s(select, "select *from selectcourse where stunumber = \'%s\'", num);
	// 执行 sql 语句。    
	// mysql_query() 的返回值份很多情形， 进行判断使要注意。    
	if (mysql_query(&db.m_sqlCon, select) == 0)
	{
		//AfxMessageBox(_T("查询数据成功!"));
		MYSQL_RES *res = mysql_store_result(&db.m_sqlCon); //读取将查询结果   
		MYSQL_FIELD *field = mysql_fetch_fields(res); //获取所有列名
		int field_count = mysql_field_count(&db.m_sqlCon); //获取列数  
		MYSQL_ROW row;
		int r = 0;
		while (row = mysql_fetch_row(res))
		{
			stunum.Format("%s", row[0]);
			coursenum.Format("%s", row[1]);
			grade.Format("%s", row[2]);
			
			char *snum = stunum.GetBuffer();
			stunum.ReleaseBuffer();
			char select1[1000];
			sprintf_s(select1, "select credit from course where numberCourse = \'%s\'", snum);
			if (mysql_query(&db.m_sqlCon, select1) == 0)
			{
				//AfxMessageBox(_T("查询数据成功!"));
				MYSQL_RES *res1 = mysql_store_result(&db.m_sqlCon); //读取将查询结果   
				MYSQL_FIELD *field = mysql_fetch_fields(res1); //获取所有列名
				int field_count1 = mysql_field_count(&db.m_sqlCon); //获取列数  
				MYSQL_ROW row1;
				while (row1 = mysql_fetch_row(res1))
				{
					credit.Format("%s", row1[0]);
				}
			}
			//插入列表控件
			m_GradeList.InsertItem(r, _T(""));
			m_GradeList.SetItemText(r, 0, stunum);
			m_GradeList.SetItemText(r, 1, coursenum);
			m_GradeList.SetItemText(r, 2, grade);
			m_GradeList.SetItemText(r, 3, credit);
			//课程总数
			m_CourseNumber++;

			float num1;
			num1 = atof(credit);
			float num2;
			num2 = atof(grade);

			m_CreditNumber += num1;
			m_AllGrade += num2;
			r++;
		}
		m_AveGradeNumber = m_AllGrade / m_CourseNumber;
		UpdateData(FALSE);
	}
	else {
		AfxMessageBox(_T("查询数据失败!"));
	}
}


BOOL StuGrade::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_GradeList.InsertColumn(0, "学号", LVCFMT_CENTER, 150);
	m_GradeList.InsertColumn(1, "课程号", LVCFMT_CENTER, 150);
	m_GradeList.InsertColumn(2, "成绩", LVCFMT_CENTER, 150);
	m_GradeList.InsertColumn(3, "学分", LVCFMT_CENTER, 150);
	m_GradeList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
