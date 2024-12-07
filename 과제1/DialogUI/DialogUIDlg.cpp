
// DialogUIDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "DialogUI.h"
#include "DialogUIDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CDialogUIDlg 对话框



CDialogUIDlg::CDialogUIDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGUI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDialogUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_START_X_POS, m_edtStartXPos);
	DDX_Control(pDX, IDC_EDIT_START_Y_POS, m_edtStartYPos);
	DDX_Control(pDX, IDC_EDIT_END_X_POS, m_edtEndXPos);
	DDX_Control(pDX, IDC_EDIT_END_Y_POS, m_edtEndYPos);
	DDX_Control(pDX, IDC_STATIC_VIEW, m_staticView);
}

BEGIN_MESSAGE_MAP(CDialogUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DRAW, &CDialogUIDlg::OnBnClickedButtonDraw)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE, &CDialogUIDlg::OnBnClickedButtonOperate)
END_MESSAGE_MAP()


// CDialogUIDlg 消息处理程序

BOOL CDialogUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDialogUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDialogUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDialogUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDialogUIDlg::OnBnClickedButtonDraw()
{
	CPoint ptStart, ptEnd;
	CString strText;
	m_edtStartXPos.GetWindowText(strText);
	if (strText.IsEmpty()) {
		AfxMessageBox(_T("start x pos is empty"));
		return;
	}
	ptStart.x = _wtoi(strText);
	m_edtStartYPos.GetWindowText(strText);
	if (strText.IsEmpty()) {
		AfxMessageBox(_T("start y pos is empty"));
		return;
	}
	ptStart.y = _wtoi(strText);
	m_edtEndXPos.GetWindowText(strText);
	if (strText.IsEmpty()) {
		AfxMessageBox(_T("end x pos is empty"));
		return;
	}
	ptEnd.x = _wtoi(strText);
	m_edtEndYPos.GetWindowText(strText);
	if (strText.IsEmpty()) {
		AfxMessageBox(_T("end y pos is empty"));
		return;
	}
	ptEnd.y = _wtoi(strText);

	m_staticView.SetStartPos(ptStart);
	m_staticView.SetEndPos(ptEnd);
	Invalidate();//刷新可以消除超出范围的绘制痕迹
	m_staticView.DrawFunc();
}


void CDialogUIDlg::OnBnClickedButtonOperate()
{
	CPoint ptStart, ptEnd;
	CString strText;
	m_edtStartXPos.GetWindowText(strText);
	if (strText.IsEmpty()) {
		AfxMessageBox(_T("start x pos is empty"));
		return;
	}
	ptStart.x = _wtoi(strText);
	m_edtStartYPos.GetWindowText(strText);
	if (strText.IsEmpty()) {
		AfxMessageBox(_T("start y pos is empty"));
		return;
	}
	ptStart.y = _wtoi(strText);
	m_edtEndXPos.GetWindowText(strText);
	if (strText.IsEmpty()) {
		AfxMessageBox(_T("end x pos is empty"));
		return;
	}
	ptEnd.x = _wtoi(strText);
	m_edtEndYPos.GetWindowText(strText);
	if (strText.IsEmpty()) {
		AfxMessageBox(_T("end y pos is empty"));
		return;
	}
	ptEnd.y = _wtoi(strText);

	m_staticView.SetStartPos(ptStart);
	m_staticView.SetEndPos(ptEnd);
	Invalidate();//刷新可以消除超出范围的绘制痕迹
	m_staticView.OperateFunc();
}
