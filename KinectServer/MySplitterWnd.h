#pragma once

class CMySplitterWnd :  public CSplitterWnd  
{  
	DECLARE_DYNCREATE(CMySplitterWnd)  
public:   
	CMySplitterWnd(void);  
	virtual ~CMySplitterWnd(void);  

 
private:  

  
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()     
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};  
