
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "KinectServer.h"

#include "MainFrm.h"

#include "LeftView2.h"
#include "LeftView.h"
#include "MidView.h"
#include "RightView.h"
#include "ParamDlg.h"
#include "SettingDlg.h"
#include "time.h"
#include <stdio.h>
#include <io.h>
#include <mmsystem.h>
//#include <atlimage.h>
//#include <atlconv.h>
using namespace std;

#define  FRAPS 25

#include "USB5538/USB5538.h"
//#pragma	comment(lib,"USB5538_64.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND(ID_KINECT_GRAB, &CMainFrame::OnKinectGrab)
	ON_WM_TIMER()
	ON_COMMAND(ID_FILE_OPEN, &CMainFrame::OnFileOpen)
	ON_COMMAND(ID_KINECTBYMAN, &CMainFrame::OnKinectbyman)
	ON_UPDATE_COMMAND_UI(ID_KINECTBYMAN, &CMainFrame::OnUpdateKinectbyman)
	ON_COMMAND(ID_KINECT_PARAM, &CMainFrame::OnKinectParam)
	ON_WM_SIZE()
	ON_COMMAND(ID_SYS_SETTING, &CMainFrame::OnSysSetting)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// system: 在此添加成员初始化代码
	m_bIsPlay=false;
	m_bGrab=false;
	m_bRotateShow=false;
	m_nGetNum=0;
	m_nViewNum=2;
	m_nKinectNum=1;
	m_nNoPeopleTime=0;
	m_bByMan=false;
	m_nShowTime=0;
	m_bShowNewPoints = false;
	m_nNewPeople = NO_PEOPLE;
	m_bSaveFarData = false;
}
CMainFrame::~CMainFrame()
{
	if (m_hDevice != INVALID_HANDLE_VALUE)		// 如果设备句柄有效
	{
		USB5538_ReleaseDevice(m_hDevice);			// 释放设备对象
		m_hDevice = INVALID_HANDLE_VALUE;
	}
}
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("未能创建菜单栏\n");
		return -1;      // 未能创建
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// 防止菜单栏在激活时获得焦点
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// 允许用户定义的工具栏操作:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// system: 如果您不希望工具栏和菜单栏可停靠，请删除这五行
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 启用工具栏和停靠窗口菜单替换
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// 启用快速(按住 Alt 拖动)工具栏自定义
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// 加载用户定义的工具栏图像
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	// 启用菜单个性化(最近使用的命令)
	// system: 定义您自己的基本命令，确保每个下拉菜单至少有一个基本命令。
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);

	CMFCToolBar::SetBasicCommands(lstBasicCommands);

	return 0;
}
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// system: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断
#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG
// CMainFrame 消息处理程序
void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* 扫描菜单*/);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}
LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}
BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// 基类将执行真正的工作

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// 为所有用户工具栏启用自定义按钮
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}
void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWndEx::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(&rect);
	if (m_bRotateShow)
	{
		m_sMyPlitterWnd.SetColumnInfo(0,rect.Width()/2,0);
		m_sMyPlitterWnd.SetColumnInfo(1,0,0);
		m_sMyPlitterWnd.SetColumnInfo(2,0,0);
		m_sMyPlitterWnd.SetColumnInfo(3,rect.Width()/2,0);
		m_sMyPlitterWnd.RecalcLayout();
	}
}
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// system: 在此添加专用代码和/或调用基类
	m_sMyPlitterWnd.CreateStatic(this,1,4);
	CRect rect;
	GetClientRect(&rect);
	//设置在最右边，方便将来修改
	if (!m_sMyPlitterWnd.CreateView(0,0,RUNTIME_CLASS(CLeftView),CSize(0,rect.Height()),pContext)||
		!m_sMyPlitterWnd.CreateView(0,1,RUNTIME_CLASS(CMidView),CSize(rect.Width(),rect.Height()),pContext)||
		!m_sMyPlitterWnd.CreateView(0,2,RUNTIME_CLASS(CRightView),CSize(0,rect.Height()),pContext)||
		!m_sMyPlitterWnd.CreateView(0,3,RUNTIME_CLASS(CLeftView2),CSize(0,rect.Height()),pContext))
	{
		return FALSE;
	}
	return TRUE;
	return CFrameWndEx::OnCreateClient(lpcs, pContext);
}
void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==0)
	{
		KillTimer(0);
		memset(byDI,2,16);
		if(!USB5538_GetDeviceDI(m_hDevice, byDI))					// 读入各路开关量状态
		{
			m_hDevice = USB5538_CreateDevice(0);					// 创建设备对象
		} 

		if (m_bStartToShoot == true) {//强制将byDI[0]修改为0，使其进入拍摄状态
			byDI[0] = 0;
		}
		//byDI[0]=0; 说明检测到有人
		if (byDI[0]==0 || byDI[1]==0 ||byDI[2]==0 || m_nNewPeople==NEW_PEOPLE_IN)
		//if (false)//TODO
		{
			m_nNewPeople = OLD_PEOPLE_LEAVE;
			m_nNoPeopleTime=0;
			m_pRightView->m_bHasPeople=true;
			if (m_pMidView->m_Player.get_playState()!=1) //播放状态，1=停止，2=暂停，3=播放，6=正在缓冲，9=正在连接，10=准备就绪
			{
				m_pMidView->CloseVideo();
			}
			//提前提示用户
			if(m_nGetNum==1)
			{
				m_pRightView->m_sNoteText.SetWindowText(_T("正在合成3D图像！"));
			}
			//如果接收到来自客户端所有的数据
			if(m_nGetNum>=m_nKinectNum)
			{
				m_nGetNum=0;
				m_pLeftView->m_bFirstDraw = true;//左侧视图需要开始绘制
				//OnPlayVideo(2);
				RunPCLFusion();
				m_bRotateShow=true;
				//KillTimer(0);
				SetTimer(1,1000/FRAPS,NULL);
			}
			else if (m_bGrab==false)
			{
				m_bGrab=true;
				m_nGetNum=0;
				OnKinectGrab();
			}
		}
		//正处于旋转中
		else if (m_bRotateShow==true)
		{
			//什么都不做
		}
		//说明没有人
		else if (m_bGrab)
		{
			m_pRightView->m_bHasPeople=false;
		}
		else
		{
			m_nNoPeopleTime++;
			m_pRightView->m_bHasPeople=false;
			m_pRightView->m_bFinish=0;
			m_bRotateShow=false;
			m_nShowTime=0;
			if (m_bByMan ==0)
			{
				if (m_nViewNum!=2)
				{
					if (m_nNoPeopleTime>120)   //2分钟
						OnPlayVideo(1);        //待机
					else
						OnPlayVideo(2);        //来人
				}
				else
				{
					int playState=m_pMidView->m_Player.get_playState();  
					if (playState==1)   //播放完成
					{
						if (m_nNoPeopleTime>120)        //2分钟
							m_pMidView->PlayVideo(1);   //待机
						else
							m_pMidView->PlayVideo(2);   //来人
					}
				}
			}
		}
		SetTimer(0,1000,NULL);
	}
	else if(nIDEvent==1)
	{
		//正处于旋转中,转动......次,初始时设计为转动...圈
		if (m_bRotateShow==true && m_nShowTime<(10*360/m_pLeftView2->m_fDegreeDelta+ 1))
		{
			//需要判断新的平滑后的二进制流文件是否生成完毕
			int nPCLFusionState = GetPCLFusionState();
			if (nPCLFusionState>0&&m_nShowTime>5)//5是任意给出的小值，一开始肯定不会过滤结束
			{
				//进入这里，说明滤波完成，可以让LeftView2显示新的点云了
				USES_CONVERSION;
				//根据当前的PCL程序的处理进度状态，读取相应的文件
// 				if (nPCLFusionState==1)
// 				{
// 					CString sFileFrom = m_sGetName + _T("start1.flag");//重置文件名，确保能读取到下一个状态
// 					CString sFileTo = m_sGetName + _T("start.flag");
// 					rename(W2A(sFileFrom),W2A(sFileTo));
// 					m_pLeftView2->ReadPointAll(_T(".txt1"));
// 				}
				if (nPCLFusionState==2) {
					CString sFileFrom = m_sTargetPath + _T("start2.flag");//重置文件名，确保能读取到下一个状态
					CString sFileTo = m_sTargetPath + _T("finish.flag");
					rename(W2A(sFileFrom),W2A(sFileTo));
					m_pLeftView2->ReadPointAll(_T(".txt2"));
				}
				else if (nPCLFusionState==9) {//说明PCLFusion程序运行出现了错误
					CString sFileFrom = m_sTargetPath + _T("error.flag");//重置文件名，确保能读取到下一个状态
					CString sFileTo = m_sTargetPath + _T("finish.flag");
					rename(W2A(sFileFrom),W2A(sFileTo));
					MessageBox(L"数据错误，请尝试重新拍摄！", L"提示");
				}
				//m_bShowNewPoints = true;
//				m_nShowTime = 50*360/m_pLeftView2->m_fDegreeDelta;//继续转一定的圈数
			}
			m_nShowTime++;
			m_pLeftView->Invalidate(FALSE);
			m_pLeftView2->Invalidate(FALSE);
			memset(byDI,2,16);
			if(!USB5538_GetDeviceDI(m_hDevice, byDI))					// 读入各路开关量状态
			{
				m_hDevice = USB5538_CreateDevice(0);					// 创建设备对象
			} 
			//说明在旋转的过程中之前的人离开了，做出相关处理
			if (byDI[0]==0 && byDI[1]==0 && byDI[2]==0 &&m_nNewPeople==OLD_PEOPLE_LEAVE)//TODO:&& byDI[1]==0 && byDI[2]==0
			{
				m_nNewPeople = WAITFOR_NEW_PEOPLE;
				m_pRightView->m_nNoteTime = -1;
				m_pRightView->m_bHasPeople = false;
				m_pRightView->m_bFinish=0;
				m_bGrab=false;
			}
			//说明在旋转的过程中又重新进来了人，因此需要直接拍摄   || byDI[1]==1 ||byDI[2]==1
			if ((byDI[0]==1 || byDI[1]==1 ||byDI[2]==1)&&m_nNewPeople==WAITFOR_NEW_PEOPLE)
			{
				m_bShowNewPoints = false;
				m_pLeftView2->m_bRotateShow = false;
				m_bRotateShow = false;
				m_nNewPeople = NEW_PEOPLE_IN;
				KillTimer(1);
				SetTimer(0,1000,NULL);
			}
		}
		else
		{
			m_pLeftView2->m_bRotateShow = false;
			m_pRightView->m_bFinish=0;
			m_pRightView->m_nNoteTime = -1;
			m_pRightView->m_bHasPeople = false;
			m_bRotateShow = false;
			KillTimer(1);
			CRect rect;
			GetClientRect(&rect);
			m_sMyPlitterWnd.SetColumnInfo(0,0,0);
			m_sMyPlitterWnd.SetColumnInfo(1,rect.Width(),0);
			m_sMyPlitterWnd.SetColumnInfo(2,0,0);
			m_sMyPlitterWnd.SetColumnInfo(3,0,0);
			m_sMyPlitterWnd.RecalcLayout();
			m_bGrab=false;
			m_nViewNum=3;
			m_nNewPeople = NO_PEOPLE;
			m_nShowTime = 0;
			m_bShowNewPoints = false;
			SetTimer(0,500,NULL);
		}
	}
	CFrameWndEx::OnTimer(nIDEvent);
}

void CMainFrame::OnKinectGrab()
{
	KinectGrab();
	SetTimer(0,500,NULL);
}

void CMainFrame::KinectGrab()
{
	CRect rect;
	GetClientRect(&rect);
	m_sMyPlitterWnd.SetColumnInfo(0,0,0);
	m_sMyPlitterWnd.SetColumnInfo(1,0,0);
	m_sMyPlitterWnd.SetColumnInfo(2,rect.Width(),0);
	m_sMyPlitterWnd.SetColumnInfo(3,0,0);
	m_sMyPlitterWnd.RecalcLayout();
	m_nViewNum=3;
	if (m_bByMan!=1)
		m_pRightView->HideButtons();
	m_nNewPeople = OLD_PEOPLE_LEAVE;
	m_nNoPeopleTime=0;
	m_pRightView->m_nNoteTime = 5;
	m_pRightView->m_bHasPeople=true;
	m_bGrab=true;
	m_nGetNum=0;
	m_pRightView->OpenKinect();
}

void CMainFrame::OnShowPoint(CString filename)
{
	CRect rect;
	GetClientRect(&rect);
	int nWidth = (rect.Height()*640/480)*2/3;
	m_sMyPlitterWnd.SetColumnInfo(0,nWidth,0);
	m_sMyPlitterWnd.SetColumnInfo(1,0,0);
	m_sMyPlitterWnd.SetColumnInfo(2,0,0);
	m_sMyPlitterWnd.SetColumnInfo(3,rect.Width()-nWidth,0);
	m_sMyPlitterWnd.RecalcLayout();
	m_nViewNum=1;
	//开始循环播放
	m_pLeftView2->m_fDegreeY = 160.0;
	m_pLeftView2->m_bRotateShow = true;
	//m_pLeftView->Invalidate(TRUE);
	//m_pLeftView2->OnRotate();
}
void CMainFrame::OnPlayVideo(int i)
{
	CRect rect;
	GetClientRect(&rect);
	m_sMyPlitterWnd.SetColumnInfo(0,0,0);
	m_sMyPlitterWnd.SetColumnInfo(1,rect.Width(),0);
	m_sMyPlitterWnd.SetColumnInfo(2,0,0);
	m_sMyPlitterWnd.SetColumnInfo(3,0,0);
	m_sMyPlitterWnd.RecalcLayout();
	m_nViewNum=2;

	m_bIsPlay=true;
	m_pMidView->PlayVideo(i);
}
void CMainFrame::InitView()
{
	ReadSysTxt();

	m_pLeftView = (CLeftView *)m_sMyPlitterWnd.GetPane(0,0);
	m_pMidView = (CMidView *)m_sMyPlitterWnd.GetPane(0,1);
	m_pRightView = (CRightView *)m_sMyPlitterWnd.GetPane(0,2);
	m_pLeftView2 = (CLeftView2 *)m_sMyPlitterWnd.GetPane(0,3);
	m_nViewNum=0;
	CRect rect;
	m_pMidView->GetClientRect(&rect);
	m_pMidView->Init(rect);
	m_pRightView->Init(rect);

	m_hDevice = USB5538_CreateDevice(0);					// 创建设备对象
	if(m_hDevice==INVALID_HANDLE_VALUE) {
		AfxMessageBox(_T("感应器初始化失败!"));
	}
	//m_pRightView->OpenKinect();
	//if (m_bStartToShoot == true) {
	//	SetTimer(0,500,NULL);

	//}

	SetTimer(0,500,NULL);
}

void CMainFrame::ReadSysTxt()
{
	GetModuleFileName(NULL,m_sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	m_sPath.ReleaseBuffer();
	int pos = m_sPath.ReverseFind('\\');
	m_sPath = m_sPath.Left(pos);

	CString sPath,str;
	sPath=m_sPath+_T("\\初始文件\\info.ini");
	//GetPrivateProfileString(_T("sys"),_T("KINECTNUM"),_T(""),str.GetBuffer(200),200,sPath);
	//str.ReleaseBuffer();
	//m_nKinectNum=_ttoi(str);
	//if (m_nKinectNum<1)
	//	m_nKinectNum=1;
	m_bStartToShoot = GetPrivateProfileInt(_T("sys"),_T("IsStartToShoot"),0,sPath);
	m_bAutoShoot = GetPrivateProfileInt(_T("sys"),_T("IsAutoShoot"),0,sPath);
	m_bSaveFarData = GetPrivateProfileInt(_T("sys"),_T("IsSaveFarData"),0,sPath);
	m_nShootStyle = GetPrivateProfileInt(_T("sys"),_T("ShootStyle"),0,sPath);
	if (m_nShootStyle==0) {
		m_nKinectNum = 6;
	}else if (m_nShootStyle==1) {
		m_nKinectNum = 3;
	}
}

void CMainFrame::OnFileOpen()
{

}

void CMainFrame::OnSysSetting()
{
	CSettingDlg  settingdlg;
	settingdlg.DoModal();
}

void CMainFrame::OnKinectbyman()
{
	m_bByMan=!m_bByMan;
	OnKinectGrab();
}
void CMainFrame::OnUpdateKinectbyman(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bByMan);
}
void CMainFrame::OnKinectParam()
{
	MessageBox(L"请在KinectCalibration程序中修改这些矩阵变换参数", L"提示");
	/*CParamDlg  paramdlg;
	paramdlg.DoModal();*/
}
void CMainFrame::RunPCLFusion()
{
	//考虑在这里打开一个控制台应用，用于显示时间等信息，显示海报总共用了102秒的时间
	CString sTimeLocal;
	SYSTEMTIME stBegin,stEnd;
	GetLocalTime(&stBegin);

	//CString fname=m_sGetName;       //不需要后缀名
	USES_CONVERSION;
	CString param,newPath;
	m_sLastDxfTime.Format(_T("%02d_%02d_%02d"),stBegin.wHour, stBegin.wMinute, stBegin.wSecond);
	
	m_sLastDxfPath = _T("");
	m_sLastDxfPath = m_sTargetPath + _T("start.flag");//初始时为start
	
	FILE *fpFinishFlag;
	fpFinishFlag = fopen(W2A(m_sLastDxfPath),"a+");//创建一个标志文件
	fclose(fpFinishFlag);
	//newPath.Format(_T("\\ShareFolder\\.dxf"), );
	//newPath = m_sPath + _T("\\ShareFolder\\") + m_sLastDxfTime + _T(".dxf");
	//newPath = m_sPath + newPath;
	CString sShootStyle;
	sShootStyle.Format(L"%d", m_nShootStyle);
	param = m_sLastDxfTime + _T(" ") + m_sTargetPath + _T(" ") + sShootStyle;//分别为dxf保存路径、pcd文件保存路径、拍摄方式
	//int len = fname.GetLength();
	//fname.Right(1);
	CString path = m_sPath+"\\初始文件\\PCLFusion.exe";  //平滑处理
	SHELLEXECUTEINFO ShExecInfo = {0}; 
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO); 
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;  
	ShExecInfo.hwnd = NULL; 
	ShExecInfo.lpVerb = _T("open"); 
	ShExecInfo.lpFile = path; 
	ShExecInfo.lpParameters = param;//每一个空格代表一个新的参数
	ShExecInfo.lpDirectory = NULL; 
	ShExecInfo.nShow = SW_HIDE;
	ShExecInfo.hInstApp = NULL; 
	ShellExecuteEx(&ShExecInfo); 

	OnShowPoint(param+_T(".txt"));
}

int CMainFrame::GetPCLFusionState()
{
	USES_CONVERSION;
	CString sFlagDxf;
	sFlagDxf = m_sTargetPath + _T("start.flag");//正在处理中
	if(!access(W2A(sFlagDxf),0))
		return 0;
// 	sFlagDxf = m_sGetName + _T("start1.flag");//完成离群点的处理
// 	if(!access(W2A(sFlagDxf),0))
// 		return 1;
	sFlagDxf = m_sTargetPath + _T("start2.flag");//完成平滑的处理
	if(!access(W2A(sFlagDxf),0))
		return 2;
	sFlagDxf = m_sTargetPath + _T("error.flag");//PCLFusion运行时出错
	if(!access(W2A(sFlagDxf),0))
		return 9;
	return -1;
}
