
// MainFrm.h : CMainFrame 类的接口
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
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:
	CMySplitterWnd	m_sMyPlitterWnd;
	CLeftView* m_pLeftView;
	CLeftView2* m_pLeftView2;
	CMidView* m_pMidView;
	CRightView* m_pRightView;
	CRITICAL_SECTION     m_lockParams;
	
	CString		m_sLastDxfTime;//最近一次保存的dxf文件的路径（主要是确定时间）
	CString		m_sLastDxfPath;
	CString     m_sPath;
	USHORT	m_nKinectNum;
	USHORT	m_nGetNum;
	UINT		m_nGetPoint;
	CString		m_sTargetPath;//当前存入文件的目标目录
	HANDLE	m_hDevice;
	bool			m_bIsPlay;
	bool			m_bGrab;
	bool			m_bRotateShow;
	short		m_nViewNum;
	bool			m_bByMan;
	bool			m_bShowNewPoints;
	
	bool			m_bAutoShoot;//是否自动进行下一次拍摄
	bool			m_bStartToShoot;//是否程序启动后自动进入倒计时拍摄
	bool			m_bSaveFarData;//是否在远程保存备份数据
	int			m_nShootStyle;//拍摄方式 0:拍摄整体、1:拍摄上半身

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
// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	void	KinectGrab();//手动点击开始拍摄后执行的具体方法
	afx_msg void OnKinectGrab();//手动点击开始拍摄，重启开启一个新定时器
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnFileOpen();
	afx_msg void OnKinectbyman();
	afx_msg void OnUpdateKinectbyman(CCmdUI *pCmdUI);
	afx_msg void OnKinectParam();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSysSetting();
};


