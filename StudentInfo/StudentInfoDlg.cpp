
// StudentInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentInfo.h"
#include "StudentInfoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CStudentInfoDlg �Ի���



CStudentInfoDlg::CStudentInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STUDENTINFO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//�������ݿ�
	bool isconnect = db.Connect();
}

void CStudentInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CStudentInfoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CStudentInfoDlg::OnBnClickedStuInfo)
	ON_BN_CLICKED(IDC_BUTTON2, &CStudentInfoDlg::OnBnClickedCourseInfo)
	ON_BN_CLICKED(IDC_BUTTON3, &CStudentInfoDlg::OnBnClickedSelectCourse)
	ON_BN_CLICKED(IDC_BUTTON4, &CStudentInfoDlg::OnBnClickedStuGrade)
	ON_BN_CLICKED(IDCANCEL, &CStudentInfoDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CStudentInfoDlg ��Ϣ�������

BOOL CStudentInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CStudentInfoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CStudentInfoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CStudentInfoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStudentInfoDlg::OnBnClickedStuInfo()
{
	m_StuInfo = new StuInfo(db);
	m_StuInfo->DoModal();
	delete m_StuInfo;
}


void CStudentInfoDlg::OnBnClickedCourseInfo()
{
	m_CourceInfo = new CourseInfo(db);
	m_CourceInfo->DoModal();
	delete m_CourceInfo;
}


void CStudentInfoDlg::OnBnClickedSelectCourse()
{
	m_SelectCourse = new SelectCourse(db);
	m_SelectCourse->DoModal();
	delete m_SelectCourse;
}


void CStudentInfoDlg::OnBnClickedStuGrade()
{
	m_StuGrade = new StuGrade(db);
	m_StuGrade->DoModal();
	delete m_StuGrade;
}


void CStudentInfoDlg::OnBnClickedCancel()
{
	if(MessageBox(_T("�Ƿ�Ҫ�뿪ϵͳ"), _T("��ʾ"), MB_OKCANCEL) == IDOK)
		CDialogEx::OnCancel();
}
