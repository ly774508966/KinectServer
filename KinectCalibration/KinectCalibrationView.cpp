
// KinectCalibrationView.cpp : CKinectCalibrationView 类的实现
//

#include "stdafx.h"

#ifndef SHARED_HANDLERS
#include "KinectCalibration.h"
#endif
#include "MainFrm.h"
#include "KinectCalibrationView.h"
#include "ParamDlg.h"
#include "ColorDlg.h"
#include "BmpDlg.h"
#include "HelpDlg.h"
#include "VisualAngleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CKinectCalibrationView

IMPLEMENT_DYNCREATE(CKinectCalibrationView, CView)

BEGIN_MESSAGE_MAP(CKinectCalibrationView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CKinectCalibrationView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_COMMAND(ID_SET_PARAM, &CKinectCalibrationView::OnSetParam)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_CLOSE_Z0, &CKinectCalibrationView::OnCloseZ0)
	ON_COMMAND(ID_CLOSE_Z1, &CKinectCalibrationView::OnCloseZ1)
	ON_COMMAND(ID_CLOSE_A0, &CKinectCalibrationView::OnCloseA0)
	ON_COMMAND(ID_CLOSE_A1, &CKinectCalibrationView::OnCloseA1)
	ON_COMMAND(ID_CLOSE_B0, &CKinectCalibrationView::OnCloseB0)
	ON_COMMAND(ID_CLOSE_B1, &CKinectCalibrationView::OnCloseB1)
	ON_COMMAND(ID_RESET_VIEW, &CKinectCalibrationView::OnResetView)
	ON_COMMAND(ID_CLOSE_ALL, &CKinectCalibrationView::OnCloseAll)
	ON_COMMAND(ID_FILE_OPEN, &CKinectCalibrationView::OnFileOpen)
	ON_COMMAND(ID_SET_COLOR, &CKinectCalibrationView::OnSetColor)
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_SET_ANGLE, &CKinectCalibrationView::OnSetAngle)
	ON_COMMAND(ID_OPEN_ORIGIN, &CKinectCalibrationView::OnOpenOrigin)
	ON_COMMAND(ID_OPEN_AFTERFILTER, &CKinectCalibrationView::OnOpenAfterfilter)
	ON_UPDATE_COMMAND_UI(ID_OPEN_ORIGIN, &CKinectCalibrationView::OnUpdateOpenOriginTxt)
	ON_UPDATE_COMMAND_UI(ID_OPEN_AFTERFILTER, &CKinectCalibrationView::OnUpdateOpenfilterTxt)
	ON_COMMAND(ID_OPEN_PCD, &CKinectCalibrationView::OnOpenPcd)
	ON_UPDATE_COMMAND_UI(ID_OPEN_PCD, &CKinectCalibrationView::OnUpdateOpenPcd)
	ON_COMMAND(ID_SET_BMP, &CKinectCalibrationView::OnSetBmp)
	ON_COMMAND(ID_HELP, &CKinectCalibrationView::OnHelp)
END_MESSAGE_MAP()

	// CKinectCalibrationView 构造/析构
	//vector<POINT6D>  m_pPointsListZ0;


	//POINT3D prBoxCenter;
	//POINT3D prBoxSize;

CKinectCalibrationView::CKinectCalibrationView()
	{
		m_GLPixelIndex = 0;
		m_hRC = NULL;
		m_bInit = false;
		m_fDegreeX = 0.0;
		m_fDegreeY = 180.0;
		m_fDegreeZ = 0.0;
		m_fTranslateX = 0.0;
		m_fTranslateY = 0.0;
		m_fTranslateZ = 0.0;
		m_fDeltaDegree = 15.0;
		m_bLButtonDown = false;
		m_bRButtonDown = false;
		m_bShowZ0 = TRUE;
		m_bShowZ1 = TRUE;
		m_bShowA0 = TRUE;
		m_bShowA1 = TRUE;
		m_bShowB0 = TRUE;
		m_bShowB1 = TRUE;
		m_nViewOpenGL.SetProjectionMode(1);
		m_nViewOpenGL.SetTwoView(false);
		m_bOpenOriginTxt = false;
		m_bOpenPcd = true;
		m_sFilepath = L"";
		m_bNewFilepath = true;//一开始当然认为是进入了一个新的文件夹路径
		//m_dlgBmp = new CBmpDlg;
		prMax.x = -10000000.0;
		prMax.y = -10000000.0;
		prMax.z = -10000000.0;
		prMin.x = 10000000.0;
		prMin.y = 10000000.0;
		prMin.z = 10000000.0;
	}

CKinectCalibrationView::~CKinectCalibrationView()
	{

	}

#ifdef _DEBUG
void CKinectCalibrationView::AssertValid() const
{
	CView::AssertValid();
}
void CKinectCalibrationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CKinectCalibrationDoc* CKinectCalibrationView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKinectCalibrationDoc)));
	return (CKinectCalibrationDoc*)m_pDocument;
}
#endif //_DEBUG

BOOL CKinectCalibrationView::PreCreateWindow(CREATESTRUCT& cs)
	{
		//  CREATESTRUCT cs 来修改窗口类或样式


		return CView::PreCreateWindow(cs);
	}


// CKinectCalibrationView 打印


void CKinectCalibrationView::OnFilePrintPreview()
	{
#ifndef SHARED_HANDLERS
		AFXPrintPreview(this);
#endif
	}

BOOL CKinectCalibrationView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// 默认准备
		return DoPreparePrinting(pInfo);
	}

void CKinectCalibrationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{

	}

void CKinectCalibrationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{

	}

void CKinectCalibrationView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
	{
#ifndef SHARED_HANDLERS
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
	}

void CKinectCalibrationView::OnDraw(CDC* pDC)
	{
		CKinectCalibrationDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		if (!m_bInit)
		{
			m_bInit = true;
		}
		//这两处注释掉才能正常拖动

		m_nViewOpenGL.OnInitRenderOpenGL();
		//CPaintDC dc(this); // device context for painting
		DrawGL();
		//SwapBuffers(dc.m_hDC);
		m_nViewOpenGL.SwapBufferOpenGL();
		CString str;
		str.Format(_T("X:%.1f	    Y:%.1f       Z:%.1f       当前单位转角为：%.1f"),m_fDegreeX,m_fDegreeY,m_fDegreeZ,m_fDeltaDegree);
		((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetWindowText(str);
	}


// CKinectCalibrationView 消息处理程序
void CKinectCalibrationView::ReadSysInfo()
{
	CString m_sPath;
	GetModuleFileName(NULL,m_sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	int pos = m_sPath.ReverseFind('\\');
	m_sPath = m_sPath.Left(pos);
	FILE *fp;
	//读取sys.txt的数据,不受Debug还是Release的影响
	CString sysPath=m_sPath+_T("\\初始文件\\sys.txt");
	USES_CONVERSION;
	fp=fopen(W2A(sysPath),"r");
	char ch=fgetc(fp);
	if(ch==EOF)
		MessageBox(_T("系统参数错误"));
	else
	{
		fseek(fp,0,SEEK_SET);
		memset(m_Rz0,0,sizeof(float)*15);
		memset(m_Rz1,0,sizeof(float)*15);
		memset(m_Rb0,0,sizeof(float)*15);
		memset(m_Rb1,0,sizeof(float)*15);
		memset(m_Rz0,0,sizeof(float)*15);
		memset(m_Rz1,0,sizeof(float)*15);

		float temp[1][3];

		fscanf(fp,"%f%f%f",&m_Rz0[0][0],&m_Rz0[0][1],&m_Rz0[0][2]);
		fscanf(fp,"%f%f%f",&m_Rz0[1][0],&m_Rz0[1][1],&m_Rz0[1][2]);
		fscanf(fp,"%f%f%f",&m_Rz0[2][0],&m_Rz0[2][1],&m_Rz0[2][2]);
		fscanf(fp,"%f%f%f",&m_Tz0[0][0],&m_Tz0[0][1],&m_Tz0[0][2]);
		fscanf(fp, "%f%f%f", &temp[0][0], &temp[0][1], &temp[0][2]);  //跳过无用行
		GetMatrixInverse(m_Rz0, 3, g_inverseRz0);

		fscanf(fp,"%f%f%f",&m_Ra0[0][0],&m_Ra0[0][1],&m_Ra0[0][2]);
		fscanf(fp,"%f%f%f",&m_Ra0[1][0],&m_Ra0[1][1],&m_Ra0[1][2]);
		fscanf(fp,"%f%f%f",&m_Ra0[2][0],&m_Ra0[2][1],&m_Ra0[2][2]);
		fscanf(fp,"%f%f%f",&m_Ta0[0][0],&m_Ta0[0][1],&m_Ta0[0][2]);
		fscanf(fp, "%f%f%f", &temp[0][0], &temp[0][1], &temp[0][2]);  //跳过无用行
		GetMatrixInverse(m_Ra0, 3, g_inverseRa0);

		fscanf(fp,"%f%f%f",&m_Rb0[0][0],&m_Rb0[0][1],&m_Rb0[0][2]);
		fscanf(fp,"%f%f%f",&m_Rb0[1][0],&m_Rb0[1][1],&m_Rb0[1][2]);
		fscanf(fp,"%f%f%f",&m_Rb0[2][0],&m_Rb0[2][1],&m_Rb0[2][2]);
		fscanf(fp,"%f%f%f",&m_Tb0[0][0],&m_Tb0[0][1],&m_Tb0[0][2]);
		fscanf(fp, "%f%f%f", &temp[0][0], &temp[0][1], &temp[0][2]);  //跳过无用行
		GetMatrixInverse(m_Rb0, 3, g_inverseRb0);

		fscanf(fp,"%f%f%f",&m_Rz1[0][0],&m_Rz1[0][1],&m_Rz1[0][2]);
		fscanf(fp,"%f%f%f",&m_Rz1[1][0],&m_Rz1[1][1],&m_Rz1[1][2]);
		fscanf(fp,"%f%f%f",&m_Rz1[2][0],&m_Rz1[2][1],&m_Rz1[2][2]);
		fscanf(fp,"%f%f%f",&m_Tz1[0][0],&m_Tz1[0][1],&m_Tz1[0][2]);
		fscanf(fp, "%f%f%f", &temp[0][0], &temp[0][1], &temp[0][2]);  //跳过无用行
		GetMatrixInverse(m_Rz1, 3, g_inverseRz1);

		fscanf(fp,"%f%f%f",&m_Ra1[0][0],&m_Ra1[0][1],&m_Ra1[0][2]);
		fscanf(fp,"%f%f%f",&m_Ra1[1][0],&m_Ra1[1][1],&m_Ra1[1][2]);
		fscanf(fp,"%f%f%f",&m_Ra1[2][0],&m_Ra1[2][1],&m_Ra1[2][2]);
		fscanf(fp,"%f%f%f",&m_Ta1[0][0],&m_Ta1[0][1],&m_Ta1[0][2]);
		fscanf(fp, "%f%f%f", &temp[0][0], &temp[0][1], &temp[0][2]);  //跳过无用行
		GetMatrixInverse(m_Ra1, 3, g_inverseRa1);

		fscanf(fp,"%f%f%f",&m_Rb1[0][0],&m_Rb1[0][1],&m_Rb1[0][2]);
		fscanf(fp,"%f%f%f",&m_Rb1[1][0],&m_Rb1[1][1],&m_Rb1[1][2]);
		fscanf(fp,"%f%f%f",&m_Rb1[2][0],&m_Rb1[2][1],&m_Rb1[2][2]);
		fscanf(fp,"%f%f%f",&m_Tb1[0][0],&m_Tb1[0][1],&m_Tb1[0][2]);
		GetMatrixInverse(m_Rb1, 3, g_inverseRb1);
	}
	fclose(fp);
	fp=NULL;
	
	//释放缓冲区
	m_sPath.ReleaseBuffer();
}

void CKinectCalibrationView::ReadIniInfo()
{
	CString m_sPath;
	GetModuleFileName(NULL, m_sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	int pos = m_sPath.ReverseFind('\\');
	m_sPath = m_sPath.Left(pos);
	//读取info.ini的数据
	int r, g, b;
	CString infoPath = m_sPath + _T("\\初始文件\\info.ini");
	r = GetPrivateProfileInt(_T("sys"), _T("Z0_R"), 255, infoPath);
	g = GetPrivateProfileInt(_T("sys"), _T("Z0_G"), 255, infoPath);
	b = GetPrivateProfileInt(_T("sys"), _T("Z0_B"), 255, infoPath);
	m_bUseZ0 = GetPrivateProfileInt(_T("sys"), _T("Z0_USE"), 0, infoPath);
	m_colorZ0 = RGB(r, g, b);

	r = GetPrivateProfileInt(_T("sys"), _T("Z1_R"), 255, infoPath);
	g = GetPrivateProfileInt(_T("sys"), _T("Z1_G"), 255, infoPath);
	b = GetPrivateProfileInt(_T("sys"), _T("Z1_B"), 255, infoPath);
	m_bUseZ1 = GetPrivateProfileInt(_T("sys"), _T("Z1_USE"), 0, infoPath);
	m_colorZ1 = RGB(r, g, b);

	r = GetPrivateProfileInt(_T("sys"), _T("A0_R"), 255, infoPath);
	g = GetPrivateProfileInt(_T("sys"), _T("A0_G"), 255, infoPath);
	b = GetPrivateProfileInt(_T("sys"), _T("A0_B"), 255, infoPath);
	m_bUseA0 = GetPrivateProfileInt(_T("sys"), _T("A0_USE"), 0, infoPath);
	m_colorA0 = RGB(r, g, b);
	r = GetPrivateProfileInt(_T("sys"), _T("A1_R"), 255, infoPath);
	g = GetPrivateProfileInt(_T("sys"), _T("A1_G"), 255, infoPath);
	b = GetPrivateProfileInt(_T("sys"), _T("A1_B"), 255, infoPath);
	m_bUseA1 = GetPrivateProfileInt(_T("sys"), _T("A1_USE"), 0, infoPath);
	m_colorA1 = RGB(r, g, b);

	r = GetPrivateProfileInt(_T("sys"), _T("B0_R"), 255, infoPath);
	g = GetPrivateProfileInt(_T("sys"), _T("B0_G"), 255, infoPath);
	b = GetPrivateProfileInt(_T("sys"), _T("B0_B"), 255, infoPath);
	m_bUseB0 = GetPrivateProfileInt(_T("sys"), _T("B0_USE"), 0, infoPath);
	m_colorB0 = RGB(r, g, b);

	r = GetPrivateProfileInt(_T("sys"), _T("B1_R"), 255, infoPath);
	g = GetPrivateProfileInt(_T("sys"), _T("B1_G"), 255, infoPath);
	b = GetPrivateProfileInt(_T("sys"), _T("B1_B"), 255, infoPath);
	m_bUseB1 = GetPrivateProfileInt(_T("sys"), _T("B1_USE"), 0, infoPath);
	m_colorB1 = RGB(r, g, b);

	CString strTemp;
	GetPrivateProfileString(_T("sys"), _T("Z0_delta"), _T("0.0"), strTemp.GetBuffer(10), 10, infoPath);
	strTemp.ReleaseBuffer();
	m_deltaZ0 = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"), _T("Z0_contrast"), _T("0.0"), strTemp.GetBuffer(10), 10, infoPath);
	strTemp.ReleaseBuffer();
	m_contrastZ0 = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"), _T("Z0_light"), _T("0.0"), strTemp.GetBuffer(10), 10, infoPath);
	strTemp.ReleaseBuffer();
	m_lightZ0 = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"), _T("A0_delta"), _T("0.0"), strTemp.GetBuffer(10), 10, infoPath);
	strTemp.ReleaseBuffer();
	m_deltaA0 = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"), _T("A0_contrast"), _T("0.0"), strTemp.GetBuffer(10), 10, infoPath);
	strTemp.ReleaseBuffer();
	m_contrastA0 = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"), _T("A0_light"), _T("0.0"), strTemp.GetBuffer(10), 10, infoPath);
	strTemp.ReleaseBuffer();
	m_lightA0 = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"), _T("B0_delta"), _T("0.0"), strTemp.GetBuffer(10), 10, infoPath);
	strTemp.ReleaseBuffer();
	m_deltaB0 = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"), _T("B0_contrast"), _T("0.0"), strTemp.GetBuffer(10), 10, infoPath);
	strTemp.ReleaseBuffer();
	m_contrastB0 = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"), _T("B0_light"), _T("0.0"), strTemp.GetBuffer(10), 10, infoPath);
	strTemp.ReleaseBuffer();
	m_lightB0 = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"), _T("Z1_delta"), _T("0.0"), strTemp.GetBuffer(10), 10, infoPath);
	strTemp.ReleaseBuffer();
	m_deltaZ1 = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"), _T("Z1_contrast"), _T("0.0"), strTemp.GetBuffer(10), 10, infoPath);
	strTemp.ReleaseBuffer();
	m_contrastZ1 = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"), _T("Z1_light"), _T("0.0"), strTemp.GetBuffer(10), 10, infoPath);
	strTemp.ReleaseBuffer();
	m_lightZ1 = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"), _T("A1_delta"), _T("0.0"), strTemp.GetBuffer(10), 10, infoPath);
	strTemp.ReleaseBuffer();
	m_deltaA1 = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"), _T("A1_contrast"), _T("0.0"), strTemp.GetBuffer(10), 10, infoPath);
	strTemp.ReleaseBuffer();
	m_contrastA1 = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"), _T("A1_light"), _T("0.0"), strTemp.GetBuffer(10), 10, infoPath);
	strTemp.ReleaseBuffer();
	m_lightA1 = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"), _T("B1_delta"), _T("0.0"), strTemp.GetBuffer(10), 10, infoPath);
	strTemp.ReleaseBuffer();
	m_deltaB1 = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"), _T("B1_contrast"), _T("0.0"), strTemp.GetBuffer(10), 10, infoPath);
	strTemp.ReleaseBuffer();
	m_contrastB1 = _wtof(strTemp);
	GetPrivateProfileString(_T("sys"), _T("B1_light"), _T("0.0"), strTemp.GetBuffer(10), 10, infoPath);
	strTemp.ReleaseBuffer();
	m_lightB1 = _wtof(strTemp);
	//释放缓冲区
	m_sPath.ReleaseBuffer();
}

void CKinectCalibrationView::ShowPoint(CString filename)
{
	CString sType = filename.Right(3);
	if (sType==L"txt") {
		ReadTxtPoint(filename);
	}else if (sType==L"pcd") {
		m_bNewFilepath = false;//读取完成后就不再是新的路径了
		m_sFilepath = filename.Left(filename.GetLength() - 6);//只记录文件夹的路径
		CString sBmpfile = filename.Left(filename.GetLength() - 3) + L"bmp";
		CFileFind ff;
		if (!ff.FindFile(sBmpfile)){//首先判断是否存在对应的图片，不存在的话退出，以免出现bug
			MessageBox(L"找不到对应的纹理数据");
			return;
		}
		ff.Close();
		ReadBmpFile(sBmpfile);
		ReadPcdPoint(filename);
		GetCloudByBmp(filename);
	}else {
		MessageBox(L"错误的文件类型");
	}
	
	this->PostMessage(WM_SIZE);
	//InvalidateRect(NULL,FALSE);	
}


void CKinectCalibrationView::ReadPcdPoint(CString filename)
{
	CStdioFile file;
	BOOL ret = file.Open(filename, CFile::modeRead);
	if (!ret)
	{
		AfxMessageBox(L"打开文件失败");
		return;
	}
	CString strLine;
	//前面11行是头信息，没有用
	for (int i = 0; i < 11;i++) {
		file.ReadString(strLine);
	}
	if (filename.Find(_T("Z0")) != -1) {
		g_T[0][0] = m_Tz0[0][0]; g_T[0][1] = m_Tz0[0][1]; g_T[0][2] = m_Tz0[0][2];
		g_inverseR[0][0] = g_inverseRz0[0][0]; g_inverseR[0][1] = g_inverseRz0[0][1]; g_inverseR[0][2] = g_inverseRz0[0][2];
		g_inverseR[1][0] = g_inverseRz0[1][0]; g_inverseR[1][1] = g_inverseRz0[1][1]; g_inverseR[1][2] = g_inverseRz0[1][2];
		g_inverseR[2][0] = g_inverseRz0[2][0]; g_inverseR[2][1] = g_inverseRz0[2][1]; g_inverseR[2][2] = g_inverseRz0[2][2];
		while (file.ReadString(strLine)) {
			CString ss;
			int i = 0;
			CString number[4];
			while (AfxExtractSubString(ss, strLine, i, _T(' ')))
				number[i++] = ss;
			float numberX = _wtof(number[0]);
			float numberY = _wtof(number[1]);
			float numberZ = _wtof(number[2]);
			float xx = numberX - g_T[0][0];
			float yy = numberY - g_T[0][1];
			float zz = numberZ - g_T[0][2];
			float x = g_inverseR[0][0] * xx + g_inverseR[0][1] * yy + g_inverseR[0][2] * zz;
			float y = g_inverseR[1][0] * xx + g_inverseR[1][1] * yy + g_inverseR[1][2] * zz;
			float z = g_inverseR[2][0] * xx + g_inverseR[2][1] * yy + g_inverseR[2][2] * zz;
			int jj = int(x / (PARAM_X*z) + 320 + 0.5);//用于四舍五入
			int ii = int(240 - y / (PARAM_Y*z) + 0.5);//用于四舍五入
			MyPoint point;
			point.i = ii; point.j = jj; point.x = numberX; point.y = numberY; point.z = numberZ;
			m_myCloudZ0.push_back(point);
		}
	}else if (filename.Find(_T("A0")) != -1) {
		g_T[0][0] = m_Ta0[0][0]; g_T[0][1] = m_Ta0[0][1]; g_T[0][2] = m_Ta0[0][2];
		g_inverseR[0][0] = g_inverseRa0[0][0]; g_inverseR[0][1] = g_inverseRa0[0][1]; g_inverseR[0][2] = g_inverseRa0[0][2];
		g_inverseR[1][0] = g_inverseRa0[1][0]; g_inverseR[1][1] = g_inverseRa0[1][1]; g_inverseR[1][2] = g_inverseRa0[1][2];
		g_inverseR[2][0] = g_inverseRa0[2][0]; g_inverseR[2][1] = g_inverseRa0[2][1]; g_inverseR[2][2] = g_inverseRa0[2][2];
		while (file.ReadString(strLine)) {
			CString ss;
			int i = 0;
			CString number[4];
			while (AfxExtractSubString(ss, strLine, i, _T(' ')))
				number[i++] = ss;
			float numberX = _wtof(number[0]);
			float numberY = _wtof(number[1]);
			float numberZ = _wtof(number[2]);
			float xx = numberX - g_T[0][0];
			float yy = numberY - g_T[0][1];
			float zz = numberZ - g_T[0][2];
			float x = g_inverseR[0][0] * xx + g_inverseR[0][1] * yy + g_inverseR[0][2] * zz;
			float y = g_inverseR[1][0] * xx + g_inverseR[1][1] * yy + g_inverseR[1][2] * zz;
			float z = g_inverseR[2][0] * xx + g_inverseR[2][1] * yy + g_inverseR[2][2] * zz;
			int jj = int(x / (PARAM_X*z) + 320 + 0.5);//用于四舍五入
			int ii = int(240 - y / (PARAM_Y*z) + 0.5);//用于四舍五入
			MyPoint point;
			point.i = ii; point.j = jj; point.x = numberX; point.y = numberY; point.z = numberZ;
			m_myCloudA0.push_back(point);
		}
	}else if (filename.Find(_T("B0")) != -1) {
		g_T[0][0] = m_Tb0[0][0]; g_T[0][1] = m_Tb0[0][1]; g_T[0][2] = m_Tb0[0][2];
		g_inverseR[0][0] = g_inverseRb0[0][0]; g_inverseR[0][1] = g_inverseRb0[0][1]; g_inverseR[0][2] = g_inverseRb0[0][2];
		g_inverseR[1][0] = g_inverseRb0[1][0]; g_inverseR[1][1] = g_inverseRb0[1][1]; g_inverseR[1][2] = g_inverseRb0[1][2];
		g_inverseR[2][0] = g_inverseRb0[2][0]; g_inverseR[2][1] = g_inverseRb0[2][1]; g_inverseR[2][2] = g_inverseRb0[2][2];
		while (file.ReadString(strLine)) {
			CString ss;
			int i = 0;
			CString number[4];
			while (AfxExtractSubString(ss, strLine, i, _T(' ')))
				number[i++] = ss;
			float numberX = _wtof(number[0]);
			float numberY = _wtof(number[1]);
			float numberZ = _wtof(number[2]);
			float xx = numberX - g_T[0][0];
			float yy = numberY - g_T[0][1];
			float zz = numberZ - g_T[0][2];
			float x = g_inverseR[0][0] * xx + g_inverseR[0][1] * yy + g_inverseR[0][2] * zz;
			float y = g_inverseR[1][0] * xx + g_inverseR[1][1] * yy + g_inverseR[1][2] * zz;
			float z = g_inverseR[2][0] * xx + g_inverseR[2][1] * yy + g_inverseR[2][2] * zz;
			int jj = int(x / (PARAM_X*z) + 320 + 0.5);//用于四舍五入
			int ii = int(240 - y / (PARAM_Y*z) + 0.5);//用于四舍五入
			MyPoint point;
			point.i = ii; point.j = jj; point.x = numberX; point.y = numberY; point.z = numberZ;
			m_myCloudB0.push_back(point);
		}
	}else if (filename.Find(_T("Z1")) != -1) {
 		g_T[0][0] = m_Tz1[0][0]; g_T[0][1] = m_Tz1[0][1]; g_T[0][2] = m_Tz1[0][2];
 		g_inverseR[0][0] = 1.0; g_inverseR[0][1] = 0.0; g_inverseR[0][2] = 0.0;
 		g_inverseR[1][0] = 0.0; g_inverseR[1][1] = 1.0; g_inverseR[1][2] = 0.0;
 		g_inverseR[2][0] = 0.0; g_inverseR[2][1] = 0.0; g_inverseR[2][2] = 1.0;
		while (file.ReadString(strLine)) {
			CString ss;
			int i = 0;
			CString number[4];
			while (AfxExtractSubString(ss, strLine, i, _T(' ')))
				number[i++] = ss;
			float numberX = _wtof(number[0]);
			float numberY = _wtof(number[1]);
			float numberZ = _wtof(number[2]);
			float xx = numberX - g_T[0][0];
			float yy = numberY - g_T[0][1];
			float zz = numberZ - g_T[0][2];
			float x = g_inverseR[0][0] * xx + g_inverseR[0][1] * yy + g_inverseR[0][2] * zz;
			float y = g_inverseR[1][0] * xx + g_inverseR[1][1] * yy + g_inverseR[1][2] * zz;
			float z = g_inverseR[2][0] * xx + g_inverseR[2][1] * yy + g_inverseR[2][2] * zz;
			int jj = int(x / (PARAM_X*z) + 320 + 0.5);//用于四舍五入
			int ii = int(240 - y / (PARAM_Y*z) + 0.5);//用于四舍五入
			MyPoint point;
			point.i = ii; point.j = jj; point.x = numberX; point.y = numberY; point.z = numberZ;
			m_myCloudZ1.push_back(point);
		}
	}else if (filename.Find(_T("A1")) != -1) {
 		g_T[0][0] = m_Ta1[0][0]; g_T[0][1] = m_Ta1[0][1]; g_T[0][2] = m_Ta1[0][2];
 		g_inverseR[0][0] = g_inverseRa1[0][0]; g_inverseR[0][1] = g_inverseRa1[0][1]; g_inverseR[0][2] = g_inverseRa1[0][2];
 		g_inverseR[1][0] = g_inverseRa1[1][0]; g_inverseR[1][1] = g_inverseRa1[1][1]; g_inverseR[1][2] = g_inverseRa1[1][2];
 		g_inverseR[2][0] = g_inverseRa1[2][0]; g_inverseR[2][1] = g_inverseRa1[2][1]; g_inverseR[2][2] = g_inverseRa1[2][2];
		while (file.ReadString(strLine)) {
			CString ss;
			int i = 0;
			CString number[4];
			while (AfxExtractSubString(ss, strLine, i, _T(' ')))
				number[i++] = ss;
			float numberX = _wtof(number[0]);
			float numberY = _wtof(number[1]);
			float numberZ = _wtof(number[2]);
			float xx = numberX - g_T[0][0];
			float yy = numberY - g_T[0][1];
			float zz = numberZ - g_T[0][2];
			float x = g_inverseR[0][0] * xx + g_inverseR[0][1] * yy + g_inverseR[0][2] * zz;
			float y = g_inverseR[1][0] * xx + g_inverseR[1][1] * yy + g_inverseR[1][2] * zz;
			float z = g_inverseR[2][0] * xx + g_inverseR[2][1] * yy + g_inverseR[2][2] * zz;
			int jj = int(x / (PARAM_X*z) + 320 + 0.5);//用于四舍五入
			int ii = int(240 - y / (PARAM_Y*z) + 0.5);//用于四舍五入
			MyPoint point;
			point.i = ii; point.j = jj; point.x = numberX; point.y = numberY; point.z = numberZ;
			m_myCloudA1.push_back(point);
		}
	}else if (filename.Find(_T("B1")) != -1) {
		g_T[0][0] = m_Tb1[0][0]; g_T[0][1] = m_Tb1[0][1]; g_T[0][2] = m_Tb1[0][2];
		g_inverseR[0][0] = g_inverseRb1[0][0]; g_inverseR[0][1] = g_inverseRb1[0][1]; g_inverseR[0][2] = g_inverseRb1[0][2];
		g_inverseR[1][0] = g_inverseRb1[1][0]; g_inverseR[1][1] = g_inverseRb1[1][1]; g_inverseR[1][2] = g_inverseRb1[1][2];
		g_inverseR[2][0] = g_inverseRb1[2][0]; g_inverseR[2][1] = g_inverseRb1[2][1]; g_inverseR[2][2] = g_inverseRb1[2][2];
		while (file.ReadString(strLine)) {
			CString ss;
			int i = 0;
			CString number[4];
			while (AfxExtractSubString(ss, strLine, i, _T(' ')))
				number[i++] = ss;
			float numberX = _wtof(number[0]);
			float numberY = _wtof(number[1]);
			float numberZ = _wtof(number[2]);
			float xx = numberX - g_T[0][0];
			float yy = numberY - g_T[0][1];
			float zz = numberZ - g_T[0][2];
			float x = g_inverseR[0][0] * xx + g_inverseR[0][1] * yy + g_inverseR[0][2] * zz;
			float y = g_inverseR[1][0] * xx + g_inverseR[1][1] * yy + g_inverseR[1][2] * zz;
			float z = g_inverseR[2][0] * xx + g_inverseR[2][1] * yy + g_inverseR[2][2] * zz;
			int jj = int(x / (PARAM_X*z) + 320 + 0.5);//用于四舍五入
			int ii = int(240 - y / (PARAM_Y*z) + 0.5);//用于四舍五入
			MyPoint point;
			point.i = ii; point.j = jj; point.x = numberX; point.y = numberY; point.z = numberZ;
			m_myCloudB1.push_back(point);
		}
	}
}

void CKinectCalibrationView::ReadBmpFile(CString filename)
{
	float delta;//atof(g_sDelta.c_str());//最暗的时候，点之间的平均间距
	float contrast;//atof(g_sZenyi.c_str());//对比度增益
	float light;//atof(g_sLight.c_str());//亮度提升
	if (filename.Find(_T("Z0")) != -1) {
		delta = m_deltaZ0;
		contrast = m_contrastZ0;
		light = m_lightZ0;
		for (int i = 0; i < BMP_HEIGHT; i++) {
			for (int j = 0; j < BMP_WIDTH; j++) {
				m_nBmpZ0[i][j] = false;
			}
		}
		if (m_pointsZ0_new.size() != 0){
			m_pointsZ0_new.clear();
		}
	}else if (filename.Find(_T("A0")) != -1) {
		delta = m_deltaA0;
		contrast = m_contrastA0;
		light = m_lightA0;
		for (int i = 0; i < BMP_HEIGHT; i++) {
			for (int j = 0; j < BMP_WIDTH; j++) {
				m_nBmpA0[i][j] = false;
			}
		}
		if (m_pointsA0_new.size() != 0){
			m_pointsA0_new.clear();
		}
	}else if (filename.Find(_T("B0")) != -1) {
		delta = m_deltaB0;
		contrast = m_contrastB0;
		light = m_lightB0;
		for (int i = 0; i < BMP_HEIGHT; i++) {
			for (int j = 0; j < BMP_WIDTH; j++) {
				m_nBmpB0[i][j] = false;
			}
		}
		if (m_pointsB0_new.size() != 0){
			m_pointsB0_new.clear();
		}
	}else if (filename.Find(_T("Z1")) != -1) {
		delta = m_deltaZ1;
		contrast = m_contrastZ1;
		light = m_lightZ1;
		for (int i = 0; i < BMP_HEIGHT; i++) {
			for (int j = 0; j < BMP_WIDTH; j++) {
				m_nBmpZ1[i][j] = false;
			}
		}
		if (m_pointsZ1_new.size() != 0){
			m_pointsZ1_new.clear();
		}
	}else if (filename.Find(_T("A1")) != -1) {
		delta = m_deltaA1;
		contrast = m_contrastA1;
		light = m_lightA1;
		for (int i = 0; i < BMP_HEIGHT; i++) {
			for (int j = 0; j < BMP_WIDTH; j++) {
				m_nBmpA1[i][j] = false;
			}
		}
		if (m_pointsA1_new.size() != 0){
			m_pointsA1_new.clear();
		}
	}else if (filename.Find(_T("B1")) != -1) {
		delta = m_deltaB1;
		contrast = m_contrastB1;
		light = m_lightB1;
		for (int i = 0; i < BMP_HEIGHT; i++) {
			for (int j = 0; j < BMP_WIDTH; j++) {
				m_nBmpB1[i][j] = false;
			}
		}
		if (m_pointsB1_new.size() != 0){
			m_pointsB1_new.clear();
		}
	}

	//宽字符类型的CString转普通string
	setlocale(LC_ALL, "chs");
	char* p = new char[200];//足够大即可
	wcstombs(p, filename, 200);
	string str = p;

	Mat imgOri = imread(str);
	int g_width = imgOri.cols;
	int g_height = imgOri.rows;
	Mat_<uchar> img_grayOri;
	cvtColor(imgOri, img_grayOri, CV_BGR2GRAY);//rgb图片转换为灰度图片
	//找到图片中的最亮点和最暗点
	int minGray = 255, maxGray = 0;
	for (auto iter = img_grayOri.begin(); iter < img_grayOri.end(); iter++) {
		if (*iter<minGray) {
			minGray = *iter;
		}
		if (*iter > maxGray) {
			maxGray = *iter;
		}
	}
	//调整亮度和对比度
	Mat img_gray = Mat::zeros(img_grayOri.size(), img_grayOri.type());
	for (int y = 0; y < img_grayOri.rows; y++) {
		for (int x = 0; x < img_grayOri.cols; x++) {
			img_gray.at<uchar>(y, x) = saturate_cast<uchar>(contrast * (img_grayOri.at<uchar>(y, x)) + light);
		}
	}

	bool pointArray[1000][1000] = { false };
	pointArray[0][0] = true;

	disArray.clear();
	for (int i = 0; i <= 255; i++) {
		float dis = (delta - 1) - (delta - 2.3) / 255.0*i;//根据阈值的不同，计算各个灰度下的平均间隔
		disArray.push_back(dis);
	}

	int integer = 0;
	float dis, decimals = 0;
	for (int y = 0; y < g_height; y++) {
		uchar* p = img_gray.ptr<uchar>(y);
		for (int x = 0; x < g_width - 1;) {
			float dis1 = disArray[p[x]];
			float dis2 = disArray[p[x + 1]];
			dis = (dis1 + dis2) / 2 + decimals;//加上上一次运算留下的小数位
			integer = dis;//向下取整
			if (integer == 0) {
				integer = 1;//至少要有一个间隔
				decimals = dis;//得到小数位的值
			}
			else {
				decimals = dis - integer;//得到小数位的值
			}

			x += integer;//水平方向间隔n个单位
			//这里需要判端新的点(x,y)和上侧各个点的距离是否满足要求
			bool bTrue = true;
			for (int yy = y - 1; yy > y - delta && yy >= 0; yy--) {
				uchar* pp = img_gray.ptr<uchar>(yy);
				for (int xx = x - delta; xx < x + delta && xx >= 0 && xx <= g_width; xx++) {
					if (pointArray[yy][xx] == true) {
						float dis3 = disArray[pp[xx]];//根据上一行点的灰度计算间隔
						float dis4 = (dis1 + dis3) / 2;
						float realDis = (xx - x)*(xx - x) + (yy - y)*(yy - y);
						if (realDis < dis4*dis4) {
							bTrue = false;
							yy = y - delta;//跳出外部循环
							break;//跳出内部循环
						}
					}
				}
			}
			if (bTrue) {
				pointArray[y][x] = true;
				if (filename.Find(_T("Z0")) != -1) {
					if (p[x]>160) {
						m_nBmpZ0[y][x] = 3;//三层点云
					}else if (p[x]>128) {
						m_nBmpZ0[y][x] = 2;//两层点云
					}else {
						m_nBmpZ0[y][x] = 1;//一层点云
					}
				}else if (filename.Find(_T("A0")) != -1) {
					if (p[x] > 160) {
						m_nBmpA0[y][x] = 3;//三层点云
					}
					else if (p[x] > 128) {
						m_nBmpA0[y][x] = 2;//两层点云
					}
					else {
						m_nBmpA0[y][x] = 1;//一层点云
					}
				}else if (filename.Find(_T("B0")) != -1) {
					if (p[x] > 160) {
						m_nBmpB0[y][x] = 3;//三层点云
					}
					else if (p[x] > 128) {
						m_nBmpB0[y][x] = 2;//两层点云
					}
					else {
						m_nBmpB0[y][x] = 1;//一层点云
					}
				}else if (filename.Find(_T("Z1")) != -1) {
					if (p[x] > 160) {
						m_nBmpZ1[y][x] = 3;//三层点云
					}
					else if (p[x] > 128) {
						m_nBmpZ1[y][x] = 2;//两层点云
					}
					else {
						m_nBmpZ1[y][x] = 1;//一层点云
					}
				}else if (filename.Find(_T("A1")) != -1) {
					if (p[x] > 160) {
						m_nBmpA1[y][x] = 3;//三层点云
					}
					else if (p[x] > 128) {
						m_nBmpA1[y][x] = 2;//两层点云
					}
					else {
						m_nBmpA1[y][x] = 1;//一层点云
					}
				}else if (filename.Find(_T("B1")) != -1) {
					if (p[x] > 160) {
						m_nBmpB1[y][x] = 3;//三层点云
					}
					else if (p[x] > 128) {
						m_nBmpB1[y][x] = 2;//两层点云
					}
					else {
						m_nBmpB1[y][x] = 1;//一层点云
					}
				}
			}
		}
	}
}

void CKinectCalibrationView::GetCloudByBmp(CString filename)
{
	if (filename.Find(_T("Z0")) != -1) {
		if (m_pointsZ0_new.size() != 0){
			m_pointsZ0_new.clear();
		}
		for (auto iter = m_myCloudZ0.begin(); iter < m_myCloudZ0.end();iter++) {
			POINT6D point;
			for (int k = 0; k < m_nBmpZ0[iter->i][iter->j];k++) {
				point.x = iter->x; point.y = iter->y;
				point.z = iter->z - k*1.78;
				point.r = point.g = point.b = 255;
				prMax.x = max(prMax.x, point.x); prMin.x = min(prMin.x, point.x);
				prMax.y = max(prMax.y, point.y); prMin.y = min(prMin.y, point.y);
				prMax.z = max(prMax.z, point.z); prMin.z = min(prMin.z, point.z);
				m_pointsZ0_new.push_back(point);
			}
		}
	}else if (filename.Find(_T("A0")) != -1) {
		if (m_pointsA0_new.size() != 0){
			m_pointsA0_new.clear();
		}
		for (auto iter = m_myCloudA0.begin(); iter < m_myCloudA0.end(); iter++) {
			POINT6D point;
			for (int k = 0; k < m_nBmpA0[iter->i][iter->j]; k++) {
				point.x = iter->x; point.y = iter->y;
				point.z = iter->z - k*1.78;
				point.r = point.g = point.b = 255;
				prMax.x = max(prMax.x, point.x); prMin.x = min(prMin.x, point.x);
				prMax.y = max(prMax.y, point.y); prMin.y = min(prMin.y, point.y);
				prMax.z = max(prMax.z, point.z); prMin.z = min(prMin.z, point.z);
				m_pointsA0_new.push_back(point);
			}
		}
	}else if (filename.Find(_T("B0")) != -1) {
		if (m_pointsB0_new.size() != 0){
			m_pointsB0_new.clear();
		}
		for (auto iter = m_myCloudB0.begin(); iter < m_myCloudB0.end(); iter++) {
			POINT6D point;
			for (int k = 0; k < m_nBmpB0[iter->i][iter->j]; k++) {
				point.x = iter->x; point.y = iter->y;
				point.z = iter->z - k*1.78;
				point.r = point.g = point.b = 255;
				prMax.x = max(prMax.x, point.x); prMin.x = min(prMin.x, point.x);
				prMax.y = max(prMax.y, point.y); prMin.y = min(prMin.y, point.y);
				prMax.z = max(prMax.z, point.z); prMin.z = min(prMin.z, point.z);
				m_pointsB0_new.push_back(point);
			}
		}
	}else if (filename.Find(_T("Z1")) != -1) {
		if (m_pointsZ1_new.size() != 0){
			m_pointsZ1_new.clear();
		}
		for (auto iter = m_myCloudZ1.begin(); iter < m_myCloudZ1.end(); iter++) {
			POINT6D point;
			for (int k = 0; k < m_nBmpZ1[iter->i][iter->j]; k++) {
				point.x = iter->x; point.y = iter->y;
				point.z = iter->z - k*1.78;
				point.r = point.g = point.b = 255;
				prMax.x = max(prMax.x, point.x); prMin.x = min(prMin.x, point.x);
				prMax.y = max(prMax.y, point.y); prMin.y = min(prMin.y, point.y);
				prMax.z = max(prMax.z, point.z); prMin.z = min(prMin.z, point.z);
				m_pointsZ1_new.push_back(point);
			}
		}
	}else if (filename.Find(_T("A1")) != -1) {
		if (m_pointsA1_new.size() != 0){
			m_pointsA1_new.clear();
		}
		for (auto iter = m_myCloudA1.begin(); iter < m_myCloudA1.end(); iter++) {
			POINT6D point;
			for (int k = 0; k < m_nBmpA1[iter->i][iter->j]; k++) {
				point.x = iter->x; point.y = iter->y;
				point.z = iter->z - k*1.78;
				point.r = point.g = point.b = 255;
				prMax.x = max(prMax.x, point.x); prMin.x = min(prMin.x, point.x);
				prMax.y = max(prMax.y, point.y); prMin.y = min(prMin.y, point.y);
				prMax.z = max(prMax.z, point.z); prMin.z = min(prMin.z, point.z);
				m_pointsA1_new.push_back(point);
			}
		}
	}else if (filename.Find(_T("B1")) != -1) {
		if (m_pointsB1_new.size() != 0){
			m_pointsB1_new.clear();
		}
		for (auto iter = m_myCloudB1.begin(); iter < m_myCloudB1.end(); iter++) {
			POINT6D point;
			for (int k = 0; k < m_nBmpB1[iter->i][iter->j]; k++) {
				point.x = iter->x; point.y = iter->y;
				point.z = iter->z - k*1.78;
				point.r = point.g = point.b = 255;
				prMax.x = max(prMax.x, point.x); prMin.x = min(prMin.x, point.x);
				prMax.y = max(prMax.y, point.y); prMin.y = min(prMin.y, point.y);
				prMax.z = max(prMax.z, point.z); prMin.z = min(prMin.z, point.z);
				m_pointsB1_new.push_back(point);
			}
		}
	}
	prBoxCenter = (prMax + prMin) / 2;
	prBoxSize = (prMax - prMin) / 2;
	m_nViewOpenGL.SetBox(tagCVector(prBoxCenter.x, prBoxCenter.y, prBoxCenter.z), tagCVector(prBoxSize.x, prBoxSize.y, prBoxSize.z));
	InvalidateRect(NULL, FALSE);
}

void CKinectCalibrationView::ReadTxtPoint(CString filename)
	{
		USES_CONVERSION;
		FILE *p_txt= fopen(W2A(filename),"r");
		if (p_txt == NULL)
		{
			fclose(p_txt);
			return ;
		}
		//////////////////////////////////////////////////////////////////////////
		//检索文件开头
		//   int nSize = sizeof('\n');
		TCHAR tHead ;
		int nBegin = 0;
		tHead = fgetc(p_txt);//   tHead = fgetc(p_txt);
		switch(tHead)
		{
		case EOF://
			nBegin = 0;
			break;
		case '!'://Catia
			//OnFileOpenCATIA(p_txt);
			return;
			// nBegin = 50;
			break;
		case '#': //Geomagic    
			nBegin = 30;
			break;
		default:
			nBegin = 0;
			break;
		}
		fseek(p_txt , nBegin , SEEK_SET);
		//检索文件开头
		//////////////////////////////////////////////////////////////////////////
		//检索文件结尾 是否有字符串标志
		fseek(p_txt ,-14L , SEEK_END);
		char  schar[14]="";
		fgets(schar , 13 , p_txt);
		schar[13] = ('\0');
		CString str;
		str.Format(_T("%s"),schar);
		int nEndCloud = str.Find(_T("cloud"));
		int nEnd = -1;
		if (nEndCloud == -1)
			nEnd = EOF;
		else if (nEndCloud != 6)
		{
			nEndCloud = nEndCloud - 20;
			nEnd = fseek(p_txt ,nEndCloud , SEEK_END);
		}

		//////////////////////////////////////////////////////////////////////////
		fseek(p_txt , nBegin , SEEK_SET);

		POINT6D f_points;

		if (filename.Find(_T("Z0"))!=-1)
		{
			m_pointsZ0.clear();//	POINT3D f_xyz;
			while (fscanf(p_txt,"%f %f %f %f %f %f",&f_points.x,&f_points.y,&f_points.z,&f_points.r,&f_points.g,&f_points.b) != nEnd)
				m_pointsZ0.push_back(f_points);
			ChangeMatrix(filename);
		}
		if (filename.Find(_T("Z1"))!=-1)
		{
			m_pointsZ1.clear();//	POINT3D f_xyz;
			while (fscanf(p_txt,"%f %f %f %f %f %f",&f_points.x,&f_points.y,&f_points.z,&f_points.r,&f_points.g,&f_points.b) != nEnd)
				m_pointsZ1.push_back(f_points);
			ChangeMatrix(filename);
		}
		if (filename.Find(_T("A0"))!=-1)
		{
			m_pointsA0.clear();//	POINT3D f_xyz;
			while (fscanf(p_txt,"%f %f %f %f %f %f",&f_points.x,&f_points.y,&f_points.z,&f_points.r,&f_points.g,&f_points.b) != nEnd)
				m_pointsA0.push_back(f_points);
			ChangeMatrix(filename);
		}
		if (filename.Find(_T("A1"))!=-1)
		{
			m_pointsA1.clear();//	POINT3D f_xyz;
			while (fscanf(p_txt,"%f %f %f %f %f %f",&f_points.x,&f_points.y,&f_points.z,&f_points.r,&f_points.g,&f_points.b) != nEnd)
				m_pointsA1.push_back(f_points);
			ChangeMatrix(filename);
		}
		if (filename.Find(_T("B0"))!=-1)
		{
			m_pointsB0.clear();//	POINT3D f_xyz;
			while (fscanf(p_txt,"%f %f %f %f %f %f",&f_points.x,&f_points.y,&f_points.z,&f_points.r,&f_points.g,&f_points.b) != nEnd)
				m_pointsB0.push_back(f_points);
			ChangeMatrix(filename);
		}
		if (filename.Find(_T("B1"))!=-1)
		{
			m_pointsB1.clear();//	POINT3D f_xyz;
			while (fscanf(p_txt,"%f %f %f %f %f %f",&f_points.x,&f_points.y,&f_points.z,&f_points.r,&f_points.g,&f_points.b) != nEnd)
				m_pointsB1.push_back(f_points);
			ChangeMatrix(filename);
		}  

		fclose(p_txt);//	vector <POINT3D>::iterator pItVector1,pItVector2;//为字符数组定义游标iterator

	}

	void CKinectCalibrationView::ChangeMatrix(CString filename)
	{
		//ReadSysInfo();
		//POINT6D f_points_new;
		/*if (m_bOpenOriginTxt)
		{
		m_pointsZ0_new = m_pointsZ0;
		m_pointsZ1_new = m_pointsZ1;
		m_pointsA0_new = m_pointsA0;
		m_pointsA1_new = m_pointsA1;
		m_pointsB0_new = m_pointsB0;
		m_pointsB1_new = m_pointsB1;
		return;
		}*/
		if (filename.Find(_T("Z0"))!=-1)
		{
			//vector<POINT6D> m_pointsZ1;
			//vector<POINT6D> m_pointsZ1_new;
			//float      m_Rz1[3][3];     //旋转矩阵a
			//float      m_Tz1[1][3];     //平移矩阵
			if (m_pointsZ0_new.size()!=0)
			{
				m_pointsZ0_new.clear();
			}
			int length = m_pointsZ0.size();
			vector<POINT6D>::iterator pIterator;
			POINT6D tempPoint;
			if (!m_pointsZ0.empty())
			{
				for (pIterator = m_pointsZ0.begin() ; pIterator != m_pointsZ0.end()-1 ; ++pIterator)
				{
					tempPoint = *pIterator;
					float x = pIterator->x;
					float y = pIterator->y;
					float z = pIterator->z;
					if (m_bOpenOriginTxt)//如果打开的是原始文件，则需要乘上转换矩阵
					{
						tempPoint.x=m_Rz0[0][0]*x+m_Rz0[0][1]*y+m_Rz0[0][2]*z+m_Tz0[0][0];
						tempPoint.y=m_Rz0[1][0]*x+m_Rz0[1][1]*y+m_Rz0[1][2]*z+m_Tz0[0][1];
						tempPoint.z=m_Rz0[2][0]*x+m_Rz0[2][1]*y+m_Rz0[2][2]*z+m_Tz0[0][2];  
					}
					else
					{
						tempPoint.x = x;
						tempPoint.y= y;
						tempPoint.z = z;
					}
					m_pointsZ0_new.push_back(tempPoint);
					prMax.x=max(prMax.x,tempPoint.x);
					prMax.y=max(prMax.y,tempPoint.y);
					prMax.z=max(prMax.z,tempPoint.z);
					prMin.x=min(prMin.x,tempPoint.x);
					prMin.y=min(prMin.y,tempPoint.y);
					prMin.z=min(prMin.z,tempPoint.z);		 
				}
			}
			else
			{
				OutputDebugString(_T("Z0读取时可能出现问题！\n"));//重新执行时，出现问题，暂时没有找到问题所在
			}
		}
		if (filename.Find(_T("Z1"))!=-1)
		{
			//vector<POINT6D> m_pointsZ1;
			//vector<POINT6D> m_pointsZ1_new;
			//float      m_Rz1[3][3];     //旋转矩阵a
			//float      m_Tz1[1][3];     //平移矩阵
			if (m_pointsZ1_new.size()!=0)
			{
				m_pointsZ1_new.clear();
			}
			int length = m_pointsZ1.size();
			vector<POINT6D>::iterator pIterator;
			POINT6D tempPoint;
			if (!m_pointsZ1.empty())
			{
				for (pIterator = m_pointsZ1.begin() ; pIterator != m_pointsZ1.end()-1 ; ++pIterator)
				{
					tempPoint = *pIterator;
					float x = pIterator->x;
					float y = pIterator->y;
					float z = pIterator->z;
					if (m_bOpenOriginTxt)//如果打开的是滤波后的文件
					{
						tempPoint.x=m_Rz1[0][0]*x+m_Rz1[0][1]*y+m_Rz1[0][2]*z+m_Tz1[0][0];
						tempPoint.y=m_Rz1[1][0]*x+m_Rz1[1][1]*y+m_Rz1[1][2]*z+m_Tz1[0][1];
						tempPoint.z=m_Rz1[2][0]*x+m_Rz1[2][1]*y+m_Rz1[2][2]*z+m_Tz1[0][2];  
					}
					else
					{
						tempPoint.x = x;
						tempPoint.y= y;
						tempPoint.z = z;
					}
					m_pointsZ1_new.push_back(tempPoint);
					prMax.x=max(prMax.x,tempPoint.x);
					prMax.y=max(prMax.y,tempPoint.y);
					prMax.z=max(prMax.z,tempPoint.z);
					prMin.x=min(prMin.x,tempPoint.x);
					prMin.y=min(prMin.y,tempPoint.y);
					prMin.z=min(prMin.z,tempPoint.z);		 
				}
			}
			else
			{
				OutputDebugString(_T("Z1读取时可能出现问题！\n"));//重新执行时，出现问题，暂时没有找到问题所在
			}
		}
		if (filename.Find(_T("A0"))!=-1)
		{
			//vector<POINT6D> m_pointsA0;
			//vector<POINT6D> m_pointsA0_new;
			//float      m_Ra0[3][3];     //旋转矩阵a
			//float      m_Ta0[1][3];     //平移矩阵
			if (m_pointsA0_new.size()!=0)
			{
				m_pointsA0_new.clear();
			}
			int length = m_pointsA0.size();
			vector<POINT6D>::iterator pIterator;
			POINT6D tempPoint;
			if (!m_pointsA0.empty())
			{
				for (pIterator = m_pointsA0.begin() ; pIterator != m_pointsA0.end()-1 ; ++pIterator)
				{
					tempPoint = *pIterator;
					float x = pIterator->x;
					float y = pIterator->y;
					float z = pIterator->z;
					if (m_bOpenOriginTxt)//如果打开的是滤波后的文件
					{
						tempPoint.x=m_Ra0[0][0]*x+m_Ra0[0][1]*y+m_Ra0[0][2]*z+m_Ta0[0][0];
						tempPoint.y=m_Ra0[1][0]*x+m_Ra0[1][1]*y+m_Ra0[1][2]*z+m_Ta0[0][1];
						tempPoint.z=m_Ra0[2][0]*x+m_Ra0[2][1]*y+m_Ra0[2][2]*z+m_Ta0[0][2];  
					}
					else
					{
						tempPoint.x = x;
						tempPoint.y= y;
						tempPoint.z = z;
					}
					m_pointsA0_new.push_back(tempPoint);
					prMax.x=max(prMax.x,tempPoint.x);
					prMax.y=max(prMax.y,tempPoint.y);
					prMax.z=max(prMax.z,tempPoint.z);
					prMin.x=min(prMin.x,tempPoint.x);
					prMin.y=min(prMin.y,tempPoint.y);
					prMin.z=min(prMin.z,tempPoint.z);		 
				}
			}
			else
			{
				OutputDebugString(_T("A0读取时可能出现问题！\n"));//重新执行时，出现问题，暂时没有找到问题所在
			}
		}
		if (filename.Find(_T("A1"))!=-1)
		{
			//vector<POINT6D> m_pointsA1;
			//vector<POINT6D> m_pointsA1_new;
			//float      m_Ra1[3][3];     //旋转矩阵a
			//float      m_Ta1[1][3];     //平移矩阵
			//程序第二次到这里时，该变量内部为错误的空间
			if (m_pointsA1_new.size()!=0)
			{
				m_pointsA1_new.clear();
			}
			int length = m_pointsA1.size();
			vector<POINT6D>::iterator pIterator;
			POINT6D tempPoint;
			if (!m_pointsA1.empty())
			{
				for (pIterator = m_pointsA1.begin() ; pIterator != m_pointsA1.end()-1 ; ++pIterator)
				{
					tempPoint = *pIterator;
					float x = pIterator->x;
					float y = pIterator->y;
					float z = pIterator->z;
					if (m_bOpenOriginTxt)//如果打开的是滤波后的文件
					{
						tempPoint.x=m_Ra1[0][0]*x+m_Ra1[0][1]*y+m_Ra1[0][2]*z+m_Ta1[0][0];
						tempPoint.y=m_Ra1[1][0]*x+m_Ra1[1][1]*y+m_Ra1[1][2]*z+m_Ta1[0][1];
						tempPoint.z=m_Ra1[2][0]*x+m_Ra1[2][1]*y+m_Ra1[2][2]*z+m_Ta1[0][2];  
					}
					else
					{
						tempPoint.x = x;
						tempPoint.y= y;
						tempPoint.z = z;
					}
					
					m_pointsA1_new.push_back(tempPoint);
					prMax.x=max(prMax.x,tempPoint.x);
					prMax.y=max(prMax.y,tempPoint.y);
					prMax.z=max(prMax.z,tempPoint.z);
					prMin.x=min(prMin.x,tempPoint.x);
					prMin.y=min(prMin.y,tempPoint.y);
					prMin.z=min(prMin.z,tempPoint.z);		 
				}
			}
			else
			{
				OutputDebugString(_T("A1读取时可能出现问题！\n"));//重新执行时，出现问题，暂时没有找到问题所在
			}
		}
		if (filename.Find(_T("B0"))!=-1)
		{
			//vector<POINT6D> m_pointsB0;
			//vector<POINT6D> m_pointsB0_new;
			//float      m_Rb0[3][3];     //旋转矩阵a
			//float      m_Tb0[1][3];     //平移矩阵
			if (m_pointsB0_new.size()!=0)
			{
				m_pointsB0_new.clear();
			}
			int length = m_pointsB0.size();
			vector<POINT6D>::iterator pIterator;
			POINT6D tempPoint;
			if (!m_pointsB0.empty())
			{
				for (pIterator = m_pointsB0.begin() ; pIterator != m_pointsB0.end()-1 ; ++pIterator)
				{
					tempPoint = *pIterator;
					float x = pIterator->x;
					float y = pIterator->y;
					float z = pIterator->z;
					if (m_bOpenOriginTxt)//如果打开的是滤波后的文件
					{
						tempPoint.x=m_Rb0[0][0]*x+m_Rb0[0][1]*y+m_Rb0[0][2]*z+m_Tb0[0][0];
						tempPoint.y=m_Rb0[1][0]*x+m_Rb0[1][1]*y+m_Rb0[1][2]*z+m_Tb0[0][1];
						tempPoint.z=m_Rb0[2][0]*x+m_Rb0[2][1]*y+m_Rb0[2][2]*z+m_Tb0[0][2];  
					}
					else
					{
						tempPoint.x = x;
						tempPoint.y= y;
						tempPoint.z = z;
					}
					
					m_pointsB0_new.push_back(tempPoint);
					prMax.x=max(prMax.x,tempPoint.x);
					prMax.y=max(prMax.y,tempPoint.y);
					prMax.z=max(prMax.z,tempPoint.z);
					prMin.x=min(prMin.x,tempPoint.x);
					prMin.y=min(prMin.y,tempPoint.y);
					prMin.z=min(prMin.z,tempPoint.z);		 
				}
			}
			else
			{
				OutputDebugString(_T("B0读取时可能出现问题！\n"));//重新执行时，出现问题，暂时没有找到问题所在
			}
		}
		if (filename.Find(_T("B1"))!=-1)
		{
			//vector<POINT6D> m_pointsB1;
			//vector<POINT6D> m_pointsB1_new;
			//float      m_Rb1[3][3];     //旋转矩阵a
			//float      m_Tb1[1][3];     //平移矩阵
			if (m_pointsB1_new.size()!=0)
			{
				m_pointsB1_new.clear();
			}
			int length = m_pointsB1.size();
			vector<POINT6D>::iterator pIterator;
			POINT6D tempPoint;
			if (!m_pointsB1.empty())
			{
				for (pIterator = m_pointsB1.begin() ; pIterator != m_pointsB1.end()-1 ; ++pIterator)
				{
					tempPoint = *pIterator;
					float x = pIterator->x;
					float y = pIterator->y;
					float z = pIterator->z;
					if (m_bOpenOriginTxt)//如果打开的是滤波后的文件
					{
						tempPoint.x=m_Rb1[0][0]*x+m_Rb1[0][1]*y+m_Rb1[0][2]*z+m_Tb1[0][0];
						tempPoint.y=m_Rb1[1][0]*x+m_Rb1[1][1]*y+m_Rb1[1][2]*z+m_Tb1[0][1];
						tempPoint.z=m_Rb1[2][0]*x+m_Rb1[2][1]*y+m_Rb1[2][2]*z+m_Tb1[0][2];  
					}
					else
					{
						tempPoint.x = x;
						tempPoint.y= y;
						tempPoint.z = z;
					}
					
					m_pointsB1_new.push_back(tempPoint);
					prMax.x=max(prMax.x,tempPoint.x);
					prMax.y=max(prMax.y,tempPoint.y);
					prMax.z=max(prMax.z,tempPoint.z);
					prMin.x=min(prMin.x,tempPoint.x);
					prMin.y=min(prMin.y,tempPoint.y);
					prMin.z=min(prMin.z,tempPoint.z);		 
				}
			}
			else
			{
				OutputDebugString(_T("B1读取时可能出现问题！\n"));//重新执行时，出现问题，暂时没有找到问题所在
			}
		}
		prBoxCenter = (prMax+prMin) / 2;
		prBoxSize = (prMax-prMin) / 2;
		m_nViewOpenGL.SetBox(tagCVector(prBoxCenter.x,prBoxCenter.y,prBoxCenter.z),tagCVector(prBoxSize.x , prBoxSize.y , prBoxSize.z));
		InvalidateRect(NULL,FALSE);	
	}
void CKinectCalibrationView::DrawGL()
	{
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Clear Screen And Depth Buffer
		//glLoadIdentity();                                    // Reset The Current Modelview Matrix
		//glClearColor(15/255.0,56/255.0,120/255.0,0.0);
		glRotatef(m_fDegreeX,1.0f,0.0f,0.0f);
		glRotatef(m_fDegreeY,0.0f,1.0f,0.0f);
		glRotatef(m_fDegreeZ,0.0f,0.0f,1.0f);

		CRect rect;
		GetClientRect(&rect);
		GLfloat scale=0.95*GLfloat(rect.Height())/prBoxSize.y;
		glScalef(scale,scale,scale);
		//glClearColor(15/255.0,56/255.0,120/255.0,0.0);						// Black Background
		glBegin(GL_POINTS);
		if (m_fDegreeY<=0&&m_fDegreeY>=-90)
		{
			//从上向下看
			if (m_fDegreeX>=0)
			{
				DrawZ1();
				DrawZ0();
				DrawB1();
				DrawB0();
				DrawA1();
				DrawA0();		
			}
			else
			{
				DrawZ0();
				DrawZ1();
				DrawB0();
				DrawB1();
				DrawA0();		
				DrawA1();
			}
		}
		else if (m_fDegreeY>0&&m_fDegreeY<=90)
		{
			if (m_fDegreeX>=0)
			{
				DrawZ1();
				DrawZ0();
				DrawA1();
				DrawA0();
				DrawB1();
				DrawB0();
			}
			else
			{
				DrawZ0();
				DrawZ1();		
				DrawA0();
				DrawA1();
				DrawB0();
				DrawB1();
			}
		}
		else if((m_fDegreeY>=-180&&m_fDegreeY<-90)||m_fDegreeY==180.0)
		{
			if (m_fDegreeX>=0)
			{
				DrawB1();
				DrawB0();
				DrawA1();
				DrawA0();
				DrawZ1();
				DrawZ0();
			}
			else
			{
				DrawB0();
				DrawB1();
				DrawA0();
				DrawA1();
				DrawZ0();
				DrawZ1();
			}
			
		}
		else// (m_fDegreeY>-70&&m_fDegreeY<70)
		{
			if (m_fDegreeX>=0)
			{
				DrawA1();
				DrawA0();
				DrawB1();
				DrawB0();
				DrawZ1();
				DrawZ0();
			}
			else
			{
				DrawA0();
				DrawA1();
				DrawB0();
				DrawB1();
				DrawZ0();
				DrawZ1();
			}
		}

		glEnd();
		glFlush();
	}

bool CKinectCalibrationView::InitGL(void)
	{
		glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
		//glClearColor(0.0,0.0,0.2,0.0);						// Black Background
		glClearColor(15/255.0,56/255.0,120/255.0,0.0);						// Black Background

		glEnable(GL_BLEND);									// Enables Depth Testing
		glBlendFunc(GL_SRC_ALPHA,GL_ZERO);
		glClearDepth(1.0f);                                  // Depth Buffer Setup
		glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
		glEnable(GL_COLOR_MATERIAL);                            // Enables Depth Testing
		glDepthFunc(GL_LEQUAL);                                // The Type Of Depth Testing To Do
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);    // Really Nice Perspective Calculations
		return TRUE;                                        // Initialization Went OK
	}
bool CKinectCalibrationView::SetWindowPixelFormat(HDC hDC)
	{
		//定义窗口的像素格式
		PIXELFORMATDESCRIPTOR pixelDesc=
		{
			sizeof(PIXELFORMATDESCRIPTOR),           //nSize结构长度
			1,                                       //nVersion结构版本
			PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL| 
			PFD_DOUBLEBUFFER,        //dwFlags告诉OpenGL如何处理像素PFD_SUPPORT_GDI

			PFD_TYPE_RGBA,  //iPixelType,颜色模式，包括两种PFD_TYPE_RGBA意味着每一位(bit)组代表着rgb各分量的值。PFD_TYPE_COLORINDEX意味着每一位组代表着在彩色查找表中的索引值
			24,   //cColorBits定义了指定一个颜色的位数。对RGBA来说，位数是在颜色中红、绿、蓝各分量所占的位数。对颜色的索引值来说，指的是表中的颜色数。
			0,0,0,0,0,0,  //cRedBits、cRedShifts、cGreenBits、cGreenShifts、cBlueBits、cBlueShifts用,基本不被采用，一般置0
			0,                                       //cAlphaBits,RGB颜色缓存中Alpha的位数                            
			0,                                 //cAlphaShift，已经不被采用，置0                   
			0,                                       //cAcuumBits累计缓存的位数
			0,0,0,0,                                 //cAcuumRedBits/cAcuumGreenBits/cAcuumBlueBits/cAcuumAlphaBits,基本不被采用，置0
			32,                                      //cDepthBits深度缓存的位数
			0,                                       //cStencilBits,模板缓存的位数
			0,                                       //cAuxBuffers，辅助缓存的位数，一般置0
			PFD_MAIN_PLANE,                          //iLayerType,说明层面的类型，可忽略置0，是早期的版本，包括
			0,0,0,0                                  //bReserved,dwLayerMask,dwVisibleMask,dwDamageMask,必须置0
		};

		this->m_GLPixelIndex = ChoosePixelFormat(hDC,&pixelDesc);//选择最相近的像素格式
		/*
		ChoosePixelFormat接受两个参数：一个是hDc，另一个是一个指向PIXELFORMATDESCRIPTOR结构的指针&pixelDesc
		该函数返回此像素格式的索引值,如果返回0则表示失败。
		假如函数失败，我们只是把索引值设为1并用 DescribePixelFormat得到像素格式描述。
		假如你申请一个没得到支持的像素格式，则ChoosePixelFormat将会返回与你要求的像素格式最接近的一个值
		一旦我们得到一个像素格式的索引值和相应的描述，我们就可以调用SetPixelFormat设置像素格式，并且只需设置一次。
		*/
		if(this->m_GLPixelIndex==0)
		{//选择失败
			this->m_GLPixelIndex = 1;//默认的像素格式
			//用默认的像素格式进行设置
			//
			if(DescribePixelFormat(hDC,this->m_GLPixelIndex,sizeof(PIXELFORMATDESCRIPTOR),&pixelDesc)==0)
			{
				return FALSE;
			}
		}

		if(SetPixelFormat(hDC,this->m_GLPixelIndex,&pixelDesc)==FALSE)
		{
			return FALSE;
		}
		return TRUE;
	}
bool CKinectCalibrationView::CreateViewGLContext(HDC hDC)
	{
		//WglCreateContext函数创建一个新的OpenGL渲染描述表(RC)
		//此描述表必须适用于绘制到由hdc返回的设备
		//这个渲染描述表将有和设备上下文(dc)一样的像素格式.
		this->m_hRC = wglCreateContext(hDC);//创建RC

		if(this->m_hRC==NULL)
		{//创建失败
			return FALSE;
		}

		/*
		wglMakeCurrent 函数设定OpenGL当前线程(线程相关性)的渲染环境。
		以后这个线程所有的OpenGL调用都是在这个hdc标识的设备上绘制。
		你也可以使用wglMakeCurrent 函数来改变调用线程的当前渲染环境
		使之不再是当前的渲染环境。
		*/
		if(wglMakeCurrent(hDC,this->m_hRC)==FALSE)
		{//选为当前RC失败
			return FALSE;
		}
		return TRUE;
	}
void CKinectCalibrationView::Destory()
	{
		::ReleaseDC(m_hWnd, m_hDC);

		if(wglGetCurrentContext()!=NULL)
		{
			wglMakeCurrent(NULL,NULL);
		}
		if(this->m_hRC!=NULL)
		{
			wglDeleteContext(this->m_hRC);
			this->m_hRC = NULL;
		}
	}
void CKinectCalibrationView::OnDestroy()
	{
		CView::OnDestroy();
		Destory();
		//m_nViewOpenGL.OnDestroyOpenGL();	
	}
int CKinectCalibrationView::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CView::OnCreate(lpCreateStruct) == -1)
			return -1;
		ReadSysInfo();
		ReadIniInfo();
		//HWND hWnd = this->GetSafeHwnd();	//得到一个窗口对象（CWnd的派生对象）指针的句柄（HWND）  
		//HDC hDC = ::GetDC(hWnd);	//GetDC该函数检索一指定窗口的客户区域或整个屏幕的显示设备上下文环境的句柄,
		//if(this->SetWindowPixelFormat(hDC)==FALSE)	//设置像素格式
		//	return 0;
		//if(this->CreateViewGLContext(hDC)==FALSE)	//创建RC并选为所用
		//	return 0;
		//if(!this->InitGL())			//初始化openGL
		//	return 0;

		m_nViewOpenGL.OnInitOpenGL(GetSafeHwnd());	
		return 0;
	}

BOOL CKinectCalibrationView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	m_nViewOpenGL.OnMouseWheel(nFlags, zDelta, pt);
	InvalidateRect(NULL,FALSE);	
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
void CKinectCalibrationView::OnLButtonDown(UINT nFlags, CPoint point)
	{
		//m_bLButtonDown = true;
		m_nViewOpenGL.OnLButtonDown(nFlags,point);	
		CView::OnLButtonDown(nFlags, point);
	}
void CKinectCalibrationView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		//m_bLButtonDown = true;
		m_nViewOpenGL.OnLButtonUp(nFlags,point);
		InvalidateRect(NULL,FALSE); 	
		CView::OnLButtonUp(nFlags, point);
	}
void CKinectCalibrationView::OnRButtonDown(UINT nFlags, CPoint point)
{
	/*m_oldpointR = point;
	m_bRButtonDown = true;*/
	//m_nViewOpenGL.OnRButtonDown(nFlags, point);	
	CView::OnRButtonDown(nFlags, point);
}
void CKinectCalibrationView::OnRButtonUp(UINT nFlags, CPoint point)
{
	//m_nViewOpenGL.OnRButtonUp(nFlags, point);	
	//InvalidateRect(NULL,FALSE);	
	CView::OnRButtonUp(nFlags, point);
}
void CKinectCalibrationView::OnMouseMove(UINT nFlags, CPoint point)
{
	/*CString str;
	str.Format(_T("x:%d	y:%d"),point.x,point.y);
	SetWindowText(str);*/
	m_nViewOpenGL.OnMouseMove(nFlags,point);
	InvalidateRect(NULL,FALSE); 	
	CView::OnMouseMove(nFlags, point);
}
void CKinectCalibrationView::OnMButtonDown(UINT nFlags, CPoint point)
{
	m_nViewOpenGL.OnMButtonDown(nFlags,point);	
	CView::OnMButtonDown(nFlags, point);
}
void CKinectCalibrationView::OnMButtonUp(UINT nFlags, CPoint point)
{
	m_nViewOpenGL.OnMButtonUp(nFlags,point);
	InvalidateRect(NULL,FALSE); 	
	CView::OnMButtonUp(nFlags, point);
}

BOOL CKinectCalibrationView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
	return CView::OnEraseBkgnd(pDC);
}

void CKinectCalibrationView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	//GLsizei width,height;
	//width = cx;
	//height = cy;
	//if (height==0)                                        // Prevent A Divide By Zero By
	//{
	//	height=1;                                        // Making Height Equal One
	//}

	//glViewport(0,0,width,height);                        // Reset The Current Viewport

	//glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
	//glLoadIdentity();                                    // Reset The Projection Matrix

	//// Calculate The Aspect Ratio Of The Window
	//gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);//透视投影
	//glMatrixMode(GL_MODELVIEW);                            // Select The Modelview Matrix
	//glLoadIdentity();                                    // Reset The Modelview Matrix
	//gluLookAt(0, 0, -2, 0, 0, 0, 0, 1, 0);  // 设置视点

	m_nViewOpenGL.OnSizeOpenGL(nType, cx, cy);	
}

inline double CKinectCalibrationView::PointsDistance(CPoint point1,CPoint point2)
{
	//return sqrt((point2.x-point1.x)*(point2.x-point1.x) + (point2.y-point1.y)*(point2.y-point1.y));
	return 0.0;
}

void CKinectCalibrationView::OnSetParam()
{
	//pView = (CKinectCalibrationView*)GetView(RUNTIME_CLASS(CKinectCalibrationView));
	CParamDlg *pDlg;
	pDlg = new CParamDlg(this);
	pDlg->Create(CParamDlg::IDD);
	pDlg->ShowWindow(SW_SHOW);
}

void CKinectCalibrationView::OnSetColor()
{
	CColorDlg *pDlg;
	pDlg = new CColorDlg(this);
	pDlg->Create(CColorDlg::IDD);
	pDlg->ShowWindow(SW_SHOW);
}

void CKinectCalibrationView::OnSetAngle()
{
	CVisualAngleDlg *pDlg;
	pDlg = new CVisualAngleDlg(this);
	pDlg->Create(CVisualAngleDlg::IDD);
	pDlg->ShowWindow(SW_SHOW);
}

void CKinectCalibrationView::OnSetBmp()
{
	if (m_bNewFilepath==true) {
		MessageBox(L"您需要先打开任意一个pcd文件");
		return;
	}else {
		//m_dlgBmp = new CBmpDlg;
		CBmpDlg *pDlg;
		pDlg = new CBmpDlg(this);
		pDlg->Create(CBmpDlg::IDD);
		pDlg->ShowWindow(SW_SHOW);
	}
}

void CKinectCalibrationView::OnHelp()
{
	CHelpDlg *pDlg;
	pDlg = new CHelpDlg(this);
	pDlg->Create(CHelpDlg::IDD);
	pDlg->ShowWindow(SW_SHOW);
}

void CKinectCalibrationView::OnOpenOrigin()
{
	m_bOpenOriginTxt = true;
	m_bOpenPcd = false;
}

void CKinectCalibrationView::OnUpdateOpenOriginTxt(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_bOpenOriginTxt == true && m_bOpenPcd == false);
}

void CKinectCalibrationView::OnOpenAfterfilter()
{
	m_bOpenOriginTxt = false;
	m_bOpenPcd = false;
}

void CKinectCalibrationView::OnUpdateOpenfilterTxt(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_bOpenOriginTxt == false && m_bOpenPcd == false);
}

void CKinectCalibrationView::OnOpenPcd()
{
	m_bOpenOriginTxt = false;
	m_bOpenPcd = true;
	OutputDebugString(L"test\n");
}


void CKinectCalibrationView::OnUpdateOpenPcd(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_bOpenOriginTxt == false && m_bOpenPcd == true);
}

void CKinectCalibrationView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch(nChar)
	{
	case VK_LEFT:   //右
		m_fDegreeY -= m_fDeltaDegree;
		if (m_fDegreeY<-180)
		{
			m_fDegreeY+= 360;
		}
		InvalidateRect(NULL,FALSE); 	
		break;
	case VK_RIGHT:   //右
		m_fDegreeY += m_fDeltaDegree;
		if (m_fDegreeY>180)
		{
			m_fDegreeY -= 360;
		}
		InvalidateRect(NULL,FALSE); 	
		break;
	case VK_UP:
		m_fDegreeX -= m_fDeltaDegree;
		if (m_fDegreeX<-90)
		{
			m_fDegreeX = -90;
		}
		InvalidateRect(NULL,FALSE); 	
		break;
	case  VK_DOWN:
		m_fDegreeX += m_fDeltaDegree;
		if (m_fDegreeX>90)
		{
			m_fDegreeX = 90;
		}
		InvalidateRect(NULL,FALSE);
		break;
	case  VK_PRIOR:
		m_fDegreeZ += m_fDeltaDegree;
		InvalidateRect(NULL,FALSE);
		break;
	case  VK_NEXT:
		m_fDegreeZ -= m_fDeltaDegree;
		InvalidateRect(NULL,FALSE);
		break;
	case VK_ESCAPE:
		break;
	}
	CString str;
	str.Format(_T("X:%.1f	    Y:%.1f       Z:%.1f       当前单位转角为：%.1f"),m_fDegreeX,m_fDegreeY,m_fDegreeZ,m_fDeltaDegree);
	((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetWindowText(str);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CKinectCalibrationView::OnCloseZ0()
{
	m_pointsZ0.clear();
	m_pointsZ0_new.clear();
	InvalidateRect(NULL,FALSE);
}
void CKinectCalibrationView::OnCloseZ1()
{
	m_pointsZ1.clear();
	m_pointsZ1_new.clear();
	InvalidateRect(NULL,FALSE);
}
void CKinectCalibrationView::OnCloseA0()
{
	m_pointsA0.clear();
	m_pointsA0_new.clear();
	InvalidateRect(NULL,FALSE);
}
void CKinectCalibrationView::OnCloseA1()
{
	m_pointsA1.clear();
	m_pointsA1_new.clear();
	InvalidateRect(NULL,FALSE);
}
void CKinectCalibrationView::OnCloseB0()
{
	m_pointsB0.clear();
	m_pointsB0_new.clear();
	InvalidateRect(NULL,FALSE);
}
void CKinectCalibrationView::OnCloseB1()
{
	m_pointsB1.clear();
	m_pointsB1_new.clear();
	InvalidateRect(NULL,FALSE);
}
void CKinectCalibrationView::OnCloseAll()
{
	m_pointsZ0.clear();
	m_pointsZ0_new.clear();
	m_pointsZ1.clear();
	m_pointsZ1_new.clear();
	m_pointsA0.clear();
	m_pointsA0_new.clear();
	m_pointsA1.clear();
	m_pointsA1_new.clear();
	m_pointsB0.clear();
	m_pointsB0_new.clear();
	m_pointsB1.clear();
	m_pointsB1_new.clear();
	InvalidateRect(NULL,FALSE);
}

void CKinectCalibrationView::OnResetView()
{
	m_fDegreeX = 0.0;
	m_fDegreeY = 0.0;
	m_fDegreeZ = 0.0;
	InvalidateRect(NULL,FALSE);
}
void CKinectCalibrationView::OnFileOpen()
{
	CString sPathname;
	CString sFileExt;//文件的扩展名
	LPTSTR lpszFilter;
	if (m_bOpenPcd==false) {
		lpszFilter = _T("ASCII Data Files(*.txt , *TXT)|*.txt||");//All Files(*.*)|*.*|                          |ASCII Data Files(*.asc , *ASC)|*.asc||
	}else {
		lpszFilter = _T("ASCII Data Files(*.pcd , *PCD)|*.pcd||");//All Files(*.*)|*.*|                          |ASCII Data Files(*.asc , *ASC)|*.asc||
	}
	CFileDialog p_dlg(true,_T(".txt"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT,lpszFilter,NULL);
	//pView = (CKinectCalibrationView*)GetView(RUNTIME_CLASS(CKinectCalibrationView));
	if (p_dlg.DoModal() == IDOK)
	{
		POSITION pos = p_dlg.GetStartPosition();
		while(pos!=NULL)
		{
			sPathname = p_dlg.GetNextPathName(pos);
			ShowPoint(sPathname);
		}
		InvalidateRect(NULL,FALSE);	
	}
	else 
		return ;
}

void CKinectCalibrationView::DrawZ0()
{
	if (!m_pointsZ0_new.empty()&&m_bShowZ0==TRUE)
	{
		int len = m_pointsZ0_new.size();
		vector<POINT6D>::iterator pItPoint3d;
		for (pItPoint3d = m_pointsZ0_new.begin() ; pItPoint3d != m_pointsZ0_new.end()-1 ; ++pItPoint3d)
		{
			if (m_bUseZ0)//若使用单色
			{
				glColor3f((GLfloat)GetRValue(m_colorZ0)/256.0,(GLfloat)GetGValue(m_colorZ0)/256.0,(GLfloat)GetBValue(m_colorZ0)/256.0);
			}
			else
			{
				glColor3f((GLfloat)pItPoint3d->r/256.0,(GLfloat)pItPoint3d->g/256.0,(GLfloat)pItPoint3d->b/256.0);
			}
			glVertex3f(pItPoint3d->x-prBoxCenter.x, pItPoint3d->y-prBoxCenter.y ,pItPoint3d->z-prBoxCenter.z);
		} 
	}  
}

void CKinectCalibrationView::DrawZ1()
{
	if (!m_pointsZ1_new.empty()&&m_bShowZ1==TRUE)
	{
		int len = m_pointsZ1_new.size();
		vector<POINT6D>::iterator pItPoint3d;
		for (pItPoint3d = m_pointsZ1_new.begin() ; pItPoint3d != m_pointsZ1_new.end()-1 ; ++pItPoint3d)
		{
			if (m_bUseZ1)//若使用单色
			{
				glColor3f((GLfloat)GetRValue(m_colorZ1)/256.0,(GLfloat)GetGValue(m_colorZ1)/256.0,(GLfloat)GetBValue(m_colorZ1)/256.0);
			}
			else
			{
				glColor3f((GLfloat)pItPoint3d->r/256.0,(GLfloat)pItPoint3d->g/256.0,(GLfloat)pItPoint3d->b/256.0);
			}
			glVertex3f(pItPoint3d->x-prBoxCenter.x, pItPoint3d->y-prBoxCenter.y ,pItPoint3d->z-prBoxCenter.z);
		} 
	} 
}

void CKinectCalibrationView::DrawA0()
{
	if (!m_pointsA0_new.empty()&&m_bShowA0==TRUE)
	{
		int len = m_pointsA0_new.size();
		vector<POINT6D>::iterator pItPoint3d;
		for (pItPoint3d = m_pointsA0_new.begin() ; pItPoint3d != m_pointsA0_new.end()-1 ; ++pItPoint3d)
		{
			if (m_bUseA0)//若使用单色
			{
				glColor3f((GLfloat)GetRValue(m_colorA0)/256.0,(GLfloat)GetGValue(m_colorA0)/256.0,(GLfloat)GetBValue(m_colorA0)/256.0);
			}
			else
			{
				glColor3f((GLfloat)pItPoint3d->r/256.0,(GLfloat)pItPoint3d->g/256.0,(GLfloat)pItPoint3d->b/256.0);
			}
			glVertex3f(pItPoint3d->x-prBoxCenter.x, pItPoint3d->y-prBoxCenter.y ,pItPoint3d->z-prBoxCenter.z);
		} 
	} 
}

void CKinectCalibrationView::DrawA1()
{
	if (!m_pointsA1_new.empty()&&m_bShowA1==TRUE)
	{
		int len = m_pointsA1_new.size();
		vector<POINT6D>::iterator pItPoint3d;
		for (pItPoint3d = m_pointsA1_new.begin() ; pItPoint3d != m_pointsA1_new.end()-1 ; ++pItPoint3d)
		{
			if (m_bUseA1)//若使用单色
			{
				glColor3f((GLfloat)GetRValue(m_colorA1)/256.0,(GLfloat)GetGValue(m_colorA1)/256.0,(GLfloat)GetBValue(m_colorA1)/256.0);
			}
			else
			{
				glColor3f((GLfloat)pItPoint3d->r/256.0,(GLfloat)pItPoint3d->g/256.0,(GLfloat)pItPoint3d->b/256.0);
			}
			glVertex3f(pItPoint3d->x-prBoxCenter.x, pItPoint3d->y-prBoxCenter.y ,pItPoint3d->z-prBoxCenter.z);
		} 
	} 
}

void CKinectCalibrationView::DrawB0()
{
	if (!m_pointsB0_new.empty()&&m_bShowB0==TRUE)
	{
		int len = m_pointsB0_new.size();
		vector<POINT6D>::iterator pItPoint3d;
		for (pItPoint3d = m_pointsB0_new.begin() ; pItPoint3d != m_pointsB0_new.end()-1 ; ++pItPoint3d)
		{
			if (m_bUseB0)//若使用单色
			{
				glColor3f((GLfloat)GetRValue(m_colorB0)/256.0,(GLfloat)GetGValue(m_colorB0)/256.0,(GLfloat)GetBValue(m_colorB0)/256.0);
			}
			else
			{
				glColor3f((GLfloat)pItPoint3d->r/256.0,(GLfloat)pItPoint3d->g/256.0,(GLfloat)pItPoint3d->b/256.0);
			}
			glVertex3f(pItPoint3d->x-prBoxCenter.x, pItPoint3d->y-prBoxCenter.y ,pItPoint3d->z-prBoxCenter.z);
		} 
	} 
}

void CKinectCalibrationView::DrawB1()
{
	if (!m_pointsB1_new.empty()&&m_bShowB1==TRUE)
	{
		int len = m_pointsB1_new.size();
		vector<POINT6D>::iterator pItPoint3d;
		for (pItPoint3d = m_pointsB1_new.begin() ; pItPoint3d != m_pointsB1_new.end()-1 ; ++pItPoint3d)
		{
			if (m_bUseB1)//若使用单色
			{
				glColor3f((GLfloat)GetRValue(m_colorB1)/256.0,(GLfloat)GetGValue(m_colorB1)/256.0,(GLfloat)GetBValue(m_colorB1)/256.0);
			}
			else
			{
				glColor3f((GLfloat)pItPoint3d->r/256.0,(GLfloat)pItPoint3d->g/256.0,(GLfloat)pItPoint3d->b/256.0);
			}
			glVertex3f(pItPoint3d->x-prBoxCenter.x, pItPoint3d->y-prBoxCenter.y ,pItPoint3d->z-prBoxCenter.z);
		} 
	} 
}







/***********************************************************************************
打印系数矩阵，只用于调试，不具备运算功能
对于一个N阶拟合，它的系数矩阵大小是（N + 1）行（N + 2）列
double* Para：系数矩阵存储地址
int SizeSrc：系数矩阵大小（SizeSrc）行（SizeSrc + 1）列
***********************************************************************************/
int CKinectCalibrationView::PrintPara(double* Para, int SizeSrc)
{
	int i, j;
	for (i = 0; i < SizeSrc; i++)
	{
		for (j = 0; j <= SizeSrc; j++)
			printf("%10.6lf ", ParaBuffer(Para, i, j));
		printf("\r\n");
	}
	printf("\r\n");
	return 0;
}

int CKinectCalibrationView::ParalimitRow(double* Para, int SizeSrc, int Row)
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
int CKinectCalibrationView::Paralimit(double* Para, int SizeSrc)
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
int CKinectCalibrationView::ParaPreDealA(double* Para, int SizeSrc, int Size)
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
int CKinectCalibrationView::ParaDealA(double* Para, int SizeSrc)
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
int CKinectCalibrationView::ParaPreDealB(double* Para, int SizeSrc, int OffSet)
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
int CKinectCalibrationView::ParaDealB(double* Para, int SizeSrc)
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
int CKinectCalibrationView::ParaDeal(double* Para, int SizeSrc)
{
	//PrintPara(Para, SizeSrc);
	Paralimit(Para, SizeSrc);
	//PrintPara(Para, SizeSrc);
	if (ParaDealA(Para, SizeSrc))
		return -1;
	//PrintPara(Para, SizeSrc);
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
int CKinectCalibrationView::GetParaBuffer(double* Para, const double* X, const double* Y, int Amount, int SizeSrc)
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
int CKinectCalibrationView::CalcAll(const double* BufferX, const double* BufferY, int Amount, int SizeSrc, double* ParaResK)
{
	double* ParaK = (double*)malloc(SizeSrc * (SizeSrc + 1) * sizeof(double));
	GetParaBuffer(ParaK, BufferX, BufferY, Amount, SizeSrc);
	ParaDeal(ParaK, SizeSrc);
	for (Amount = 0; Amount < SizeSrc; Amount++, ParaResK++)
		*ParaResK = ParaBuffer(ParaK, Amount, SizeSrc);
	free(ParaK);
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//按第一行展开计算|A|
float CKinectCalibrationView::getA(float arcs[WEISHU][WEISHU], int n)
{
	if (n == 1)
	{
		return arcs[0][0];
	}
	float ans = 0;
	float temp[WEISHU][WEISHU] = { 0.0 };
	int i, j, k;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n - 1; j++)
		{
			for (k = 0; k < n - 1; k++)
			{
				temp[j][k] = arcs[j + 1][(k >= i) ? k + 1 : k];

			}
		}
		float t = getA(temp, n - 1);
		if (i % 2 == 0)
		{
			ans += arcs[0][i] * t;
		}
		else
		{
			ans -= arcs[0][i] * t;
		}
	}
	return ans;
}

//计算每一行每一列的每个元素所对应的余子式，组成A*
void  CKinectCalibrationView::getAStart(float arcs[WEISHU][WEISHU], int n, float ans[WEISHU][WEISHU])
{
	if (n == 1)
	{
		ans[0][0] = 1;
		return;
	}
	int i, j, k, t;
	float temp[WEISHU][WEISHU];
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			for (k = 0; k < n - 1; k++)
			{
				for (t = 0; t < n - 1; t++)
				{
					temp[k][t] = arcs[k >= i ? k + 1 : k][t >= j ? t + 1 : t];
				}
			}


			ans[j][i] = getA(temp, n - 1);
			if ((i + j) % 2 == 1)
			{
				ans[j][i] = -ans[j][i];
			}
		}
	}
}

//得到给定矩阵src的逆矩阵保存到des中。
bool CKinectCalibrationView::GetMatrixInverse(float src[WEISHU][WEISHU], int n, float des[WEISHU][WEISHU])
{
	float flag = getA(src, n);
	float t[WEISHU][WEISHU];
	if (flag == 0)
	{
		return false;
	}
	else
	{
		getAStart(src, n, t);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				des[i][j] = t[i][j] / flag;
			}

		}
	}
	return true;
}


