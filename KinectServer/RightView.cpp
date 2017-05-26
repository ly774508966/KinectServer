// RightView.cpp : 实现文件
//

#include "stdafx.h"
#include "KinectServer.h"
#include "RightView.h"
#include "LeftView.h"
#include "LeftView2.h"
#include "MainFrm.h"
#include "Socket_client.h"
#include <atlimage.h>
#include <mmsystem.h>

#define _FILTER_GROUND_
//把二维的数组与一维数组的转换，也可以直接用二维数组，只是我的习惯是不用二维数组
#define ParaBuffer(Buffer,Row,Col) (*(Buffer + (Row) * (SizeSrc + 1) + (Col)))
#define WEISHU 3//数组维数

POINT3D prMax;
POINT3D prMin;
float fx=(float)(1.0/525.0);
float fy=(float)(1.0/525.0);
// CRightView

IMPLEMENT_DYNCREATE(CRightView, CFormView)

	CRightView::CRightView()
	: CFormView(CRightView::IDD)
{
	m_pD2DFactory =NULL;
	m_pDrawColor=NULL;
	m_nSensorCount=0;
	m_bSave=0;
	m_ShowID=0;
	m_bHasPeople=0;
	m_bFinish=0;
	m_nPCNum=0;
	m_bFilterGround =true;
	m_bSaveByTimes = false;
}

CRightView::~CRightView()
{
	delete m_pKinect[0];
	delete m_pKinect[1];
	for (int i=0;i<m_nPCNum;i++)
	{
		delete m_pClientSocket[i];
	}
	if (m_pDrawColor != NULL)
	{
		delete m_pDrawColor;
	}
	if (m_pD2DFactory != NULL)
	{
		m_pD2DFactory=NULL;
		delete m_pD2DFactory;
	}
}

void CRightView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NOTETEXT, m_sNoteText);
	DDX_Control(pDX, IDC_BTN_SAVEONE, m_btnSaveOne);
}

BEGIN_MESSAGE_MAP(CRightView, CFormView)

	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_SAVE, &CRightView::OnBnClickedSave)
	ON_BN_CLICKED(IDC_DEGREE1, &CRightView::OnBnClickedDegree1)
	ON_BN_CLICKED(IDC_DEGREE_UP1, &CRightView::OnBnClickedDegreeUp1)
	ON_BN_CLICKED(IDC_DEGREE_DOWN1, &CRightView::OnBnClickedDegreeDown1)
	ON_BN_CLICKED(IDC_BTN_SAVEONE, &CRightView::OnBnClickedSaveOne)
	ON_BN_CLICKED(IDC_DEGREE2, &CRightView::OnBnClickedDegree2)
	ON_BN_CLICKED(IDC_DEGREE_UP2, &CRightView::OnBnClickedDegreeUp2)
	ON_BN_CLICKED(IDC_DEGREE_DOWN2, &CRightView::OnBnClickedDegreeDown2)
	ON_BN_CLICKED(IDC_BTN_SWITCH, &CRightView::OnBnClickedBtnSwitch)
	ON_BN_CLICKED(IDC_BTN_GROUND, &CRightView::OnBiaodingGround)
	ON_BN_CLICKED(IDC_BUTTON3, &CRightView::OnBnClickedSaveByTimes)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CRightView 诊断

#ifdef _DEBUG
void CRightView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CRightView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

// CRightView 消息处理程序
HBRUSH CRightView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	//在这加一条是否为对话框的判断语句  
	if(nCtlColor==CTLCOLOR_DLG)          //更改按钮颜色
	{
		//pDC->SetBkMode(TRANSPARENT);
		//pDC->SetBkColor(RGB(121,121,255));   
		HBRUSH b=CreateSolidBrush(RGB(121,121,255));
		return b;
	}
	else if(nCtlColor==CTLCOLOR_STATIC)  //更改静态文本
	{

		CFont font;     // 字体对象  
		COLORREF color; // 字体颜色
		font.CreatePointFont(400, _T("华文彩云"));  
		color = RGB(255, 0, 0); 

		pDC->SelectObject(&font);    // 设置字体  
		pDC->SetTextColor(color);    // 设置颜色  
		//pDC->SetBkColor(RGB(121,121,255));  // 设置字体背景颜色
		HBRUSH b=CreateSolidBrush(RGB(121,121,255));
		return b;

	}
	return hbr;
}

void CRightView::Init(CRect rect)
{
	m_pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	m_pLeftView = (CLeftView *) m_pMainFrame->m_sMyPlitterWnd.GetPane(0,0);
	m_pLeftView2 = (CLeftView2 *) m_pMainFrame->m_sMyPlitterWnd.GetPane(0,3);
	ReadSysInfo();
	if (!AfxSocketInit())
	{
		MessageBox(_T("通信初始化失败！"));
	}
	m_nPicW=300;
	m_nPicH=480;
	int texth=200;
	CRect rect1;
	GetClientRect(&rect1);
	int left1=(rect.Width()-m_nPicW-100-640)/2+m_nPicW;
	int up=(rect.Height()-texth-480)/2;
	int	left2=rect.Width()-100;

	int	left3=(rect.Width()-800)/2;
	int up3=rect.Height()-175;

	GetDlgItem(IDC_IMAGE)->MoveWindow(0,(rect.Height()-texth-m_nPicH)/2,m_nPicW,m_nPicH);
	GetDlgItem(IDC_IMAGE_COLOR)->MoveWindow(left1,up,640,480);

	GetDlgItem(IDC_BTN_SAVE)->MoveWindow(left2,up,80,25);
	GetDlgItem(IDC_BTN_SAVEONE)->MoveWindow(left2,up+40,80,25);
	GetDlgItem(IDC_BTN_GROUND)->MoveWindow(left2,up+80,80,25);
	GetDlgItem(IDC_BTN_SWITCH)->MoveWindow(left2,up+120,80,25);
	GetDlgItem(IDCANCEL)->MoveWindow(left2,up+160,80,25);
	GetDlgItem(IDC_BUTTON3)->MoveWindow(left2-100,up+40,80,25);
	GetDlgItem(IDC_BUTTON4)->MoveWindow(left2-100,up+80,80,25);

	GetDlgItem(IDC_BUTTON)->MoveWindow(left2,up+160,80,25);
	GetDlgItem(IDC_DEGREE1)->MoveWindow(left2,up+200,80,25);
	GetDlgItem(IDC_DEGREE_UP1)->MoveWindow(left2,up+240,80,25);
	GetDlgItem(IDC_DEGREE_DOWN1)->MoveWindow(left2,up+280,80,25);
	GetDlgItem(IDC_DEGREE2)->MoveWindow(left2,up+320,80,25);
	GetDlgItem(IDC_DEGREE_UP2)->MoveWindow(left2,up+360,80,25);
	GetDlgItem(IDC_DEGREE_DOWN2)->MoveWindow(left2,up+400,80,25);


	GetDlgItem(IDC_NOTETEXT)->MoveWindow(left3,up3,800,150);

	CString fname;
	CStatic *pWnd=(CStatic*)GetDlgItem(IDC_IMAGE);
	fname.Format(_T("提示%d.bmp"),1);

	ShowPic(pWnd,fname,rect.left,rect.top);

	for (int i=0;i<m_nPCNum;i++)
	{
		m_pClientSocket[i] = new CClientSocket();
		m_pClientSocket[i]->SetLink(this);
	}

	m_pKinect[0]=(CKinect*) new CKinect(this);
	m_pKinect[1]=(CKinect*) new CKinect(this);

	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
	m_pDrawColor = new ImageRenderer();
	m_pDrawColor->Initialize(GetDlgItem(IDC_IMAGE_COLOR)->GetSafeHwnd(), m_pD2DFactory, 640, 480, 640 * sizeof(long));

	//暂时将MySend中的Socket连接放到这里处理
	for (int i=0;i<m_nPCNum;i++)
	{
		//m_pClientSocket[i]->Close();
		m_pClientSocket[i]->Create();
		m_pClientSocket[i]->Connect(m_sIP[i],nPort);
		//m_pClientSocket[i]->SetLink(this);
	}
	//暂时将摄像头的初始化连接放到这里处理
	HRESULT hr;
	hr = NuiGetSensorCount(&m_nSensorCount);
	if (m_nSensorCount<1)
		return; 

	for (int i=0;i<m_nSensorCount;i++)
	{
		if(!m_pKinect[i]->CreateFirstConnected(i) )
		{
			//MessageBox(_T("Kinect初始化失败"));
			return;
		}
		m_pKinect[i]->m_nDeviceNum=i;
	}
	if (m_nSensorCount>1)
	{
		CString SId=m_pKinect[0]->m_sDeviceId; 
		int pos=SId.ReverseFind('&');
		SId=SId.Right(SId.GetLength()-pos-1);
		int nid=_ttoi(SId);
		if (nid > 3)
		{
			CKinect *pkinect=m_pKinect[0];
			m_pKinect[0]=m_pKinect[1];
			m_pKinect[1]=pkinect;

			m_pKinect[0]->m_nDeviceNum=0;
			m_pKinect[1]->m_nDeviceNum=1;

		}
		int oldid=m_ShowID>0?0:1;
		m_pKinect[oldid]->Shutdown();
	}
}

void CRightView::ReadSysInfo()
{
	// system: 在此添加命令处理程序代码
	GetModuleFileName(NULL,m_sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	m_sPath.ReleaseBuffer();
	int pos = m_sPath.ReverseFind('\\');
	m_sPath = m_sPath.Left(pos);

	CString sPath,str,ss;
	sPath=m_sPath+_T("\\初始文件\\info.ini");
	//m_nPCNum = GetPrivateProfileInt(_T("sys"),_T("PCNUM"),1,sPath);
	
	CString strTemp;
	GetPrivateProfileString(_T("sys"),_T("Z_a"),_T("0.0"),strTemp.GetBuffer(10),10,sPath);
	str.ReleaseBuffer();
	m_dZ_a = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"),_T("Z_b"),_T("0.0"),strTemp.GetBuffer(10),10,sPath);
	str.ReleaseBuffer();
	m_dZ_b = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"),_T("Z_d"),_T("0.0"),strTemp.GetBuffer(10),10,sPath);
	str.ReleaseBuffer();
	m_dZ_d = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"),_T("Z_error"),_T("0.0"),strTemp.GetBuffer(10),10,sPath);
	str.ReleaseBuffer();
	m_dZ_error = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"),_T("Z_up"),_T("0.0"),strTemp.GetBuffer(10),10,sPath);
	str.ReleaseBuffer();
	m_bZ_up = _wtoi(strTemp);

	GetPrivateProfileString(_T("sys"),_T("A_a"),_T("0.0"),strTemp.GetBuffer(10),10,sPath);
	str.ReleaseBuffer();
	m_dA_a = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"),_T("A_b"),_T("0.0"),strTemp.GetBuffer(10),10,sPath);
	str.ReleaseBuffer();
	m_dA_b = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"),_T("A_d"),_T("0.0"),strTemp.GetBuffer(10),10,sPath);
	str.ReleaseBuffer();
	m_dA_d = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"),_T("A_error"),_T("0.0"),strTemp.GetBuffer(10),10,sPath);
	str.ReleaseBuffer();
	m_dA_error = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"),_T("A_up"),_T("0.0"),strTemp.GetBuffer(10),10,sPath);
	str.ReleaseBuffer();
	m_bA_up = _wtoi(strTemp);

	GetPrivateProfileString(_T("sys"),_T("B_a"),_T("0.0"),strTemp.GetBuffer(10),10,sPath);
	str.ReleaseBuffer();
	m_dB_a = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"),_T("B_b"),_T("0.0"),strTemp.GetBuffer(10),10,sPath);
	str.ReleaseBuffer();
	m_dB_b = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"),_T("B_d"),_T("0.0"),strTemp.GetBuffer(10),10,sPath);
	str.ReleaseBuffer();
	m_dB_d = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"),_T("B_error"),_T("0.0"),strTemp.GetBuffer(10),10,sPath);
	str.ReleaseBuffer();
	m_dB_error = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"),_T("B_up"),_T("0.0"),strTemp.GetBuffer(10),10,sPath);
	str.ReleaseBuffer();
	m_bB_up = _wtoi(strTemp);

	m_nPCNum = m_pMainFrame->m_nKinectNum - 1;
	for (int i=0;i<m_nPCNum;i++)
	{
		ss.Format(_T("IP%d"),i+1);
		GetPrivateProfileString(_T("sys"),ss,_T(""),str.GetBuffer(200),200,sPath);
		str.ReleaseBuffer();
		str.Trim();
		m_sIP[i]=str;
	}

	memset(m_Ra0,0,sizeof(float)*9);
	memset(m_Ta,0,sizeof(float)*3);
	memset(m_Rb0,0,sizeof(float)*9);
	memset(m_Tb,0,sizeof(float)*3);
	memset(m_Rz0,0,sizeof(float)*9);
	memset(m_Tz0,0,sizeof(float)*3);

	memset(m_Ra1,0,sizeof(float)*9);
	memset(m_Ta1,0,sizeof(float)*3);
	memset(m_Rb1,0,sizeof(float)*9);
	memset(m_Tb1,0,sizeof(float)*3);
	memset(m_Rz1,0,sizeof(float)*9);
	memset(m_Tz1,0,sizeof(float)*3);
	FILE *fp;
	CString fname=m_sPath+_T("\\初始文件\\sys.txt");
	USES_CONVERSION;
	fp=fopen(W2A(fname),"r");
	char ch=fgetc(fp);
	if(ch==EOF)
		MessageBox(_T("系统参数错误"));
	else
	{
		fseek(fp,0,SEEK_SET);

		fscanf(fp,"%f%f%f",&m_Rz0[0][0],&m_Rz0[0][1],&m_Rz0[0][2]);
		fscanf(fp,"%f%f%f",&m_Rz0[1][0],&m_Rz0[1][1],&m_Rz0[1][2]);
		fscanf(fp,"%f%f%f",&m_Rz0[2][0],&m_Rz0[2][1],&m_Rz0[2][2]);
		fscanf(fp,"%f%f%f",&m_Tz0[0][0],&m_Tz0[0][1],&m_Tz0[0][2]);
		fscanf(fp,"%f%f%f",&m_Ra0[0][0],&m_Ra0[0][1],&m_Ra0[0][2]);  //跳过无用行

		fscanf(fp,"%f%f%f",&m_Ra0[0][0],&m_Ra0[0][1],&m_Ra0[0][2]);
		fscanf(fp,"%f%f%f",&m_Ra0[1][0],&m_Ra0[1][1],&m_Ra0[1][2]);
		fscanf(fp,"%f%f%f",&m_Ra0[2][0],&m_Ra0[2][1],&m_Ra0[2][2]);
		fscanf(fp,"%f%f%f",&m_Ta[0][0],&m_Ta[0][1],&m_Ta[0][2]);
		fscanf(fp,"%f%f%f",&m_Rb0[0][0],&m_Rb0[0][1],&m_Rb0[0][2]);  //跳过无用行

		fscanf(fp,"%f%f%f",&m_Rb0[0][0],&m_Rb0[0][1],&m_Rb0[0][2]);
		fscanf(fp,"%f%f%f",&m_Rb0[1][0],&m_Rb0[1][1],&m_Rb0[1][2]);
		fscanf(fp,"%f%f%f",&m_Rb0[2][0],&m_Rb0[2][1],&m_Rb0[2][2]);
		fscanf(fp,"%f%f%f",&m_Tb[0][0],&m_Tb[0][1],&m_Tb[0][2]);
		fscanf(fp,"%f%f%f",&m_Rz1[0][0],&m_Rz1[0][1],&m_Rz1[0][2]);  //跳过无用行

		fscanf(fp,"%f%f%f",&m_Rz1[0][0],&m_Rz1[0][1],&m_Rz1[0][2]);
		fscanf(fp,"%f%f%f",&m_Rz1[1][0],&m_Rz1[1][1],&m_Rz1[1][2]);
		fscanf(fp,"%f%f%f",&m_Rz1[2][0],&m_Rz1[2][1],&m_Rz1[2][2]);
		fscanf(fp,"%f%f%f",&m_Tz1[0][0],&m_Tz1[0][1],&m_Tz1[0][2]);
		fscanf(fp,"%f%f%f",&m_Rb1[0][0],&m_Rb1[0][1],&m_Rb1[0][2]);  //跳过无用行

		fscanf(fp,"%f%f%f",&m_Ra1[0][0],&m_Ra1[0][1],&m_Ra1[0][2]);
		fscanf(fp,"%f%f%f",&m_Ra1[1][0],&m_Ra1[1][1],&m_Ra1[1][2]);
		fscanf(fp,"%f%f%f",&m_Ra1[2][0],&m_Ra1[2][1],&m_Ra1[2][2]);
		fscanf(fp,"%f%f%f",&m_Ta1[0][0],&m_Ta1[0][1],&m_Ta1[0][2]);
		fscanf(fp,"%f%f%f",&m_Rb1[0][0],&m_Rb1[0][1],&m_Rb1[0][2]);  //跳过无用行

		fscanf(fp,"%f%f%f",&m_Rb1[0][0],&m_Rb1[0][1],&m_Rb1[0][2]);
		fscanf(fp,"%f%f%f",&m_Rb1[1][0],&m_Rb1[1][1],&m_Rb1[1][2]);
		fscanf(fp,"%f%f%f",&m_Rb1[2][0],&m_Rb1[2][1],&m_Rb1[2][2]);
		fscanf(fp,"%f%f%f",&m_Tb1[0][0],&m_Tb1[0][1],&m_Tb1[0][2]);
	}
	fclose(fp);
	fp=NULL;
}

void CRightView::MySendCmd(int Cmd)
{

	for (int i=0;i<m_nPCNum;i++)
	{
		FARDATA fardata;
		fardata.cmd=Cmd;
		fardata.length=0;
		memset(fardata.sName,0,sizeof(fardata.sName));
		m_pClientSocket[i]->SendCmd(fardata);
	}
}

void CRightView::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(0);
	CString str;
	int second=200;//初始时设定为0.2s取一次状态
	if (m_pMainFrame->m_bByMan!=1)
	{
		if (m_nNoteTime>=0)
		{
			second=1000;
			str.Format(_T("请保持姿势，%d S后开始拍照！"),m_nNoteTime);
			m_sNoteText.SetWindowText(str);
			if (m_nNoteTime>0)
			{
				int i=6-m_nNoteTime;
				CStatic *pWnd=(CStatic*)GetDlgItem(IDC_IMAGE);
				CRect rect;
				pWnd->GetWindowRect(rect);
				str.Format(_T("提示%d.bmp"),i);
				ShowPic(pWnd,str,rect.left,rect.top);
			}
			m_nNoteTime--;
		}
		else if (m_pMainFrame->m_nGetNum==m_pMainFrame->m_nKinectNum)
		{
			//m_pMainFrame->m_nGetNum = 0;
			CStatic *pWnd=(CStatic*)GetDlgItem(IDC_IMAGE);
			CRect rect;
			pWnd->GetWindowRect(rect);
			str=_T("结束.bmp");
			ShowPic(pWnd,str,rect.left,rect.top);
			str.Format(_T("               完成！"));
			m_sNoteText.SetWindowText(str);
			m_bSave=0;
			return;
		}
		else if (m_bHasPeople==1 && m_bFinish!=1)//这里出现了问题
		{
			str=_T("        请保持姿势,拍照中！");
			m_sNoteText.SetWindowText(str);
			str=m_sPath+_T("\\初始文件\\扫描中.mp3");
			sndPlaySound(str,SND_ASYNC);
			m_bSave=1;                          //保存照片
			m_pMainFrame->m_nGetNum=0;
			if (m_pMainFrame->m_bSaveFarData)//让远程保存备份数据
				MySendCmd(CMD_SAVE_FAR);            //发送命令
			else
				MySendCmd(CMD_SAVE);            //发送命令
		}
	}

	BeginGrab();
	SetTimer(0,second,NULL);
}

void CRightView::OpenKinect()
{
	m_sNoteText.SetWindowText(_T(""));
	//MySendCmd(CMD_OPENKINECT);
	SetTimer(0,200,NULL);
}

void CRightView::BeginGrab()
{
	if (m_bSave>0)
	{
		for (int i=0;i<m_nSensorCount;i++)
		{

			m_ShowID=i;
			//m_pKinect[i]->Init();
			m_pKinect[i]->GrabImage(m_bSave);
			m_pDrawColor->Draw(ColorByte,ColorSize);
			//CString str;
			//str=SetFilePath(m_bSave);
			/*SaveBitmapToFile(ColorByte, 640, 480, 32, str + _T("Z0.bmp"));*/
			SaveDepthData(i);//i=0
			//m_pKinect[i]->Shutdown();
		}
		m_bSave=0;
		m_bFinish=1;
	}
	else
	{
		m_pKinect[m_ShowID]->GrabImage(m_bSave);
		m_pDrawColor->Draw(ColorByte,ColorSize);
	}
}

void CRightView::DoCmdPro(UINT cmd,CString fname,UINT UsePointNum,char *FileData)
{
	float * PointData=(float *)FileData;
	CString sGetName,path,sday,stime,ss,sName;
	if (fname.Find(_T("Z1"))!=-1)
	{
		/*memcpy(R,m_Rz0,sizeof(m_Rz0));
		memcpy(T,m_Tz,sizeof(m_Tz));*/
		sGetName=_T("Z1");
	}
	else if (fname.Find(_T("A0"))!=-1)
	{
		memcpy(R,m_Ra0,sizeof(m_Ra0));
		memcpy(T,m_Ta,sizeof(m_Ta));
		sGetName=_T("A0");
	}
	else if (fname.Find(_T("A1"))!=-1)
	{
		memcpy(R,m_Ra1,sizeof(m_Ra1));
		memcpy(T,m_Ta1,sizeof(m_Ta1));
		sGetName=_T("A1");
	}
	else if (fname.Find(_T("B0"))!=-1)
	{
		memcpy(R,m_Rb0,sizeof(m_Rb0));
		memcpy(T,m_Tb,sizeof(m_Tb));
		sGetName=_T("B0");
	}
	else if (fname.Find(_T("B1"))!=-1)
	{
		memcpy(R,m_Rb1,sizeof(m_Rb1));
		memcpy(T,m_Tb1,sizeof(m_Tb1));
		sGetName=_T("B1");
	}
	else
	{
		return;
	}

	if (m_pMainFrame->m_nGetNum==0)
	{
		sName=SetFileTimePath(m_bSave);
		m_pMainFrame->m_sTargetPath=sName;
	}
	else
	{
		sName=m_pMainFrame->m_sTargetPath;
	}
	sName=sName+sGetName;
	switch (cmd)
	{
	case CMD_DATA:
		{	
			SaveDepthDataAll(sName,PointData);
			break;
		}
	case CMD_BIAODING: 
		{
			SaveDepthDataOne(sName,PointData);
			break;
		}
	default:
		break;
	}
	return;
}

//仅保存本地相机的数据
void CRightView::SaveDepthData(int index)      //z0,z1  命名
{
	CString sName;
	if (m_pMainFrame->m_nGetNum==0)
	{
		//单相机必然进入这里
		memset(m_pLeftView->m_btRGB_Z0,0,640*480*3);
		memset(m_pLeftView->m_btRGB_Z1,0,640*480*3);
		memset(m_pLeftView->m_btRGB_A0,0,640*480*3);
		memset(m_pLeftView->m_btRGB_A1,0,640*480*3);
		memset(m_pLeftView->m_btRGB_B0,0,640*480*3);
		memset(m_pLeftView->m_btRGB_B1,0,640*480*3);
		m_pLeftView2->m_pointsZ0_new.clear();
		m_pLeftView2->m_pointsZ1_new.clear();
		m_pLeftView2->m_pointsA0_new.clear();
		m_pLeftView2->m_pointsA1_new.clear();
		m_pLeftView2->m_pointsB0_new.clear();
		m_pLeftView2->m_pointsB1_new.clear();
		//m_pLeftView2->m_pPointsList.clear();
		sName=SetFileTimePath(m_bSave);
		m_pMainFrame->m_sTargetPath=sName;

		CString str = _T("Z0");
		//str.Format(_T("Z%d"),index);
		sName=sName+str;
		//SaveBitmapToFile(640, 480, 24, sName + _T(".bmp"));//第三个参数一定要是8~24之间的，否则无法作为纹理图案来处理
		//GetFaceKeyPoints(sName + _T(".bmp"));
		//m_pLeftView->m_sBmpPath = sName;
	}
	else
	{
		sName=m_pMainFrame->m_sTargetPath;
		CString str = _T("Z1");
		//str.Format(_T("Z%d"),index);
		sName=sName+str;
	}
	if (m_bSave>1)                        //每个相机存各自的个txt,用于前期的标定
	{
		SaveDepthDataOne(sName,m_pKinect[index]->m_PointsBuffer);
	}												
	else								//实际拍照,存一起
	{
		if (index==1)
		{
			memcpy(R,m_Rz1,sizeof(m_Rz1));
			memcpy(T,m_Tz1,sizeof(m_Tz1));
		}
		else if (index==0)
		{
			memcpy(R,m_Rz0,sizeof(m_Rz0));
			memcpy(T,m_Tz0,sizeof(m_Tz0));
		}
		SaveDepthDataAll(sName,m_pKinect[index]->m_PointsBuffer);
	}
}

//分别保存单个txt文件，用于前期标定
void CRightView::SaveDepthDataOne(CString fname,float* PointsBuffer)
{
	//所有主机得到的数据都会经过这个函数,所以在这里对地面进行过滤时最合适的
	USES_CONVERSION;
	m_pMainFrame->m_nGetNum++;
	CString sName=fname+_T(".txt");
	FILE *fp_txt=NULL;
	fp_txt=fopen(W2A(sName),"w+");
	bool bInto = false;
	for(int i=0;i<480;i++)
	{
		for(int j=0;j<640;j++)
		{
			float realDepth=PointsBuffer[4*(i*640+j)];
			if ( realDepth>Mindepth&&realDepth<Maxdepth )
			{
				bInto = true;
				float yy =(float) -(i - 240.0) * fy * realDepth;
				float xx = (float)(j- 320.0) * fx * realDepth;
				//if (fname.Find(_T("Z1"))!=-1 || fname.Find(_T("A1"))!=-1 || fname.Find(_T("B1"))!=-1)
				//{
				//	xx *= 0.95;//暂时测试用
				//}
				if(m_bFilterGround)
				{
					//如果过滤地面
					if(!IfAtGround(fname,i,j,xx,yy,realDepth))
					{
						int red, green, blue;
						blue  =(int)PointsBuffer[4*(i*640+j)+1];
						green =(int)PointsBuffer[4*(i*640+j)+2];
						red   =(int)PointsBuffer[4*(i*640+j)+3];
						fprintf(fp_txt, "%f %f %f %d %d %d\r\n", xx, yy, realDepth, red, green, blue);
					}
				}
				else
				{
					//如果保留地面，则需要删去上侧的数据，200待调整
					if (yy<-200)
					{
						int red, green, blue;
						blue  =(int)PointsBuffer[4*(i*640+j)+1];
						green =(int)PointsBuffer[4*(i*640+j)+2];
						red   =(int)PointsBuffer[4*(i*640+j)+3];
						fprintf(fp_txt, "%f %f %f %d %d %d\r\n", xx, yy, realDepth, red, green, blue);
					}
				}

			}
		}
	}
	if(!bInto)
	{
		//m_sNoteText.SetWindowText(_T("出现了空文件！"));
	}
	fclose(fp_txt);
	fp_txt=NULL;
	//多次循环拍摄时进行的判断
	if (m_bSaveByTimes==true)
	{
		m_nSaveTimes = 30;
		if (m_pMainFrame->m_nGetNum==m_pMainFrame->m_nKinectNum)
		{
			if(m_nSaveCurrentTime<m_nSaveTimes-1)//尚未保存完要求的次数
			{
				Sleep(1000);
				CString str;
				str.Format(L"正在拍摄第%d张，总计%d张",m_nSaveCurrentTime+1,m_nSaveTimes);
				m_sNoteText.SetWindowText(str);
				OnBnClickedSaveOne();
				m_nSaveCurrentTime++;
			}
			else
			{
				m_bSaveByTimes = false;
				m_sNoteText.SetWindowText(_T("循环拍摄完成！"));
			}
		}
	}
	else
	{
		m_sNoteText.SetWindowText(_T("单份保存完成！"));
		m_btnSaveOne.EnableWindow(TRUE);
	}
}

//保存所有pcd和dxf文件，用于实际工作
void CRightView::SaveDepthDataAll(CString fname,float* PointsBuffer)
{
	POINT6D f_xyzrgb;
	MY_POINT3D f_xyz;
	CString sName;
	int pointnum=0;
	
	USES_CONVERSION;
	FILE *fp_txt=NULL;
	FILE *fp_pcd=NULL;
	
	sName=fname+_T(".pcd");
	fp_pcd=fopen(W2A(sName),"a+");
	pointnum=0;
	//第一次循环，计算出有多少个点
	for(int i=0;i<480;i++)//i为480行，一行640列
	{
		for(int j=0;j<640;j++)//j为640列
		{
			//所有点都保存到LeftView中去
			//TODO
			float realDepth=PointsBuffer[4*(i*640+j)];
			if (realDepth>Mindepth&&realDepth<Maxdepth)//点距离在要求的范围内(测试时保证所有的点都在这个区域中)
			{
				float yy = -(i - 240) * fy * realDepth;	
				float xx = (j- 320) * fx * realDepth;
// 				float yy = -(i - 240) * fy * 1000;	
// 				float xx = (j- 320) * fx * 1000;
				//if (fname.Find(_T("Z1"))!=-1 || fname.Find(_T("A1"))!=-1 || fname.Find(_T("B1"))!=-1)
				//{
				//	xx *= 0.95;//暂时测试用
				//}
				if(!IfAtGround(fname,i,j,xx,yy,realDepth)/*&&!IfFilterFace(fname,i,j)*/)
				{
					pointnum++;
				}
				else
				{
					PointsBuffer[4*(i*640+j)] = 0;
				}
			}
			else
			{
				PointsBuffer[4*(i*640+j)] = 0;
			}
		}	
	}
	//这里要改
	//fprintf(fp_pcd,"%d",pointnum);
	//fprintf(fp_pcd,"# .PCD v0.7 - Point Cloud Data file format\r\nVERSION 0.7\r\nFIELDS x y z rgb\r\nSIZE 4 4 4 4\r\nTYPE F F F F\r\nCOUNT 1 1 1 1\r\nWIDTH %d\r\nHEIGHT 1\r\nVIEWPOINT 0 0 0 1 0 0 0\r\nPOINTS %d\r\nDATA ascii\r\n",pointnum,pointnum);
	fprintf(fp_pcd,"# .PCD v0.7 - Point Cloud Data file format\r\nVERSION 0.7\r\nFIELDS x y z\r\nSIZE 4 4 4\r\nTYPE F F F\r\nCOUNT 1 1 1\r\nWIDTH %d\r\nHEIGHT 1\r\nVIEWPOINT 0 0 0 1 0 0 0\r\nPOINTS %d\r\nDATA ascii\r\n",pointnum,pointnum);
	for(int i=0;i<480;i++)
	{
		for(int j=0;j<640;j++)
		{
			int b=PointsBuffer[4*(i*640+j)+1];
			int g=PointsBuffer[4*(i*640+j)+2];
			int r =PointsBuffer[4*(i*640+j)+3];
			float realDepth=PointsBuffer[4*(i*640+j)];
			//先将RGB流写入LeftView中,注意这里的rgb的值是反的
			if(fname.Find(_T("Z0"))!=-1)
			{
// 				if (realDepth == 0) {
// 					m_pLeftView->m_btRGB_Z0[(640*i+j)*3+0] = 255;
// 					m_pLeftView->m_btRGB_Z0[(640*i+j)*3+1] = 255;
// 					m_pLeftView->m_btRGB_Z0[(640*i+j)*3+2] = 255;
// 				}else {
					m_pLeftView->m_btRGB_Z0[(640*i+j)*3+0] =b;
					m_pLeftView->m_btRGB_Z0[(640*i+j)*3+1] = g;
					m_pLeftView->m_btRGB_Z0[(640*i+j)*3+2] = r;
//				}
			}
			if(fname.Find(_T("Z1"))!=-1)
			{
// 				if (realDepth == 0) {
// 					m_pLeftView->m_btRGB_Z1[(640*i+j)*3+0] = 255;
// 					m_pLeftView->m_btRGB_Z1[(640*i+j)*3+1] = 255;
// 					m_pLeftView->m_btRGB_Z1[(640*i+j)*3+2] = 255;
// 				}else {
					m_pLeftView->m_btRGB_Z1[(640*i+j)*3+0] =b;
					m_pLeftView->m_btRGB_Z1[(640*i+j)*3+1] = g;
					m_pLeftView->m_btRGB_Z1[(640*i+j)*3+2] = r;
//				}
			}
			if(fname.Find(_T("A0"))!=-1)
			{
// 				if (realDepth == 0) {
// 					m_pLeftView->m_btRGB_A0[(640*i+j)*3+0] = 255;
// 					m_pLeftView->m_btRGB_A0[(640*i+j)*3+1] = 255;
// 					m_pLeftView->m_btRGB_A0[(640*i+j)*3+2] = 255;
// 				}else {
					m_pLeftView->m_btRGB_A0[(640*i+j)*3+0] =b;
					m_pLeftView->m_btRGB_A0[(640*i+j)*3+1] = g;
					m_pLeftView->m_btRGB_A0[(640*i+j)*3+2] = r;
//				}
			}
			if(fname.Find(_T("A1"))!=-1)
			{
// 				if (realDepth == 0) {
// 					m_pLeftView->m_btRGB_A1[(640*i+j)*3+0] = 255;
// 					m_pLeftView->m_btRGB_A1[(640*i+j)*3+1] = 255;
// 					m_pLeftView->m_btRGB_A1[(640*i+j)*3+2] = 255;
// 				}else {
					m_pLeftView->m_btRGB_A1[(640*i+j)*3+0] =b;
					m_pLeftView->m_btRGB_A1[(640*i+j)*3+1] = g;
					m_pLeftView->m_btRGB_A1[(640*i+j)*3+2] = r;
//				}
			}
			if(fname.Find(_T("B0"))!=-1)
			{
// 				if (realDepth == 0) {
// 					m_pLeftView->m_btRGB_B0[(640*i+j)*3+0] = 255;
// 					m_pLeftView->m_btRGB_B0[(640*i+j)*3+1] = 255;
// 					m_pLeftView->m_btRGB_B0[(640*i+j)*3+2] = 255;
// 				}else {
					m_pLeftView->m_btRGB_B0[(640*i+j)*3+0] =b;
					m_pLeftView->m_btRGB_B0[(640*i+j)*3+1] = g;
					m_pLeftView->m_btRGB_B0[(640*i+j)*3+2] = r;
//				}
			}
			if(fname.Find(_T("B1"))!=-1)
			{
// 				if (realDepth == 0) {
// 					m_pLeftView->m_btRGB_B1[(640*i+j)*3+0] = 255;
// 					m_pLeftView->m_btRGB_B1[(640*i+j)*3+1] = 255;
// 					m_pLeftView->m_btRGB_B1[(640*i+j)*3+2] = 255;
// 				}else {
					m_pLeftView->m_btRGB_B1[(640*i+j)*3+0] =b;
					m_pLeftView->m_btRGB_B1[(640*i+j)*3+1] = g;
					m_pLeftView->m_btRGB_B1[(640*i+j)*3+2] = r;
//				}
			}
			//再将点云流写入LeftView2中
			//float realDepth=PointsBuffer[4*(i*640+j)];
			if ( realDepth>Mindepth && realDepth<Maxdepth)
			{
				//TODO
 				float y = -(i - 240) * fy * realDepth;	
 				float x = (j- 320) * fx * realDepth;
// 				float y = -(i - 240) * fy * 1000;	
// 				float x = (j- 320) * fx * 1000;
				float xx,yy,zz;
				if(fname.Find(_T("Z1"))==-1)
				{
					xx=R[0][0]*x+R[0][1]*y+R[0][2]*realDepth+T[0][0];
					yy=R[1][0]*x+R[1][1]*y+R[1][2]*realDepth+T[0][1];
					zz=R[2][0]*x+R[2][1]*y+R[2][2]*realDepth+T[0][2];
				}
				else//若为Z1,不需要旋转
				{
					xx = x; yy = y; zz = realDepth;
				}
				f_xyz.x=xx;
				f_xyz.y=yy;
				f_xyz.z=zz;

				prMax.x=max(prMax.x,f_xyz.x);
				prMax.y=max(prMax.y,f_xyz.y);
				prMax.z=max(prMax.z,f_xyz.z);
				prMin.x=min(prMin.x,f_xyz.x);
				prMin.y=min(prMin.y,f_xyz.y);
				prMin.z=min(prMin.z,f_xyz.z);
				m_pLeftView2->m_pPointsList.push_back(f_xyz);
				//int rgb;
				//rgb = (r<<16|g<<8|b);
				//fprintf(fp_pcd,"%f %f %f %d\r\n",xx,yy,zz,rgb);
				fprintf(fp_pcd,"%f %f %f\r\n",xx,yy,zz);
			}
		}
	}
	fclose(fp_pcd);
	fp_pcd=NULL;
	m_pMainFrame->m_nGetNum++;
	if (m_pMainFrame->m_nGetNum==m_pMainFrame->m_nKinectNum)
	{
		m_pLeftView2->prBoxCenter = (prMax+prMin) / 2;
		m_pLeftView2->prBoxSize = (prMax-prMin) / 2;
	}
}

CString CRightView::SetFileTimePath(int index)
{
	CString sday,stime,path,ss,str;
	SYSTEMTIME st;
	GetLocalTime(&st);
	sday.Format(_T("%d_%02d_%02d"),st.wYear,st.wMonth,st.wDay);
	path=m_sPath+_T("\\Image\\")+sday;
	if (!PathIsDirectory(path))
		CreateDirectory(path, NULL );

	if (index==1)
	{
		stime.Format(_T("\\%02d_%02d_%02d_pcd"),st.wHour,st.wMinute,st.wSecond);
	}
	else
	{
		stime.Format(_T("\\%02d_%02d_%02d_txt"),st.wHour,st.wMinute,st.wSecond);
	}
	path=path+stime;
	if (!PathIsDirectory(path))
		CreateDirectory(path, NULL );

	//ss.Format(_T("%d%02d%02d_%02d%02d%02d"),st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	/*ss = _T("1");
	path=path+_T("\\")+ss;*/
	path=path+_T("\\");

	return path;
}
void CRightView::OnBnClickedBtnSwitch()
{
	// system: 在此添加控件通知处理程序代码
	if (m_nSensorCount==2)
	{
		m_ShowID=m_ShowID>0?0:1;
		int OldID=m_ShowID>0?0:1;
		m_pKinect[m_ShowID]->Init();
	}
	else
	{
		m_ShowID=0; 
		MessageBox(_T("只有一台Kinect!"));
	}
}
void CRightView::OnBnClickedSave()
{
	// system: 在此添加控件通知处理程序代码
	if (m_pMainFrame->m_bSaveFarData)//让远程保存备份数据
		MySendCmd(CMD_SAVE_FAR);            //发送命令
	else
		MySendCmd(CMD_SAVE);            //发送命令
	m_pMainFrame->m_nGetNum=0;
	m_bSave = 1;
}
void CRightView::OnBnClickedSaveOne()
{
	// system: 在此添加控件通知处理程序代码
	Sleep(10000);
	m_btnSaveOne.EnableWindow(FALSE);
	m_pMainFrame->m_nGetNum=0;
	MySendCmd(CMD_BIAODING);
	m_bSave = 2;
	m_bFilterGround = true;
}
void CRightView::OnBnClickedSaveByTimes()
{
	m_sNoteText.SetWindowText(_T("循环拍摄中，请勿进行其他操作！"));
	m_bSaveByTimes = true;

	m_nSaveCurrentTime = 0;
	OnBnClickedSaveOne();
}
void CRightView::OnBnClickedSaveLots()
{

}
void CRightView::OnBnClickedDegree1()
{
	// system: 在此添加控件通知处理程序代码
	m_pKinect[0]->Degree0();
}
void CRightView::OnBnClickedDegreeUp1()
{
	// system: 在此添加控件通知处理程序代码
	m_pKinect[0]->Up();
}
void CRightView::OnBnClickedDegreeDown1()
{
	// system: 在此添加控件通知处理程序代码
	m_pKinect[0]->Down();
}
void CRightView::OnBnClickedDegree2()
{
	// system: 在此添加控件通知处理程序代码
	m_pKinect[1]->Degree0();
}
void CRightView::OnBnClickedDegreeUp2()
{
	// system: 在此添加控件通知处理程序代码
	m_pKinect[1]->Up();
}
void CRightView::OnBnClickedDegreeDown2()
{
	// system: 在此添加控件通知处理程序代码
	m_pKinect[1]->Down();
}
void CRightView::ShowPic(CStatic* pWnd,CString fname ,int x,int y) 
{

	CString BmpName=m_sPath+_T("\\初始文件\\")+fname;
	HBITMAP  hbitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),BmpName,IMAGE_BITMAP,m_nPicW,
		m_nPicH,LR_LOADFROMFILE);   
	pWnd->SetBitmap(hbitmap);    
}
void CRightView::OnBiaodingGround()
{
	m_pMainFrame->m_nGetNum=0;;
	MySendCmd(CMD_BIAODING);
	m_bSave = 2;
	m_bFilterGround = false;
}
void CRightView::rgb2hsv(int r,int g,int b,HSV& hsv)
{
	int max = r>g?(r>b?r:b):(g>b?g:b);
	int min = r<g?(r<b?r:b):(g<b?g:b);
	if(max == min)
		hsv.h = 0;
	else if(max==r&&g>=b)
		hsv.h = 60*(g-b)/(max - min) + 0;
	else if(max==r&&g<b)
		hsv.h = 60*(g-b)/(max - min) + 360;
	else if(max==g)
		hsv.h = 60*(b-r)/(max - min) + 120;
	else if(max==b)
		hsv.h = 60*(r-g)/(max - min) + 240;
	else
		return;
	if(max == 0)
		hsv.s = 0;
	else
		hsv.s = (max - min)/max;
	hsv.v = max;
}
void CRightView::Mat3Trans(float input[][3],float output[][3])
{
	output[0][0]=m_Rz0[0][0]*input[0][0]+m_Rz0[0][1]*input[1][0]+m_Rz0[0][2]*input[2][0];
	output[0][1]=m_Rz0[0][0]*input[0][1]+m_Rz0[0][1]*input[1][1]+m_Rz0[0][2]*input[2][1];
	output[0][2]=m_Rz0[0][0]*input[0][2]+m_Rz0[0][1]*input[1][2]+m_Rz0[0][2]*input[2][2];

	output[1][0]=m_Rz0[1][0]*input[0][0]+m_Rz0[1][1]*input[1][0]+m_Rz0[1][2]*input[2][0];
	output[1][1]=m_Rz0[1][0]*input[0][1]+m_Rz0[1][1]*input[1][1]+m_Rz0[1][2]*input[2][1];
	output[1][2]=m_Rz0[1][0]*input[0][2]+m_Rz0[1][1]*input[1][2]+m_Rz0[1][2]*input[2][2];

	output[2][0]=m_Rz0[2][0]*input[0][0]+m_Rz0[2][1]*input[1][0]+m_Rz0[2][2]*input[2][0];
	output[2][1]=m_Rz0[2][0]*input[0][1]+m_Rz0[2][1]*input[1][1]+m_Rz0[2][2]*input[2][1];
	output[2][2]=m_Rz0[2][0]*input[0][2]+m_Rz0[2][1]*input[1][2]+m_Rz0[2][2]*input[2][2];
}

void CRightView::HideButtons()
{
	GetDlgItem(IDC_BTN_SAVE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_SAVEONE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_GROUND)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_SWITCH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BUTTON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DEGREE1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DEGREE_UP1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DEGREE_DOWN1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DEGREE2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DEGREE_UP2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DEGREE_DOWN2)->ShowWindow(SW_HIDE);
}

bool CRightView::IfAtGround(CString fname, int i, int j, float xx, float yy, float depth)
{
	//根据fname获得该数据来自哪个主机
	int len = fname.GetLength();
	TCHAR cABZ = fname.GetAt(len-2);
	TCHAR c01 = fname.GetAt(len-1);
	double a, b, c, d, error;
	bool bUp;
	if(cABZ == _T('Z'))
	{
		a = m_dZ_a; b = m_dZ_b; c = -1; d = m_dZ_d; error = m_dZ_error;
		bUp = m_bZ_up;
	}else if(cABZ == _T('A'))
	{
		a = m_dA_a; b = m_dA_b; c = -1; d = m_dA_d; error = m_dA_error;
		bUp = m_bA_up;
	}else//if(ch == _T('B'))
	{
		a = m_dB_a; b = m_dB_b; c = -1; d = m_dB_d; error = m_dB_error;
		bUp = m_bB_up;
	}
	//如果需要过滤地面

	if(c01==_T('0'))//上面相机，不需要去除地面
	{
		return false;
	}
	else//下面相机，需要去除地面
	{
		if(i > 300)//只有靠近下面的点才有可能是地面
		{
			if( j>100 && j<540 )//取靠近中间的部分，这里的数值待定
			{
				double dist = (a*xx + b*yy + c*depth + d) / sqrt(a*a + b*b + c*c);
				if(bUp==1)//向上取点
				{
					if (dist > error)
					{
						return false;
					}
					else
						return true;
				}
				else//向下取点
				{
					if (dist < error)
					{
						return false;
					}
					else
						return true;
				}
			}
			else
			{
				return true;
			}
		}
		else
		{
			return false;
		}

	}
}

HRESULT CRightView::SaveBitmapToFile(LONG lWidth, LONG lHeight, WORD wBitsPerPixel, LPCWSTR lpszFilePath)
{
	int nBytesWidth = 640*3;//三个颜色，每个各占用了1个字节00~FF

	HANDLE hMem = GlobalAlloc(GMEM_ZEROINIT,640*480*3);
	BYTE* pImage = (BYTE*)GlobalAlloc(GMEM_ZEROINIT,nBytesWidth*480*3);//这里又乘了一个3是为什么

	for (int i=0;i<480;i++)
	{
		for (int j=0;j<640;j++)
		{
			*(pImage + i*nBytesWidth + j*3 + 0) = (BYTE)(m_pKinect[0]->m_PointsBuffer[3*(i*640+j)+1]);
			*(pImage + i*nBytesWidth + j*3 + 1) = (BYTE)(m_pKinect[0]->m_PointsBuffer[3*(i*640+j)+2]);
			*(pImage + i*nBytesWidth + j*3 + 2) = (BYTE)(m_pKinect[0]->m_PointsBuffer[3*(i*640+j)+3]);
		}
	}

 	DWORD dwByteCount = lWidth * lHeight * (wBitsPerPixel / 8);//这里的除以8又是为了什么

	BITMAPINFOHEADER bmpInfoHeader = {0};

	bmpInfoHeader.biSize        = sizeof(BITMAPINFOHEADER);  // Size of the header
	bmpInfoHeader.biBitCount    = wBitsPerPixel;             // Bit count
	bmpInfoHeader.biCompression = BI_RGB;                    // Standard RGB, no compression
	bmpInfoHeader.biWidth       = lWidth;                    // Width in pixels
	bmpInfoHeader.biHeight      = -lHeight;                  // Height in pixels, negative indicates it's stored right-side-up
	bmpInfoHeader.biPlanes      = 1;                         // Default
	bmpInfoHeader.biSizeImage   = dwByteCount;               // Image size in bytes

	BITMAPFILEHEADER bfh = {0};

	bfh.bfType    = 0x4D42;                                           // 'M''B', indicates bitmap
	bfh.bfOffBits = bmpInfoHeader.biSize + sizeof(BITMAPFILEHEADER);  // Offset to the start of pixel data
	bfh.bfSize    = bfh.bfOffBits + bmpInfoHeader.biSizeImage;        // Size of image + headers
	 
	// Create the file on disk to write to
	HANDLE hFile = CreateFileW(lpszFilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// Return if error opening file
	if (NULL == hFile) 
	{
		return E_ACCESSDENIED;
	}

	DWORD dwBytesWritten = 0;

	// Write the bitmap file header
	if ( !WriteFile(hFile, &bfh, sizeof(bfh), &dwBytesWritten, NULL) )
	{
		CloseHandle(hFile);
		return E_FAIL;
	}

	// Write the bitmap info header
	if ( !WriteFile(hFile, &bmpInfoHeader, sizeof(bmpInfoHeader), &dwBytesWritten, NULL) )
	{
		CloseHandle(hFile);
		return E_FAIL;
	}

	// Write the RGB Data
	if ( !WriteFile(hFile, pImage, bmpInfoHeader.biSizeImage, &dwBytesWritten, NULL) )
	{
		CloseHandle(hFile);
		return E_FAIL;
	}    

	// Close the file
	CloseHandle(hFile);

	GlobalUnlock(hMem);
	GlobalFree(hMem);
	return S_OK;
}


/***********************************************************************************
系数矩阵的限幅处理，防止它溢出，目前这个函数很不完善，并不能很好地解决这个问题
原理：矩阵解行列式，同一行乘以一个系数，行列式的解不变
当然，相对溢出问题，还有一个精度问题，也是同样的思路，现在对于这两块的处理很不完善，有待优化
以行为单位处理
***********************************************************************************/

/***********************************************************************************
打印系数矩阵，只用于调试，不具备运算功能
对于一个N阶拟合，它的系数矩阵大小是（N + 1）行（N + 2）列
double* Para：系数矩阵存储地址
int SizeSrc：系数矩阵大小（SizeSrc）行（SizeSrc + 1）列
***********************************************************************************/
int CRightView::PrintPara(double* Para, int SizeSrc)
{
	//int i, j;
	//for (i = 0; i < SizeSrc; i++)
	//{
	//	for (j = 0; j <= SizeSrc; j++)
	//		/*{
	//		double temp = ParaBuffer(Para, i, j);
	//		}*/
	//		printf("%10.6lf ", ParaBuffer(Para, i, j));
	//	printf("\r\n");
	//}
	//printf("\r\n");
	return 0;
}

int CRightView::ParalimitRow(double* Para, int SizeSrc, int Row)
{
	int i;
	double Max, Min, Temp;
	for (Max = abs(ParaBuffer(Para, Row, 0)), Min = Max, i = SizeSrc; i; i--)
	{
		Temp = abs(ParaBuffer(Para, Row, i));
		if (Max < Temp)
			Max = Temp;
		if (Min > Temp)
			Min = Temp;
	}
	Max = (Max + Min) * 0.000005;
	for (i = SizeSrc; i >= 0; i--)
		ParaBuffer(Para, Row, i) /= Max;
	return 0;
}

/***********************************************************************************
同上，以矩阵为单位处理
***********************************************************************************/
int CRightView::Paralimit(double* Para, int SizeSrc)
{
	int i;
	for (i = 0; i < SizeSrc; i++)
		if (ParalimitRow(Para, SizeSrc, i))
			return -1;
	return 0;
}

/***********************************************************************************
系数矩阵行列式变换
***********************************************************************************/
int CRightView::ParaPreDealA(double* Para, int SizeSrc, int Size)
{
	int i, j;
	for (Size -= 1, i = 0; i < Size; i++)
	{
		for (j = 0; j < Size; j++)
			ParaBuffer(Para, i, j) = ParaBuffer(Para, i, j) * ParaBuffer(Para, Size, Size) - ParaBuffer(Para, Size, j) * ParaBuffer(Para, i, Size);
		ParaBuffer(Para, i, SizeSrc) = ParaBuffer(Para, i, SizeSrc) * ParaBuffer(Para, Size, Size) - ParaBuffer(Para, Size, SizeSrc) * ParaBuffer(Para, i, Size);
		ParaBuffer(Para, i, Size) = 0;
		ParalimitRow(Para, SizeSrc, i);
	}
	return 0;
}

/***********************************************************************************
系数矩阵行列式变换，与ParaPreDealA配合
完成第一次变换，变换成三角矩阵
***********************************************************************************/
int CRightView::ParaDealA(double* Para, int SizeSrc)
{
	int i;
	for (i = SizeSrc; i; i--)
		if (ParaPreDealA(Para, SizeSrc, i))
			return -1;
	return 0;
}

/***********************************************************************************
系数矩阵行列式变换
***********************************************************************************/
int CRightView::ParaPreDealB(double* Para, int SizeSrc, int OffSet)
{
	int i, j;
	for (i = OffSet + 1; i < SizeSrc; i++)
	{
		for (j = OffSet + 1; j <= i; j++)
			ParaBuffer(Para, i, j) *= ParaBuffer(Para, OffSet, OffSet);
		ParaBuffer(Para, i, SizeSrc) = ParaBuffer(Para, i, SizeSrc) * ParaBuffer(Para, OffSet, OffSet) - ParaBuffer(Para, i, OffSet) * ParaBuffer(Para, OffSet, SizeSrc);
		ParaBuffer(Para, i, OffSet) = 0;
		ParalimitRow(Para, SizeSrc, i);
	}
	return 0;
}

/***********************************************************************************
系数矩阵行列式变换，与ParaPreDealB配合
完成第一次变换，变换成对角矩阵，变换完毕
***********************************************************************************/
int CRightView::ParaDealB(double* Para, int SizeSrc)
{
	int i;
	for (i = 0; i < SizeSrc; i++)
		if (ParaPreDealB(Para, SizeSrc, i))
			return -1;
	for (i = 0; i < SizeSrc; i++)
	{
		if (ParaBuffer(Para, i, i))
		{
			ParaBuffer(Para, i, SizeSrc) /= ParaBuffer(Para, i, i);
			ParaBuffer(Para, i, i) = 1.0;
		}
	}
	return 0;
}

/***********************************************************************************
系数矩阵变换
***********************************************************************************/
int CRightView::ParaDeal(double* Para, int SizeSrc)
{
	PrintPara(Para, SizeSrc);
	Paralimit(Para, SizeSrc);
	PrintPara(Para, SizeSrc);
	if (ParaDealA(Para, SizeSrc))
		return -1;
	PrintPara(Para, SizeSrc);
	if (ParaDealB(Para, SizeSrc))
		return -1;
	return 0;
}

/***********************************************************************************
最小二乘法的第一步就是从XY数据里面获取系数矩阵
double* Para：系数矩阵地址
const double* X：X数据地址
const double* Y：Y数据地址
int Amount：XY数据组数
int SizeSrc：系数矩阵大小（SizeSrc）行（SizeSrc + 1）列
***********************************************************************************/
int CRightView::GetParaBuffer(double* Para, const double* X, const double* Y, int Amount, int SizeSrc)
{
	int i, j;
	for (i = 0; i < SizeSrc; i++)
		for (ParaBuffer(Para, 0, i) = 0, j = 0; j < Amount; j++)
			ParaBuffer(Para, 0, i) += pow(*(X + j), 2 * (SizeSrc - 1) - i);
	for (i = 1; i < SizeSrc; i++)
		for (ParaBuffer(Para, i, SizeSrc - 1) = 0, j = 0; j < Amount; j++)
			ParaBuffer(Para, i, SizeSrc - 1) += pow(*(X + j), SizeSrc - 1 - i);
	for (i = 0; i < SizeSrc; i++)
		for (ParaBuffer(Para, i, SizeSrc) = 0, j = 0; j < Amount; j++)
			ParaBuffer(Para, i, SizeSrc) += (*(Y + j)) * pow(*(X + j), SizeSrc - 1 - i);
	for (i = 1; i < SizeSrc; i++)
		for (j = 0; j < SizeSrc - 1; j++)
			ParaBuffer(Para, i, j) = ParaBuffer(Para, i - 1, j + 1);
	return 0;
}

/***********************************************************************************
整个计算过程
***********************************************************************************/
int CRightView::CalNihe(const double* BufferX, const double* BufferY, int Amount, int SizeSrc, double* ParaResK)
{
	double* ParaK = (double*)malloc(SizeSrc * (SizeSrc + 1) * sizeof(double));
	GetParaBuffer(ParaK, BufferX, BufferY, Amount, SizeSrc);
	ParaDeal(ParaK, SizeSrc);
	for (Amount = 0; Amount < SizeSrc; Amount++, ParaResK++)
		*ParaResK = ParaBuffer(ParaK, Amount, SizeSrc);
	free(ParaK);
	return 0;
}
