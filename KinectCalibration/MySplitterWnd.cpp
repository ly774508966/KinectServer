#include "stdafx.h"  
#include "MySplitterWnd.h"  
#include "MainFrm.h"


IMPLEMENT_DYNCREATE(CMySplitterWnd, CSplitterWnd)  
IMPLEMENT_DYNCREATE(CMySplitterWndStatic, CSplitterWnd)  

	CMySplitterWnd::CMySplitterWnd(void)
{  
	m_cxBorderShare = 0; //�������ʱ�����϶�����ƫ����
	m_cyBorderShare = 0; //�������ʱ�����϶�����ƫ����
	m_cxSplitterGap= 9; //��ֹʱ�����϶����Ŀ��   
	m_cySplitterGap= 5; //��ֹʱ�����϶����Ŀ��
	m_cxBorder=0;
	m_cyBorder=0;          // ���
	m_bFirst = FALSE;
}  

CMySplitterWnd::~CMySplitterWnd(void)  
{  

}  

BEGIN_MESSAGE_MAP(CMySplitterWnd, CSplitterWnd)  
END_MESSAGE_MAP()  

void CMySplitterWnd::OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect)
{
	if(!m_bFirst)
	{
		m_bFirst = 1;//�ⲿ������ִ��һ�β��ܳɹ�
		return;//�˳�
	}
	//��һ�λ��ƽ���֮����ܵõ�����ܵ�ָ��
	CMainFrame *pFrm = (CMainFrame*)AfxGetMainWnd();
	if(pFrm)
	{
		COLORREF m_DColor = RGB(30,30,30);
		COLORREF m_LColor = RGB(165,165,165);
		m_DColor_R = GetRValue(m_DColor);
		m_DColor_G = GetGValue(m_DColor);
		m_DColor_B = GetBValue(m_DColor);
		m_LColor_R = GetRValue(m_LColor);
		m_LColor_G = GetGValue(m_LColor);
		m_LColor_B = GetBValue(m_LColor);

		if(nType== splitBar && pDC!=NULL)//�жϻ��ָ���ʱ
		{
			CRect m_rect = rect;
			if(rect.Width()<15)//����ָ���
			{
				//int m= rect.Width(); 
				for(int k = 0;k<rect.Width()+1;k++)
				{
					m_rect.left = rect.right-k;
					m_rect.right = rect.right-k+1;
					CBrush brush(RGB(
						m_DColor_R+k*((m_LColor_R-m_DColor_R)/rect.Width()),//m_cxSplitterGap
						m_DColor_G+k*((m_LColor_G-m_DColor_G)/rect.Width()),
						m_DColor_B+k*((m_LColor_B-m_DColor_B)/rect.Width())
						));//��ɫ��ˢ
					pDC->FillRect(&m_rect,&brush);
				}
			}
			else//����ָ���
			{
				//int m= rect.Height();
				for(int k = 0;k<rect.Height();k++)
				{
					m_rect.top = rect.bottom-k-1;
					m_rect.bottom = rect.bottom-k;
					CBrush brush(RGB(
						m_DColor_R+k*((m_LColor_R-m_DColor_R)/rect.Height()),//m_cySplitterGap
						m_DColor_G+k*((m_LColor_G-m_DColor_G)/rect.Height()),
						m_DColor_B+k*((m_LColor_B-m_DColor_B)/rect.Height())
						));//��ɫ��ˢ
					pDC->FillRect(&m_rect,&brush);
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////


	CMySplitterWndStatic::CMySplitterWndStatic(void)
{  
	m_cxBorderShare = 0; //�������ʱ�����϶�����ƫ����
	m_cyBorderShare = 0; //�������ʱ�����϶�����ƫ����
	m_cxSplitterGap= 9; //��ֹʱ�����϶����Ŀ��   
	m_cySplitterGap= 5; //��ֹʱ�����϶����Ŀ��
	m_cxBorder=0;
	m_cyBorder=0;          // ���
	m_bFirst = FALSE;
}  

CMySplitterWndStatic::~CMySplitterWndStatic(void)  
{  

}  

BEGIN_MESSAGE_MAP(CMySplitterWndStatic, CSplitterWnd)  
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()  

void CMySplitterWndStatic::OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect)
{
	if(!m_bFirst)
	{
		m_bFirst = 1;//�ⲿ������ִ��һ�β��ܳɹ�
		return;//�˳�
	}
	//��һ�λ��ƽ���֮����ܵõ�����ܵ�ָ��
	CMainFrame *pFrm = (CMainFrame*)AfxGetMainWnd();
	if(pFrm)
	{
		COLORREF m_DColor = RGB(30,30,30);
		COLORREF m_LColor = RGB(165,165,165);
		m_DColor_R = GetRValue(m_DColor);
		m_DColor_G = GetGValue(m_DColor);
		m_DColor_B = GetBValue(m_DColor);
		m_LColor_R = GetRValue(m_LColor);
		m_LColor_G = GetGValue(m_LColor);
		m_LColor_B = GetBValue(m_LColor);

		if(nType== splitBar && pDC!=NULL)//�жϻ��ָ���ʱ
		{
			CRect m_rect = rect;
			if(rect.Width()<15)//����ָ���
			{
				//int m= rect.Width(); 
				for(int k = 0;k<rect.Width()+1;k++)
				{
					m_rect.left = rect.right-k;
					m_rect.right = rect.right-k+1;
					CBrush brush(RGB(
						m_DColor_R+k*((m_LColor_R-m_DColor_R)/rect.Width()),//m_cxSplitterGap
						m_DColor_G+k*((m_LColor_G-m_DColor_G)/rect.Width()),
						m_DColor_B+k*((m_LColor_B-m_DColor_B)/rect.Width())
						));//��ɫ��ˢ
					pDC->FillRect(&m_rect,&brush);
				}
			}
			else//����ָ���
			{
				//int m= rect.Height();
				for(int k = 0;k<rect.Height();k++)
				{
					m_rect.top = rect.bottom-k-1;
					m_rect.bottom = rect.bottom-k;
					CBrush brush(RGB(
						m_DColor_R+k*((m_LColor_R-m_DColor_R)/rect.Height()),//m_cySplitterGap
						m_DColor_G+k*((m_LColor_G-m_DColor_G)/rect.Height()),
						m_DColor_B+k*((m_LColor_B-m_DColor_B)/rect.Height())
						));//��ɫ��ˢ
					pDC->FillRect(&m_rect,&brush);
				}
			}
		}
	}
}




void CMySplitterWndStatic::OnLButtonDown(UINT nFlags, CPoint point)
{

	CWnd::OnLButtonDown(nFlags, point);
}


void CMySplitterWndStatic::OnMouseMove(UINT nFlags, CPoint point)
{
	CWnd::OnMouseMove(nFlags, point);
}
