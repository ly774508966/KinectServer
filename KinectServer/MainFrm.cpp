
// MainFrm.cpp : CMainFrame ���ʵ��
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
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// system: �ڴ���ӳ�Ա��ʼ������
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
	if (m_hDevice != INVALID_HANDLE_VALUE)		// ����豸�����Ч
	{
		USB5538_ReleaseDevice(m_hDevice);			// �ͷ��豸����
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
		TRACE0("δ�ܴ����˵���\n");
		return -1;      // δ�ܴ���
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// ��ֹ�˵����ڼ���ʱ��ý���
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// �����û�����Ĺ���������:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// system: �������ϣ���������Ͳ˵�����ͣ������ɾ��������
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// ���ù�������ͣ�����ڲ˵��滻
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// ���ÿ���(��ס Alt �϶�)�������Զ���
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// �����û�����Ĺ�����ͼ��
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	// ���ò˵����Ի�(���ʹ�õ�����)
	// system: �������Լ��Ļ������ȷ��ÿ�������˵�������һ���������
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
	// system: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���
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
// CMainFrame ��Ϣ�������
void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* ɨ��˵�*/);
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
	// ���ཫִ�������Ĺ���

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// Ϊ�����û������������Զ��尴ť
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
	// system: �ڴ����ר�ô����/����û���
	m_sMyPlitterWnd.CreateStatic(this,1,4);
	CRect rect;
	GetClientRect(&rect);
	//���������ұߣ����㽫���޸�
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
		if(!USB5538_GetDeviceDI(m_hDevice, byDI))					// �����·������״̬
		{
			m_hDevice = USB5538_CreateDevice(0);					// �����豸����
		} 

		if (m_bStartToShoot == true) {//ǿ�ƽ�byDI[0]�޸�Ϊ0��ʹ���������״̬
			byDI[0] = 0;
		}
		//byDI[0]=0; ˵����⵽����
		if (byDI[0]==0 || byDI[1]==0 ||byDI[2]==0 || m_nNewPeople==NEW_PEOPLE_IN)
		//if (false)//TODO
		{
			m_nNewPeople = OLD_PEOPLE_LEAVE;
			m_nNoPeopleTime=0;
			m_pRightView->m_bHasPeople=true;
			if (m_pMidView->m_Player.get_playState()!=1) //����״̬��1=ֹͣ��2=��ͣ��3=���ţ�6=���ڻ��壬9=�������ӣ�10=׼������
			{
				m_pMidView->CloseVideo();
			}
			//��ǰ��ʾ�û�
			if(m_nGetNum==1)
			{
				m_pRightView->m_sNoteText.SetWindowText(_T("���ںϳ�3Dͼ��"));
			}
			//������յ����Կͻ������е�����
			if(m_nGetNum>=m_nKinectNum)
			{
				m_nGetNum=0;
				m_pLeftView->m_bFirstDraw = true;//�����ͼ��Ҫ��ʼ����
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
		//��������ת��
		else if (m_bRotateShow==true)
		{
			//ʲô������
		}
		//˵��û����
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
					if (m_nNoPeopleTime>120)   //2����
						OnPlayVideo(1);        //����
					else
						OnPlayVideo(2);        //����
				}
				else
				{
					int playState=m_pMidView->m_Player.get_playState();  
					if (playState==1)   //�������
					{
						if (m_nNoPeopleTime>120)        //2����
							m_pMidView->PlayVideo(1);   //����
						else
							m_pMidView->PlayVideo(2);   //����
					}
				}
			}
		}
		SetTimer(0,1000,NULL);
	}
	else if(nIDEvent==1)
	{
		//��������ת��,ת��......��,��ʼʱ���Ϊת��...Ȧ
		if (m_bRotateShow==true && m_nShowTime<(10*360/m_pLeftView2->m_fDegreeDelta+ 1))
		{
			//��Ҫ�ж��µ�ƽ����Ķ��������ļ��Ƿ��������
			int nPCLFusionState = GetPCLFusionState();
			if (nPCLFusionState>0&&m_nShowTime>5)//5�����������Сֵ��һ��ʼ�϶�������˽���
			{
				//�������˵���˲���ɣ�������LeftView2��ʾ�µĵ�����
				USES_CONVERSION;
				//���ݵ�ǰ��PCL����Ĵ������״̬����ȡ��Ӧ���ļ�
// 				if (nPCLFusionState==1)
// 				{
// 					CString sFileFrom = m_sGetName + _T("start1.flag");//�����ļ�����ȷ���ܶ�ȡ����һ��״̬
// 					CString sFileTo = m_sGetName + _T("start.flag");
// 					rename(W2A(sFileFrom),W2A(sFileTo));
// 					m_pLeftView2->ReadPointAll(_T(".txt1"));
// 				}
				if (nPCLFusionState==2) {
					CString sFileFrom = m_sTargetPath + _T("start2.flag");//�����ļ�����ȷ���ܶ�ȡ����һ��״̬
					CString sFileTo = m_sTargetPath + _T("finish.flag");
					rename(W2A(sFileFrom),W2A(sFileTo));
					m_pLeftView2->ReadPointAll(_T(".txt2"));
				}
				else if (nPCLFusionState==9) {//˵��PCLFusion�������г����˴���
					CString sFileFrom = m_sTargetPath + _T("error.flag");//�����ļ�����ȷ���ܶ�ȡ����һ��״̬
					CString sFileTo = m_sTargetPath + _T("finish.flag");
					rename(W2A(sFileFrom),W2A(sFileTo));
					MessageBox(L"���ݴ����볢���������㣡", L"��ʾ");
				}
				//m_bShowNewPoints = true;
//				m_nShowTime = 50*360/m_pLeftView2->m_fDegreeDelta;//����תһ����Ȧ��
			}
			m_nShowTime++;
			m_pLeftView->Invalidate(FALSE);
			m_pLeftView2->Invalidate(FALSE);
			memset(byDI,2,16);
			if(!USB5538_GetDeviceDI(m_hDevice, byDI))					// �����·������״̬
			{
				m_hDevice = USB5538_CreateDevice(0);					// �����豸����
			} 
			//˵������ת�Ĺ�����֮ǰ�����뿪�ˣ�������ش���
			if (byDI[0]==0 && byDI[1]==0 && byDI[2]==0 &&m_nNewPeople==OLD_PEOPLE_LEAVE)//TODO:&& byDI[1]==0 && byDI[2]==0
			{
				m_nNewPeople = WAITFOR_NEW_PEOPLE;
				m_pRightView->m_nNoteTime = -1;
				m_pRightView->m_bHasPeople = false;
				m_pRightView->m_bFinish=0;
				m_bGrab=false;
			}
			//˵������ת�Ĺ����������½������ˣ������Ҫֱ������   || byDI[1]==1 ||byDI[2]==1
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
	//��ʼѭ������
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

	m_hDevice = USB5538_CreateDevice(0);					// �����豸����
	if(m_hDevice==INVALID_HANDLE_VALUE) {
		AfxMessageBox(_T("��Ӧ����ʼ��ʧ��!"));
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
	sPath=m_sPath+_T("\\��ʼ�ļ�\\info.ini");
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
	MessageBox(L"����KinectCalibration�������޸���Щ����任����", L"��ʾ");
	/*CParamDlg  paramdlg;
	paramdlg.DoModal();*/
}
void CMainFrame::RunPCLFusion()
{
	//�����������һ������̨Ӧ�ã�������ʾʱ�����Ϣ����ʾ�����ܹ�����102���ʱ��
	CString sTimeLocal;
	SYSTEMTIME stBegin,stEnd;
	GetLocalTime(&stBegin);

	//CString fname=m_sGetName;       //����Ҫ��׺��
	USES_CONVERSION;
	CString param,newPath;
	m_sLastDxfTime.Format(_T("%02d_%02d_%02d"),stBegin.wHour, stBegin.wMinute, stBegin.wSecond);
	
	m_sLastDxfPath = _T("");
	m_sLastDxfPath = m_sTargetPath + _T("start.flag");//��ʼʱΪstart
	
	FILE *fpFinishFlag;
	fpFinishFlag = fopen(W2A(m_sLastDxfPath),"a+");//����һ����־�ļ�
	fclose(fpFinishFlag);
	//newPath.Format(_T("\\ShareFolder\\.dxf"), );
	//newPath = m_sPath + _T("\\ShareFolder\\") + m_sLastDxfTime + _T(".dxf");
	//newPath = m_sPath + newPath;
	CString sShootStyle;
	sShootStyle.Format(L"%d", m_nShootStyle);
	param = m_sLastDxfTime + _T(" ") + m_sTargetPath + _T(" ") + sShootStyle;//�ֱ�Ϊdxf����·����pcd�ļ�����·�������㷽ʽ
	//int len = fname.GetLength();
	//fname.Right(1);
	CString path = m_sPath+"\\��ʼ�ļ�\\PCLFusion.exe";  //ƽ������
	SHELLEXECUTEINFO ShExecInfo = {0}; 
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO); 
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;  
	ShExecInfo.hwnd = NULL; 
	ShExecInfo.lpVerb = _T("open"); 
	ShExecInfo.lpFile = path; 
	ShExecInfo.lpParameters = param;//ÿһ���ո����һ���µĲ���
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
	sFlagDxf = m_sTargetPath + _T("start.flag");//���ڴ�����
	if(!access(W2A(sFlagDxf),0))
		return 0;
// 	sFlagDxf = m_sGetName + _T("start1.flag");//�����Ⱥ��Ĵ���
// 	if(!access(W2A(sFlagDxf),0))
// 		return 1;
	sFlagDxf = m_sTargetPath + _T("start2.flag");//���ƽ���Ĵ���
	if(!access(W2A(sFlagDxf),0))
		return 2;
	sFlagDxf = m_sTargetPath + _T("error.flag");//PCLFusion����ʱ����
	if(!access(W2A(sFlagDxf),0))
		return 9;
	return -1;
}
