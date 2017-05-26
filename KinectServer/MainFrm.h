
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "MySplitterWnd.h"

#define CMD_NAME			1
#define CMD_OPENKINECT		2
#define CMD_GRAB			3
#define CMD_SAVE			5
#define CMD_BIAODING		6
#define CMD_SAVE_FAR  10
//#define CMD_BIAODING		6
#define CMD_DATA			7
#define CMD_DONE			9
#define nPort				6666

#define NO_PEOPLE 0
#define NEW_PEOPLE_IN 1
#define OLD_PEOPLE_LEAVE 2
#define WAITFOR_NEW_PEOPLE 3
//#define Mindepth			600
//#define Maxdepth			1700
#define WAITTIME            5

class CLeftView;
class CLeftView2;
class CMidView;
class CRightView;
class CMainFrame : public CFrameWndEx
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:
	CMySplitterWnd	m_sMyPlitterWnd;
	CLeftView* m_pLeftView;
	CLeftView2* m_pLeftView2;
	CMidView* m_pMidView;
	CRightView* m_pRightView;
	CRITICAL_SECTION     m_lockParams;
	
	CString		m_sLastDxfTime;//���һ�α����dxf�ļ���·������Ҫ��ȷ��ʱ�䣩
	CString		m_sLastDxfPath;
	CString     m_sPath;
	USHORT	m_nKinectNum;
	USHORT	m_nGetNum;
	UINT		m_nGetPoint;
	CString		m_sTargetPath;//��ǰ�����ļ���Ŀ��Ŀ¼
	HANDLE	m_hDevice;
	bool			m_bIsPlay;
	bool			m_bGrab;
	bool			m_bRotateShow;
	short		m_nViewNum;
	bool			m_bByMan;
	bool			m_bShowNewPoints;
	
	bool			m_bAutoShoot;//�Ƿ��Զ�������һ������
	bool			m_bStartToShoot;//�Ƿ�����������Զ����뵹��ʱ����
	bool			m_bSaveFarData;//�Ƿ���Զ�̱��汸������
	int			m_nShootStyle;//���㷽ʽ 0:�������塢1:�����ϰ���

	int			m_nNoPeopleTime;
	int			m_nShowTime;
//	int			m_nTest;
	
	BYTE			byDI[16];
	int			m_nNewPeople;

	int GetPCLFusionState();
	void	InitView();
	void	ReadSysTxt();
	void	ReadFile();
	void	OnShowPoint(CString filename);
	void	OnPlayVideo(int i);
	void    RunPCLFusion();
// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	void	KinectGrab();//�ֶ������ʼ�����ִ�еľ��巽��
	afx_msg void OnKinectGrab();//�ֶ������ʼ���㣬��������һ���¶�ʱ��
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnFileOpen();
	afx_msg void OnKinectbyman();
	afx_msg void OnUpdateKinectbyman(CCmdUI *pCmdUI);
	afx_msg void OnKinectParam();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSysSetting();
};


