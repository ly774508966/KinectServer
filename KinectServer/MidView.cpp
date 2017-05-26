// LeftView.cpp : 实现文件
//

#include "stdafx.h"
#include "KinectServer.h"
#include "MidView.h"
#include "MainFrm.h"

#include <atlimage.h>


// CMidView

IMPLEMENT_DYNCREATE(CMidView, CFormView)

CMidView::CMidView()
	: CFormView(CMidView::IDD)
{
	m_bIsPlaying=0;
	m_bIfGrab=false;
	m_hDevice = INVALID_HANDLE_VALUE;
}

CMidView::~CMidView()
{
}

void CMidView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OCX1, m_Player);
}

BEGIN_MESSAGE_MAP(CMidView, CFormView)
		ON_WM_CREATE()
END_MESSAGE_MAP()


// CMidView 诊断

#ifdef _DEBUG
void CMidView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMidView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


int CMidView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CMidView::Init(CRect rect)
{
	GetModuleFileName(NULL,m_sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	m_sPath.ReleaseBuffer();
	int pos = m_sPath.ReverseFind('\\');
	m_sPath = m_sPath.Left(pos);

	//CRect rect1;
	//GetClientRect(&rect1);

	m_pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	m_nPicW=300;
	m_nPicH=500;
	
	GetDlgItem(IDC_IMAGE_1)->MoveWindow(0,(rect.Height()-m_nPicH)/2,m_nPicW,m_nPicH);
	/*GetDlgItem(IDC_IMAGE_2)->MoveWindow(0,m_nPicH,m_nPicW,m_nPicH);
	GetDlgItem(IDC_IMAGE_3)->MoveWindow(0,m_nPicH*2,m_nPicW,m_nPicH);
	GetDlgItem(IDC_IMAGE_4)->MoveWindow(0,m_nPicH*3,m_nPicW,m_nPicH);
	GetDlgItem(IDC_IMAGE_5)->MoveWindow(0,m_nPicH*4,m_nPicW,m_nPicH);*/

	m_Player.MoveWindow(m_nPicW,0,rect.Width()-m_nPicW,rect.Height());

	CString fname;
	CStatic *pWnd=(CStatic*)GetDlgItem(IDC_IMAGE_1);
	fname.Format(_T("提示%d.bmp"),1);
	ShowPic(pWnd,fname,0,0);

	/*pWnd=(CStatic*)GetDlgItem(IDC_IMAGE_2);
	fname.Format(_T("提示%d.bmp"),2);
	ShowPic(pWnd,fname,0,m_nPicH);

	pWnd=(CStatic*)GetDlgItem(IDC_IMAGE_3);
	fname.Format(_T("提示%d.bmp"),3);
	ShowPic(pWnd,fname,0,m_nPicH*2);

	pWnd=(CStatic*)GetDlgItem(IDC_IMAGE_4);
	fname.Format(_T("提示%d.bmp"),4);
	ShowPic(pWnd,fname,0,m_nPicH*3);

	pWnd=(CStatic*)GetDlgItem(IDC_IMAGE_5);
	fname.Format(_T("提示%d.bmp"),5);
	ShowPic(pWnd,fname,0,m_nPicH*4);*/
}
void CMidView::PlayVideo(int i)
{
	CString  PathName;
	int playtimes=1;
	m_bIsPlaying=1;	
	switch (i)
	{
	case 1:
		PathName=m_sPath+_T("\\初始文件\\A_待机.mp4"); 
		playtimes=1;
		break;
	case 2:
		PathName=m_sPath+_T("\\初始文件\\A_来人.mp4"); 
		playtimes=1;
		break;
	default:
		PathName=m_sPath+_T("\\初始文件\\A_待机.mp4"); 
		playtimes=1;
		break;
	}

	m_Setting=m_Player.get_settings();
	m_Setting.put_playCount(playtimes);
	m_Player.put_URL(PathName);
}

void CMidView::CloseVideo()
{
	m_Player.close();
}

void CMidView::ShowPic(CStatic* pWnd,CString fname ,int x,int y) 
{
	CString BmpName=m_sPath+_T("\\初始文件\\")+fname;
	HBITMAP  hbitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),BmpName,IMAGE_BITMAP,m_nPicW,
						m_nPicH,LR_LOADFROMFILE);   
	pWnd->SetBitmap(hbitmap);    

}