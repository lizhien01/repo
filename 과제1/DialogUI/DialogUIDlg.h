
// DialogUIDlg.h: 头文件
//

#pragma once
#include "CStaticView.h"


// CDialogUIDlg 对话框
class CDialogUIDlg : public CDialogEx
{
// 构造
public:
	CDialogUIDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edtStartXPos;
	CEdit m_edtStartYPos;
	CEdit m_edtEndXPos;
	CEdit m_edtEndYPos;
	CStaticView m_staticView;
	afx_msg void OnBnClickedButtonDraw();
	afx_msg void OnBnClickedButtonOperate();
};
