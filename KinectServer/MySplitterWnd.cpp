#include "stdafx.h"  
#include "MySplitterWnd.h"  
 
IMPLEMENT_DYNCREATE(CMySplitterWnd, CSplitterWnd)  
  
CMySplitterWnd::CMySplitterWnd(void)
{  
	m_cySplitterGap=1;
}  
   
CMySplitterWnd::~CMySplitterWnd(void)  
{  
}  

BEGIN_MESSAGE_MAP(CMySplitterWnd, CSplitterWnd)  
      
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()  

void CMySplitterWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// system: Add your message handler code here and/or call default

	CWnd::OnLButtonDown(nFlags, point);
}


void CMySplitterWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// system: Add your message handler code here and/or call default

	CWnd::OnMouseMove(nFlags, point);
}
