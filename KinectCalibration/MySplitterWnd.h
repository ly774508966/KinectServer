#pragma once

class CMySplitterWnd :  public CSplitterWnd  
{  
	DECLARE_DYNCREATE(CMySplitterWnd)  
public:   
	CMySplitterWnd(void);  
	virtual ~CMySplitterWnd(void);  
public:
	DECLARE_MESSAGE_MAP()     
	virtual void OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect);

	int m_DColor_R;
	int m_DColor_G;
	int m_DColor_B;
	int m_LColor_R;
	int m_LColor_G;
	int m_LColor_B;
	BOOL m_bFirst;
};  

class CMySplitterWndStatic :  public CSplitterWnd  
{  
	DECLARE_DYNCREATE(CMySplitterWndStatic)  
public:   
	CMySplitterWndStatic(void);  
	virtual ~CMySplitterWndStatic(void);  
public:
	DECLARE_MESSAGE_MAP()     
	virtual void OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect);

	int m_DColor_R;
	int m_DColor_G;
	int m_DColor_B;
	int m_LColor_R;
	int m_LColor_G;
	int m_LColor_B;
	BOOL m_bFirst;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};  

