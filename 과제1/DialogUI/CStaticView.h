#pragma once


// CStaticView

class CStaticView : public CStatic
{
	DECLARE_DYNAMIC(CStaticView)

public:
	CStaticView();
	virtual ~CStaticView();
	void SetStartPos(CPoint pos);
	void SetEndPos(CPoint pos);
	void DrawFunc();
	void OperateFunc();

private:
	CPoint m_ptStartPos;
	CPoint m_ptEndPos;
	CPoint m_ptTemp;
	CBrush brush;
	int cmd;
	int radius;
	int imgIndex;

protected:
	DECLARE_MESSAGE_MAP()

	void SaveDCContentAsBMP(CWnd* pWnd, LPCTSTR filePath);


public:
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


