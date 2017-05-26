#pragma once

#include "afxwin.h"
#include "resource.h"
#include "KinectServerDoc.h"
#include "afxcmn.h"

#include "mediaplayer.h"
#include "CWMPControls.h"
#include "CWMPMedia.h"
#include "CWMPPlayer4.h"
#include "CWMPPlaylist.h"
#include "CWMPSettings.h"
#include "ocx1.h"

// CMidView 窗体视图
class CLeftView;
class CRightView;
class CMainFrame;
class CMidView : public CFormView
{
	DECLARE_DYNCREATE(CMidView)

protected:
	CMidView();           // 动态创建所使用的受保护的构造函数
	virtual ~CMidView();

public:
	enum { IDD = IDD_MIDVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	CLeftView*	m_pLeftView;
	CRightView* m_pRightView;
	CMainFrame* m_pMainFrame;

	CWMPSettings m_Setting;
	CWMPControls m_Control; 
	CString m_sPath;
	CWMPPlayer4 m_Player;

	BOOL m_bIsPlaying;
	int	 m_nGetNum;
	CString m_sGetName;
	HANDLE		m_hDevice;
	BOOL        m_bIfGrab;
	BOOL        m_bRotateShow;
	int         m_nShowTime;
	int			m_nCenterx;
	int			m_nCentery;

	int			m_nPicW;
	int			m_nPicH;

	void PlayVideo(int i);
	void CloseVideo();
	void Init(CRect rect);
	void ShowPic(CStatic* pWnd,CString fname , int x,int y);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


