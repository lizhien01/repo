// CStaticView.cpp: 实现文件
//

#include "pch.h"
#include "DialogUI.h"
#include "CStaticView.h"


// CStaticView

IMPLEMENT_DYNAMIC(CStaticView, CStatic)

CStaticView::CStaticView():cmd(0),radius(0),imgIndex(1)
{
	srand(time(NULL));
	brush.CreateSolidBrush(RGB(255, 255, 255));
}

CStaticView::~CStaticView()
{
}


BEGIN_MESSAGE_MAP(CStaticView, CStatic)
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CStaticView 消息处理程序


void CStaticView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CStatic::OnPaint()
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(0, 0, 0));
	if (cmd == 1)
	{
		CBrush* pOldBrush = dc.SelectObject(&brush);
		dc.Ellipse(m_ptStartPos.x - radius, m_ptStartPos.y - radius,
			m_ptStartPos.x + radius, m_ptStartPos.y + radius);
		dc.SelectObject(pOldBrush);
		cmd = 0;
	}
	else if (cmd == 2)
	{
		CBrush* pOldBrush = dc.SelectObject(&brush);
		dc.Ellipse(m_ptTemp.x - radius, m_ptTemp.y - radius,
			m_ptTemp.x + radius, m_ptTemp.y + radius);
		dc.SelectObject(pOldBrush);
	}
}


void CStaticView::SetStartPos(CPoint pos) {
	m_ptStartPos = pos;
}


void CStaticView::SetEndPos(CPoint pos) {
	m_ptEndPos = pos;
}


void CStaticView::DrawFunc()
{
	if (cmd == 0)
	{
		cmd = 1;
		radius = rand() % 10 + 30;
		Invalidate();
	}
}


void CStaticView::OperateFunc()
{
	if (cmd == 0)
	{
		cmd = 2;
		m_ptTemp = m_ptStartPos;
		radius = rand() % 10 + 30;
		imgIndex = 1;
		Invalidate();
		SetTimer(1, 1000, NULL);
	}
}

void CStaticView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_ptTemp == m_ptEndPos)
	{
		KillTimer(1);
		cmd = 0;
		AfxMessageBox(_T("Finish!"));
	}
	else
	{
		CString strPath;
		strPath.Format(_T("images/%d.bmp"), imgIndex++);
		SaveDCContentAsBMP(this, strPath);
		if (m_ptTemp.x < m_ptEndPos.x) {
			m_ptTemp.x += 10;
			if (m_ptTemp.x > m_ptEndPos.x)
				m_ptTemp.x = m_ptEndPos.x;
		}
		else if (m_ptTemp.x > m_ptEndPos.x) {
			m_ptTemp.x -= 10;
			if (m_ptTemp.x < m_ptEndPos.x)
				m_ptTemp.x = m_ptEndPos.x;
		}

		if (m_ptTemp.y < m_ptEndPos.y) {
			m_ptTemp.y += 10;
			if (m_ptTemp.y > m_ptEndPos.y)
				m_ptTemp.y = m_ptEndPos.y;
		}
		else if (m_ptTemp.y > m_ptEndPos.y) {
			m_ptTemp.y -= 10;
			if (m_ptTemp.y < m_ptEndPos.y)
				m_ptTemp.y = m_ptEndPos.y;
		}
		Invalidate();
	}
	CStatic::OnTimer(nIDEvent);
}

void CStaticView::SaveDCContentAsBMP(CWnd* pWnd, LPCTSTR filePath)
{
	CPaintDC dc(pWnd);
	CRect rect;
	pWnd->GetClientRect(&rect);

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

	memDC.BitBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, SRCCOPY);

	CImage image;
	image.Attach(bitmap);
	HRESULT hr = image.Save(filePath, Gdiplus::ImageFormatBMP);
	if (FAILED(hr))
	{
		AfxMessageBox(_T("Failed to save BMP file!"));
	}
	memDC.SelectObject(pOldBitmap);
}
