// ParamDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "KinectCalibration.h"
#include "ParamDlg.h"
#include "afxdialogex.h"


// CParamDlg 对话框
#include "MainFrm.h"
#include "KinectCalibrationDoc.h"
#include "KinectCalibrationView.h"
IMPLEMENT_DYNAMIC(CParamDlg, CDialogEx)

CParamDlg::CParamDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CParamDlg::IDD, pParent)
	, m_nDegreePerKey(0)
{
	m_nTimes = 1;
	m_strTimer = _T("已保存");
	m_nDegreePerKey = 15;
}

CParamDlg::~CParamDlg()
{
}

void CParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON5, m_btnHideZ0);
	DDX_Control(pDX, IDC_BUTTON6, m_btnHideZ1);
	DDX_Control(pDX, IDC_BUTTON7, m_btnHideA0);
	DDX_Control(pDX, IDC_BUTTON8, m_btnHideA1);
	DDX_Control(pDX, IDC_BUTTON9, m_btnHideB0);
	DDX_Control(pDX, IDC_BUTTON10, m_btnHideB1);
	DDX_Control(pDX, IDC_BUTTON11, m_btnShowZ0);
	DDX_Control(pDX, IDC_BUTTON12, m_btnShowZ1);
	DDX_Control(pDX, IDC_BUTTON13, m_btnShowA0);
	DDX_Control(pDX, IDC_BUTTON14, m_btnShowA1);
	DDX_Control(pDX, IDC_BUTTON15, m_btnShowB0);
	DDX_Control(pDX, IDC_BUTTON16, m_btnShowB1);
	DDX_Text(pDX, IDC_EDIT1, m_nDegreePerKey);
}


BEGIN_MESSAGE_MAP(CParamDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CParamDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SAVE, &CParamDlg::OnBnClickedSave)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SAVE_Z0, &CParamDlg::OnBnClickedSaveZ0)
	ON_BN_CLICKED(IDC_SAVE_Z1, &CParamDlg::OnBnClickedSaveZ1)
	ON_BN_CLICKED(IDC_SAVE_A0, &CParamDlg::OnBnClickedSaveA0)
	ON_BN_CLICKED(IDC_SAVE_A1, &CParamDlg::OnBnClickedSaveA1)
	ON_BN_CLICKED(IDC_SAVE_B0, &CParamDlg::OnBnClickedSaveB0)
	ON_BN_CLICKED(IDC_SAVE_B1, &CParamDlg::OnBnClickedSaveB1)
	//////////////////////////////////////////////////////////////////////////A0
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_DX, &CParamDlg::OnDeltaposSpinDx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_DY, &CParamDlg::OnDeltaposSpinDy)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_DZ, &CParamDlg::OnDeltaposSpinDz)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LX, &CParamDlg::OnDeltaposSpinLx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LY, &CParamDlg::OnDeltaposSpinLy)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LZ, &CParamDlg::OnDeltaposSpinLz)
	//////////////////////////////////////////////////////////////////////////B0
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_DX2, &CParamDlg::OnDeltaposSpinDx2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_DY2, &CParamDlg::OnDeltaposSpinDy2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_DZ2, &CParamDlg::OnDeltaposSpinDz2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LX2, &CParamDlg::OnDeltaposSpinLx2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LY2, &CParamDlg::OnDeltaposSpinLy2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LZ2, &CParamDlg::OnDeltaposSpinLz2)
	//////////////////////////////////////////////////////////////////////////Z0
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_DX3, &CParamDlg::OnDeltaposSpinDx3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_DY3, &CParamDlg::OnDeltaposSpinDy3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_DZ3, &CParamDlg::OnDeltaposSpinDz3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LX3, &CParamDlg::OnDeltaposSpinLx3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LY3, &CParamDlg::OnDeltaposSpinLy3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LZ3, &CParamDlg::OnDeltaposSpinLz3)
	//////////////////////////////////////////////////////////////////////////A1
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_DX4, &CParamDlg::OnDeltaposSpinDx4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_DY4, &CParamDlg::OnDeltaposSpinDy4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_DZ4, &CParamDlg::OnDeltaposSpinDz4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LX4, &CParamDlg::OnDeltaposSpinLx4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LY4, &CParamDlg::OnDeltaposSpinLy4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LZ4, &CParamDlg::OnDeltaposSpinLz4)
	//////////////////////////////////////////////////////////////////////////B1
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_DX5, &CParamDlg::OnDeltaposSpinDx5)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_DY5, &CParamDlg::OnDeltaposSpinDy5)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_DZ5, &CParamDlg::OnDeltaposSpinDz5)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LX5, &CParamDlg::OnDeltaposSpinLx5)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LY5, &CParamDlg::OnDeltaposSpinLy5)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LZ5, &CParamDlg::OnDeltaposSpinLz5)
	//////////////////////////////////////////////////////////////////////////Z1
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_DX6, &CParamDlg::OnDeltaposSpinDx6)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_DY6, &CParamDlg::OnDeltaposSpinDy6)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_DZ6, &CParamDlg::OnDeltaposSpinDz6)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LX6, &CParamDlg::OnDeltaposSpinLx6)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LY6, &CParamDlg::OnDeltaposSpinLy6)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LZ6, &CParamDlg::OnDeltaposSpinLz6)
	ON_BN_CLICKED(IDC_BUTTON5, &CParamDlg::OnHideZ0)
	ON_BN_CLICKED(IDC_BUTTON6, &CParamDlg::OnHideZ1)
	ON_BN_CLICKED(IDC_BUTTON7, &CParamDlg::OnHideA0)
	ON_BN_CLICKED(IDC_BUTTON8, &CParamDlg::OnHideA1)
	ON_BN_CLICKED(IDC_BUTTON9, &CParamDlg::OnHideB0)
	ON_BN_CLICKED(IDC_BUTTON10, &CParamDlg::OnHideB1)
	ON_BN_CLICKED(IDC_BUTTON12, &CParamDlg::OnShowZ1)
	ON_BN_CLICKED(IDC_BUTTON11, &CParamDlg::OnShowZ0)
	ON_BN_CLICKED(IDC_BUTTON13, &CParamDlg::OnShowA0)
	ON_BN_CLICKED(IDC_BUTTON14, &CParamDlg::OnShowA1)
	ON_BN_CLICKED(IDC_BUTTON15, &CParamDlg::OnShowB0)
	ON_BN_CLICKED(IDC_BUTTON16, &CParamDlg::OnShowB1)
END_MESSAGE_MAP()


// CParamDlg 消息处理程序


void CParamDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}


BOOL CParamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_pFrm = (CMainFrame*)AfxGetMainWnd();
	m_pView = (CKinectCalibrationView *)m_pFrm->GetActiveView();

	m_btnShowZ0.EnableWindow(FALSE);
	m_btnShowZ1.EnableWindow(FALSE);
	m_btnShowA0.EnableWindow(FALSE);
	m_btnShowA1.EnableWindow(FALSE);
	m_btnShowB0.EnableWindow(FALSE);
	m_btnShowB1.EnableWindow(FALSE);

	CString sPathRoot,sPath,str;
	GetModuleFileName(NULL,sPathRoot.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	int pos = sPathRoot.ReverseFind('\\');
	sPathRoot = sPathRoot.Left(pos);

	sPath=sPathRoot+_T("\\初始文件\\sys.txt");
	float z0[5][3];
	float a0[5][3];
	float b0[5][3];
	float z1[5][3];
	float a1[5][3];
	float b1[5][3];
	memset(z0,0,sizeof(float)*15);
	memset(a0,0,sizeof(float)*15);
	memset(b0,0,sizeof(float)*15);
	memset(z1,0,sizeof(float)*15);
	memset(a1,0,sizeof(float)*15);
	memset(b1,0,sizeof(float)*15);
	FILE *fp;
	USES_CONVERSION;
	fp=fopen(W2A(sPath),"r");
	char ch=fgetc(fp);
	if(ch==EOF);
	else
	{
		fseek(fp,0,SEEK_SET);
		fscanf(fp,"%f%f%f",&z0[0][0],&z0[0][1],&z0[0][2]);
		fscanf(fp,"%f%f%f",&z0[1][0],&z0[1][1],&z0[1][2]);
		fscanf(fp,"%f%f%f",&z0[2][0],&z0[2][1],&z0[2][2]);
		fscanf(fp,"%f%f%f",&z0[3][0],&z0[3][1],&z0[3][2]);
		fscanf(fp,"%f%f%f",&z0[4][0],&z0[4][1],&z0[4][2]); 

		fscanf(fp,"%f%f%f",&a0[0][0],&a0[0][1],&a0[0][2]);
		fscanf(fp,"%f%f%f",&a0[1][0],&a0[1][1],&a0[1][2]);
		fscanf(fp,"%f%f%f",&a0[2][0],&a0[2][1],&a0[2][2]);
		fscanf(fp,"%f%f%f",&a0[3][0],&a0[3][1],&a0[3][2]);
		fscanf(fp,"%f%f%f",&a0[4][0],&a0[4][1],&a0[4][2]); 

		fscanf(fp,"%f%f%f",&b0[0][0],&b0[0][1],&b0[0][2]);
		fscanf(fp,"%f%f%f",&b0[1][0],&b0[1][1],&b0[1][2]);
		fscanf(fp,"%f%f%f",&b0[2][0],&b0[2][1],&b0[2][2]);
		fscanf(fp,"%f%f%f",&b0[3][0],&b0[3][1],&b0[3][2]);
		fscanf(fp,"%f%f%f",&b0[4][0],&b0[4][1],&b0[4][2]); 

		fscanf(fp,"%f%f%f",&z1[0][0],&z1[0][1],&z1[0][2]);
		fscanf(fp,"%f%f%f",&z1[1][0],&z1[1][1],&z1[1][2]);
		fscanf(fp,"%f%f%f",&z1[2][0],&z1[2][1],&z1[2][2]);
		fscanf(fp,"%f%f%f",&z1[3][0],&z1[3][1],&z1[3][2]);
		fscanf(fp,"%f%f%f",&z1[4][0],&z1[4][1],&z1[4][2]); 

		fscanf(fp,"%f%f%f",&a1[0][0],&a1[0][1],&a1[0][2]);
		fscanf(fp,"%f%f%f",&a1[1][0],&a1[1][1],&a1[1][2]);
		fscanf(fp,"%f%f%f",&a1[2][0],&a1[2][1],&a1[2][2]);
		fscanf(fp,"%f%f%f",&a1[3][0],&a1[3][1],&a1[3][2]);
		fscanf(fp,"%f%f%f",&a1[4][0],&a1[4][1],&a1[4][2]); 

		fscanf(fp,"%f%f%f",&b1[0][0],&b1[0][1],&b1[0][2]);
		fscanf(fp,"%f%f%f",&b1[1][0],&b1[1][1],&b1[1][2]);
		fscanf(fp,"%f%f%f",&b1[2][0],&b1[2][1],&b1[2][2]);
		fscanf(fp,"%f%f%f",&b1[3][0],&b1[3][1],&b1[3][2]);
		fscanf(fp,"%f%f%f",&b1[4][0],&b1[4][1],&b1[4][2]); 
	}

	fclose(fp);
	fp=NULL;
	str.Format(_T("%.1f"),a0[3][0]);
	GetDlgItem(IDC_EDIT_X)->SetWindowText(str);

	str.Format(_T("%.1f"),a0[3][1]);
	GetDlgItem(IDC_EDIT_Y)->SetWindowText(str);

	str.Format(_T("%.1f"),a0[3][2]);
	GetDlgItem(IDC_EDIT_Z)->SetWindowText(str);

	str.Format(_T("%.1f"),a0[4][0]);
	GetDlgItem(IDC_EDIT_DX)->SetWindowText(str);

	str.Format(_T("%.1f"),a0[4][1]);
	GetDlgItem(IDC_EDIT_DY)->SetWindowText(str);

	str.Format(_T("%.1f"),a0[4][2]);
	GetDlgItem(IDC_EDIT_DZ)->SetWindowText(str);

	//第二个
	str.Format(_T("%.1f"),b0[3][0]);
	GetDlgItem(IDC_EDIT_X2)->SetWindowText(str);

	str.Format(_T("%.1f"),b0[3][1]);
	GetDlgItem(IDC_EDIT_Y2)->SetWindowText(str);

	str.Format(_T("%.1f"),b0[3][2]);
	GetDlgItem(IDC_EDIT_Z2)->SetWindowText(str);

	str.Format(_T("%.1f"),b0[4][0]);
	GetDlgItem(IDC_EDIT_DX2)->SetWindowText(str);

	str.Format(_T("%.1f"),b0[4][1]);
	GetDlgItem(IDC_EDIT_DY2)->SetWindowText(str);

	str.Format(_T("%.1f"),b0[4][2]);
	GetDlgItem(IDC_EDIT_DZ2)->SetWindowText(str);

	//第3个
	str.Format(_T("%.1f"),z0[3][0]);
	GetDlgItem(IDC_EDIT_X3)->SetWindowText(str);

	str.Format(_T("%.1f"),z0[3][1]);
	GetDlgItem(IDC_EDIT_Y3)->SetWindowText(str);

	str.Format(_T("%.1f"),z0[3][2]);
	GetDlgItem(IDC_EDIT_Z3)->SetWindowText(str);

	str.Format(_T("%.1f"),z0[4][0]);
	GetDlgItem(IDC_EDIT_DX3)->SetWindowText(str);

	str.Format(_T("%.1f"),z0[4][1]);
	GetDlgItem(IDC_EDIT_DY3)->SetWindowText(str);

	str.Format(_T("%.1f"),z0[4][2]);
	GetDlgItem(IDC_EDIT_DZ3)->SetWindowText(str);

	//第4个
	str.Format(_T("%.1f"),a1[3][0]);
	GetDlgItem(IDC_EDIT_X4)->SetWindowText(str);

	str.Format(_T("%.1f"),a1[3][1]);
	GetDlgItem(IDC_EDIT_Y4)->SetWindowText(str);

	str.Format(_T("%.1f"),a1[3][2]);
	GetDlgItem(IDC_EDIT_Z4)->SetWindowText(str);

	str.Format(_T("%.1f"),a1[4][0]);
	GetDlgItem(IDC_EDIT_DX4)->SetWindowText(str);

	str.Format(_T("%.1f"),a1[4][1]);
	GetDlgItem(IDC_EDIT_DY4)->SetWindowText(str);

	str.Format(_T("%.1f"),a1[4][2]);
	GetDlgItem(IDC_EDIT_DZ4)->SetWindowText(str);

	//第5个
	str.Format(_T("%.1f"),b1[3][0]);
	GetDlgItem(IDC_EDIT_X5)->SetWindowText(str);

	str.Format(_T("%.1f"),b1[3][1]);
	GetDlgItem(IDC_EDIT_Y5)->SetWindowText(str);

	str.Format(_T("%.1f"),b1[3][2]);
	GetDlgItem(IDC_EDIT_Z5)->SetWindowText(str);

	str.Format(_T("%.1f"),b1[4][0]);
	GetDlgItem(IDC_EDIT_DX5)->SetWindowText(str);

	str.Format(_T("%.1f"),b1[4][1]);
	GetDlgItem(IDC_EDIT_DY5)->SetWindowText(str);

	str.Format(_T("%.1f"),b1[4][2]);
	GetDlgItem(IDC_EDIT_DZ5)->SetWindowText(str);

	//第6个
	str.Format(_T("%.1f"),z1[3][0]);
	GetDlgItem(IDC_EDIT_X6)->SetWindowText(str);

	str.Format(_T("%.1f"),z1[3][1]);
	GetDlgItem(IDC_EDIT_Y6)->SetWindowText(str);

	str.Format(_T("%.1f"),z1[3][2]);
	GetDlgItem(IDC_EDIT_Z6)->SetWindowText(str);

	str.Format(_T("%.1f"),z1[4][0]);
	GetDlgItem(IDC_EDIT_DX6)->SetWindowText(str);

	str.Format(_T("%.1f"),z1[4][1]);
	GetDlgItem(IDC_EDIT_DY6)->SetWindowText(str);

	str.Format(_T("%.1f"),z1[4][2]);
	GetDlgItem(IDC_EDIT_DZ6)->SetWindowText(str);

	/*m_deltaAngle = m_pView->m_deltaAngle;
	str.Format(_T("%.2f"),m_deltaAngle);
	GetDlgItem(IDC_DELTA_ANGLE)->SetWindowText(str);

	m_deltaTranslation = m_pView->m_deltaTranslation;
	str.Format(_T("%.2f"),m_deltaTranslation);
	GetDlgItem(IDC_DELTA_TRANSLATION)->SetWindowText(str);*/

	//保存那两个单位参数
	CString infoPath=sPathRoot+_T("\\初始文件\\info.ini");
	GetPrivateProfileString(_T("sys"),_T("delta_Angle"),_T(""),str.GetBuffer(200),200,infoPath);
	GetDlgItem(IDC_DELTA_ANGLE)->SetWindowText(str);
	m_deltaAngle = _wtof(str);

	GetPrivateProfileString(_T("sys"),_T("delta_Translation"),_T(""),str.GetBuffer(200),200,infoPath);
	GetDlgItem(IDC_DELTA_TRANSLATION)->SetWindowText(str);
	m_deltaTranslation = _wtof(str);

	sPathRoot.ReleaseBuffer();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CParamDlg::SaveParam()
{
	CString sPathRoot,sPath,str;
	GetModuleFileName(NULL,sPathRoot.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	//sPathRoot.ReleaseBuffer();
	int pos = sPathRoot.ReverseFind('\\');
	sPathRoot = sPathRoot.Left(pos);

	sPath=sPathRoot+_T("\\初始文件\\sys.txt");
	//GetPrivateProfileString(_T("sys"),_T("name"),_T(""),m_sName.GetBuffer(200),200,sPath);
	//m_sName.ReleaseBuffer();
	//m_sName.Trim();

	FILE *fp=NULL;
	USES_CONVERSION;
	fp=fopen(W2A(sPath),"w+");		//创建文件  

	//Z0
	GetDlgItem(IDC_EDIT_DX3)->GetWindowText(str);
	double degreex3=_ttof(str);
	double degreeX3=degreex3*PI/180;
	GetDlgItem(IDC_EDIT_DY3)->GetWindowText(str);
	double degreey3=_ttof(str);
	double degreeY3=degreey3*PI/180;
	GetDlgItem(IDC_EDIT_DZ3)->GetWindowText(str);
	double degreez3=_ttof(str);
	double degreeZ3=degreez3*PI/180;

	double z0[4][3];      //旋转矩阵
	z0[0][0]=cos(degreeY3)*cos(degreeZ3);
	z0[0][1]=cos(degreeY3)*sin(degreeZ3);
	z0[0][2]=-sin(degreeY3);

	z0[1][0]=-cos(degreeX3)*sin(degreeZ3)+sin(degreeX3)*sin(degreeY3)*cos(degreeZ3);
	z0[1][1]=cos(degreeX3)*cos(degreeZ3)+sin(degreeX3)*sin(degreeY3)*sin(degreeZ3);
	z0[1][2]=sin(degreeX3)*cos(degreeY3);

	z0[2][0]=sin(degreeX3)*sin(degreeZ3)+cos(degreeX3)*sin(degreeY3)*cos(degreeZ3);
	z0[2][1]=-sin(degreeX3)*cos(degreeZ3)+cos(degreeX3)*sin(degreeY3)*sin(degreeZ3);
	z0[2][2]=cos(degreeX3)*cos(degreeY3);

	//平移矩阵
	GetDlgItem(IDC_EDIT_X3)->GetWindowText(str);
	z0[3][0]=_ttof(str);
	GetDlgItem(IDC_EDIT_Y3)->GetWindowText(str);
	z0[3][1]=_ttof(str);
	GetDlgItem(IDC_EDIT_Z3)->GetWindowText(str);
	z0[3][2]=_ttof(str);

	fprintf(fp, "%f %f %f \n%f %f %f \n%f %f %f \n%f %f %f \n%f %f %f\n\n",
		z0[0][0],z0[0][1],z0[0][2],z0[1][0],z0[1][1],z0[1][2],z0[2][0],z0[2][1],z0[2][2],z0[3][0],z0[3][1],z0[3][2],degreex3,degreey3,degreez3);

	//第2个 a0  
	GetDlgItem(IDC_EDIT_DX)->GetWindowText(str);
	double degreex=_ttof(str);
	double degreeX=degreex*PI/180;
	GetDlgItem(IDC_EDIT_DY)->GetWindowText(str);
	double degreey=_ttof(str);
	double degreeY=degreey*PI/180;
	GetDlgItem(IDC_EDIT_DZ)->GetWindowText(str);
	double degreez=_ttof(str);
	double degreeZ=degreez*PI/180;

	double a0[4][3];      //旋转矩阵
	a0[0][0]=cos(degreeY)*cos(degreeZ);
	a0[0][1]=cos(degreeY)*sin(degreeZ);
	a0[0][2]=-sin(degreeY);

	//z0[1][0] = -cos(degreeX3)*sin(degreeZ3) + sin(degreeX3)*sin(degreeY3)*cos(degreeZ3);
	//z0[1][1] = cos(degreeX3)*cos(degreeZ3) + sin(degreeX3)*sin(degreeY3)*sin(degreeZ3);
	//z0[1][2] = sin(degreeX3)*cos(degreeY3);

	//z0[2][0] = sin(degreeX3)*sin(degreeZ3) + cos(degreeX3)*sin(degreeY3)*cos(degreeZ3);
	//z0[2][1] = -sin(degreeX3)*cos(degreeZ3) + cos(degreeX3)*sin(degreeY3)*sin(degreeZ3);
	//z0[2][2] = cos(degreeX3)*cos(degreeY3);

	a0[1][0]=-cos(degreeX)*sin(degreeZ)+sin(degreeX)*sin(degreeY)*cos(degreeZ);
	a0[1][1]=cos(degreeX)*cos(degreeZ)+sin(degreeX)*sin(degreeY)*sin(degreeZ);
	a0[1][2]=sin(degreeX)*cos(degreeY);

	a0[2][0]=sin(degreeX)*sin(degreeZ)+cos(degreeX)*sin(degreeY)*cos(degreeZ);
	a0[2][1]=-sin(degreeX)*cos(degreeZ)+cos(degreeX)*sin(degreeY)*sin(degreeZ);
	a0[2][2]=cos(degreeX)*cos(degreeY);

	//平移矩阵
	GetDlgItem(IDC_EDIT_X)->GetWindowText(str);
	a0[3][0]=_ttof(str);
	GetDlgItem(IDC_EDIT_Y)->GetWindowText(str);
	a0[3][1]=_ttof(str);
	GetDlgItem(IDC_EDIT_Z)->GetWindowText(str);
	a0[3][2]=_ttof(str);

	fprintf(fp, "%f %f %f \n%f %f %f \n%f %f %f \n%f %f %f \n%f %f %f\n\n",
		a0[0][0],a0[0][1],a0[0][2],a0[1][0],a0[1][1],a0[1][2],a0[2][0],a0[2][1],a0[2][2],a0[3][0],a0[3][1],a0[3][2],degreex,degreey,degreez);

	//第3个 b0
	GetDlgItem(IDC_EDIT_DX2)->GetWindowText(str);
	double degreex2=_ttof(str);
	double degreeX2=degreex2*PI/180;
	GetDlgItem(IDC_EDIT_DY2)->GetWindowText(str);
	double degreey2=_ttof(str);
	double degreeY2=degreey2*PI/180;
	GetDlgItem(IDC_EDIT_DZ2)->GetWindowText(str);
	double degreez2=_ttof(str);
	double degreeZ2=degreez2*PI/180;

	double b0[4][3];      //旋转矩阵
	b0[0][0]=cos(degreeY2)*cos(degreeZ2);
	b0[0][1]=cos(degreeY2)*sin(degreeZ2);
	b0[0][2]=-sin(degreeY2);

	b0[1][0]=-cos(degreeX2)*sin(degreeZ2)+sin(degreeX2)*sin(degreeY2)*cos(degreeZ2);
	b0[1][1]=cos(degreeX2)*cos(degreeZ2)+sin(degreeX2)*sin(degreeY2)*sin(degreeZ2);
	b0[1][2]=sin(degreeX2)*cos(degreeY2);

	b0[2][0]=sin(degreeX2)*sin(degreeZ2)+cos(degreeX2)*sin(degreeY2)*cos(degreeZ2);
	b0[2][1]=-sin(degreeX2)*cos(degreeZ2)+cos(degreeX2)*sin(degreeY2)*sin(degreeZ2);
	b0[2][2]=cos(degreeX2)*cos(degreeY2);

	//平移矩阵
	GetDlgItem(IDC_EDIT_X2)->GetWindowText(str);
	b0[3][0]=_ttof(str);
	GetDlgItem(IDC_EDIT_Y2)->GetWindowText(str);
	b0[3][1]=_ttof(str);
	GetDlgItem(IDC_EDIT_Z2)->GetWindowText(str);
	b0[3][2]=_ttof(str);

	fprintf(fp, "%f %f %f \n%f %f %f \n%f %f %f \n%f %f %f \n%f %f %f\n\n",
		b0[0][0],b0[0][1],b0[0][2],b0[1][0],b0[1][1],b0[1][2],b0[2][0],b0[2][1],b0[2][2],b0[3][0],b0[3][1],b0[3][2],degreex2,degreey2,degreez2);


	//z1
	GetDlgItem(IDC_EDIT_DX6)->GetWindowText(str);
	double degreex6=_ttof(str);
	double degreeX6=degreex6*PI/180;

	GetDlgItem(IDC_EDIT_DY6)->GetWindowText(str);
	double degreey6=_ttof(str);
	double degreeY6=degreey6*PI/180;

	GetDlgItem(IDC_EDIT_DZ6)->GetWindowText(str);
	double degreez6=_ttof(str);
	double degreeZ6=degreez6*PI/180;

	double z1[4][3];      //旋转矩阵
	z1[0][0]=cos(degreeY6)*cos(degreeZ6);
	z1[0][1]=cos(degreeY6)*sin(degreeZ6);
	z1[0][2]=-sin(degreeY6);

	z1[1][0]=-cos(degreeX6)*sin(degreeZ6)+sin(degreeX6)*sin(degreeY6)*cos(degreeZ6);
	z1[1][1]=cos(degreeX6)*cos(degreeZ6)+sin(degreeX6)*sin(degreeY6)*sin(degreeZ6);
	z1[1][2]=sin(degreeX6)*cos(degreeY6);

	z1[2][0]=sin(degreeX6)*sin(degreeZ6)+cos(degreeX6)*sin(degreeY6)*cos(degreeZ6);
	z1[2][1]=-sin(degreeX6)*cos(degreeZ6)+cos(degreeX6)*sin(degreeY6)*sin(degreeZ6);
	z1[2][2]=cos(degreeX6)*cos(degreeY6);

	//平移矩阵
	GetDlgItem(IDC_EDIT_X6)->GetWindowText(str);
	z1[3][0]=_ttof(str);
	GetDlgItem(IDC_EDIT_Y6)->GetWindowText(str);
	z1[3][1]=_ttof(str);
	GetDlgItem(IDC_EDIT_Z6)->GetWindowText(str);
	z1[3][2]=_ttof(str);

	fprintf(fp, "%f %f %f \n%f %f %f \n%f %f %f \n%f %f %f \n%f %f %f\n\n",
		z1[0][0],z1[0][1],z1[0][2],z1[1][0],z1[1][1],z1[1][2],z1[2][0],z1[2][1],z1[2][2],z1[3][0],z1[3][1],z1[3][2],degreex6,degreey6,degreez6);

	//第5个 a1
	GetDlgItem(IDC_EDIT_DX4)->GetWindowText(str);
	double degreex4=_ttof(str);
	double degreeX4=degreex4*PI/180;

	GetDlgItem(IDC_EDIT_DY4)->GetWindowText(str);
	double degreey4=_ttof(str);
	double degreeY4=degreey4*PI/180;

	GetDlgItem(IDC_EDIT_DZ4)->GetWindowText(str);
	double degreez4=_ttof(str);
	double degreeZ4=degreez4*PI/180;

	double a1[4][3];      //旋转矩阵
	a1[0][0]=cos(degreeY4)*cos(degreeZ4);
	a1[0][1]=cos(degreeY4)*sin(degreeZ4);
	a1[0][2]=-sin(degreeY4);

	a1[1][0]=-cos(degreeX4)*sin(degreeZ4)+sin(degreeX4)*sin(degreeY4)*cos(degreeZ4);
	a1[1][1]=cos(degreeX4)*cos(degreeZ4)+sin(degreeX4)*sin(degreeY4)*sin(degreeZ4);
	a1[1][2]=sin(degreeX4)*cos(degreeY4);

	a1[2][0]=sin(degreeX4)*sin(degreeZ4)+cos(degreeX4)*sin(degreeY4)*cos(degreeZ4);
	a1[2][1]=-sin(degreeX4)*cos(degreeZ4)+cos(degreeX4)*sin(degreeY4)*sin(degreeZ4);
	a1[2][2]=cos(degreeX4)*cos(degreeY4);

	//平移矩阵
	GetDlgItem(IDC_EDIT_X4)->GetWindowText(str);
	a1[3][0]=_ttof(str);
	GetDlgItem(IDC_EDIT_Y4)->GetWindowText(str);
	a1[3][1]=_ttof(str);
	GetDlgItem(IDC_EDIT_Z4)->GetWindowText(str);
	a1[3][2]=_ttof(str);

	fprintf(fp, "%f %f %f \n%f %f %f \n%f %f %f \n%f %f %f \n%f %f %f\n\n",
		a1[0][0],a1[0][1],a1[0][2],a1[1][0],a1[1][1],a1[1][2],a1[2][0],a1[2][1],a1[2][2],a1[3][0],a1[3][1],a1[3][2],degreex4,degreey4,degreez4);

	//第6个 b1
	GetDlgItem(IDC_EDIT_DX5)->GetWindowText(str);
	double degreex5=_ttof(str);
	double degreeX5=degreex5*PI/180;

	GetDlgItem(IDC_EDIT_DY5)->GetWindowText(str);
	double degreey5=_ttof(str);
	double degreeY5=degreey5*PI/180;

	GetDlgItem(IDC_EDIT_DZ5)->GetWindowText(str);
	double degreez5=_ttof(str);
	double degreeZ5=degreez5*PI/180;

	double b1[4][3];      //旋转矩阵
	b1[0][0]=cos(degreeY5)*cos(degreeZ5);
	b1[0][1]=cos(degreeY5)*sin(degreeZ5);
	b1[0][2]=-sin(degreeY5);

	b1[1][0]=-cos(degreeX5)*sin(degreeZ5)+sin(degreeX5)*sin(degreeY5)*cos(degreeZ5);
	b1[1][1]=cos(degreeX5)*cos(degreeZ5)+sin(degreeX5)*sin(degreeY5)*sin(degreeZ5);
	b1[1][2]=sin(degreeX5)*cos(degreeY5);

	b1[2][0]=sin(degreeX5)*sin(degreeZ5)+cos(degreeX5)*sin(degreeY5)*cos(degreeZ5);
	b1[2][1]=-sin(degreeX5)*cos(degreeZ5)+cos(degreeX5)*sin(degreeY5)*sin(degreeZ5);
	b1[2][2]=cos(degreeX5)*cos(degreeY5);

	//平移矩阵
	GetDlgItem(IDC_EDIT_X5)->GetWindowText(str);
	b1[3][0]=_ttof(str);
	GetDlgItem(IDC_EDIT_Y5)->GetWindowText(str);
	b1[3][1]=_ttof(str);
	GetDlgItem(IDC_EDIT_Z5)->GetWindowText(str);
	b1[3][2]=_ttof(str);

	fprintf(fp, "%f %f %f \n%f %f %f \n%f %f %f \n%f %f %f \n%f %f %f\n\n",
		b1[0][0],b1[0][1],b1[0][2],b1[1][0],b1[1][1],b1[1][2],b1[2][0],b1[2][1],b1[2][2],b1[3][0],b1[3][1],b1[3][2],degreex5,degreey5,degreez5);

	fclose(fp);
	fp=NULL;

	//保存那两个单位参数
	CString infoPath=sPathRoot+_T("\\初始文件\\info.ini");
	GetDlgItem(IDC_DELTA_ANGLE)->GetWindowText(str);
	m_deltaAngle = _wtof(str);
	WritePrivateProfileString(_T("sys"),_T("delta_Angle"),str,infoPath);

	GetDlgItem(IDC_DELTA_TRANSLATION)->GetWindowText(str);
	m_deltaTranslation = _wtof(str);
	WritePrivateProfileString(_T("sys"),_T("delta_Translation"),str,infoPath);

	sPathRoot.ReleaseBuffer();
}

void CParamDlg::OnBnClickedSave()
{
	UpdateData(TRUE);
	m_pView->m_fDeltaDegree = (float)m_nDegreePerKey;
	SaveParam();
	m_strTimer = _T("全部参数已保存");
	SetTimer(1,20,NULL);
}

void CParamDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==1)
	{
		CString str;
		for(int i=0;i<m_nTimes;i++)
		{
			str += _T(".");
		}
		if(m_nTimes==10)
		{
			m_nTimes = 1;
			str += m_strTimer;
			KillTimer(1);
		}
		m_nTimes++;
		GetDlgItem(IDC_STATIC_TIP)->SetWindowTextW(str);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CParamDlg::OnBnClickedSaveZ0()
{
	//UpdateData(TRUE);
	SaveParam();
	/*CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
	CKinectCalibrationView *pView = (CKinectCalibrationView *)p->GetActiveView();*/
	//CKinectCalibrationView* pView = (CKinectCalibrationView*)GetParent();
	m_pView->ReadSysInfo();
	m_strTimer = _T("Z0已保存");
	SetTimer(1,20,NULL);
	m_pView->ChangeMatrix(_T("Z0"));
}


void CParamDlg::OnBnClickedSaveZ1()
{
	SaveParam();
	m_pView->ReadSysInfo();
	m_strTimer = _T("Z1已保存");
	SetTimer(1,20,NULL);
	m_pView->ChangeMatrix(_T("Z1"));
}


void CParamDlg::OnBnClickedSaveA0()
{
	//UpdateData(TRUE);
	SaveParam();
	/*CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
	CKinectCalibrationView *pView = (CKinectCalibrationView *)p->GetActiveView();*/
	m_pView->ReadSysInfo();
	m_strTimer = _T("A0已保存");
	SetTimer(1,20,NULL);
	m_pView->ChangeMatrix(_T("A0"));
}


void CParamDlg::OnBnClickedSaveA1()
{
	//UpdateData(TRUE);
	SaveParam();
	/*CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
	CKinectCalibrationView *pView = (CKinectCalibrationView *)p->GetActiveView();*/
	m_pView->ReadSysInfo();
	m_strTimer = _T("A1已保存");
	SetTimer(1,20,NULL);
	m_pView->ChangeMatrix(_T("A1"));
}


void CParamDlg::OnBnClickedSaveB0()
{
	//UpdateData(TRUE);
	SaveParam();
	/*CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
	CKinectCalibrationView *pView = (CKinectCalibrationView *)p->GetActiveView();*/
	m_pView->ReadSysInfo();
	m_strTimer = _T("B0已保存");
	SetTimer(1,20,NULL);
	m_pView->ChangeMatrix(_T("B0"));
}


void CParamDlg::OnBnClickedSaveB1()
{
	//UpdateData(TRUE);
	SaveParam();
	m_pView->ReadSysInfo();
	m_strTimer = _T("B1已保存");
	SetTimer(1,20,NULL);
	m_pView->ChangeMatrix(_T("B1"));
}


BOOL CParamDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->wParam==VK_RETURN)
	{
		OnBnClickedSave();
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CParamDlg::OnDeltaposSpinDx(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_DX)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaAngle);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_DX)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveA0();
}


void CParamDlg::OnDeltaposSpinDy(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_DY)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaAngle);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_DY)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveA0();
}


void CParamDlg::OnDeltaposSpinDz(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_DZ)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaAngle);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_DZ)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveA0();
}


void CParamDlg::OnDeltaposSpinLx(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_X)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaTranslation);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_X)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveA0();
}


void CParamDlg::OnDeltaposSpinLy(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_Y)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaTranslation);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_Y)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveA0();
}


void CParamDlg::OnDeltaposSpinLz(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_Z)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaTranslation);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_Z)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveA0();
}

void CParamDlg::OnDeltaposSpinDx2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_DX2)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaAngle);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_DX2)->SetWindowText(str);

	*pResult = 0;
	OnBnClickedSaveB0();
}


void CParamDlg::OnDeltaposSpinDy2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_DY2)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaAngle);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_DY2)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveB0();
}


void CParamDlg::OnDeltaposSpinDz2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_DZ2)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaAngle);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_DZ2)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveB0();
}


void CParamDlg::OnDeltaposSpinLx2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_X2)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaTranslation);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_X2)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveB0();
}


void CParamDlg::OnDeltaposSpinLy2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_Y2)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaTranslation);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_Y2)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveB0();
}


void CParamDlg::OnDeltaposSpinLz2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_Z2)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaTranslation);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_Z2)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveB0();
}


void CParamDlg::OnDeltaposSpinDx3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_DX3)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaAngle);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_DX3)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveZ0();
}


void CParamDlg::OnDeltaposSpinDy3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_DY3)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaAngle);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_DY3)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveZ0();
}


void CParamDlg::OnDeltaposSpinDz3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_DZ3)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaAngle);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_DZ3)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveZ0();
}


void CParamDlg::OnDeltaposSpinLx3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_X3)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaTranslation);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_X3)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveZ0();
}


void CParamDlg::OnDeltaposSpinLy3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_Y3)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaTranslation);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_Y3)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveZ0();
}


void CParamDlg::OnDeltaposSpinLz3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_Z3)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaTranslation);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_Z3)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveZ0();
}

void CParamDlg::OnDeltaposSpinDx4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_DX4)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaAngle);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_DX4)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveA1();
}


void CParamDlg::OnDeltaposSpinDy4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_DY4)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaAngle);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_DY4)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveA1();
}


void CParamDlg::OnDeltaposSpinDz4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_DZ4)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaAngle);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_DZ4)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveA1();
}

void CParamDlg::OnDeltaposSpinLx4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_X4)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaTranslation);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_X4)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveA1();
}


void CParamDlg::OnDeltaposSpinLy4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_Y4)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaTranslation);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_Y4)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveA1();
}


void CParamDlg::OnDeltaposSpinLz4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_Z4)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaTranslation);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_Z4)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveA1();
}

void CParamDlg::OnDeltaposSpinDx5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_DX5)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaAngle);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_DX5)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveB1();
}


void CParamDlg::OnDeltaposSpinDy5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_DY5)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaAngle);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_DY5)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveB1();
}


void CParamDlg::OnDeltaposSpinDz5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_DZ5)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaAngle);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_DZ5)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveB1();
}
void CParamDlg::OnDeltaposSpinLx5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_X5)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaTranslation);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_X5)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveB1();
}


void CParamDlg::OnDeltaposSpinLy5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_Y5)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaTranslation);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_Y5)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveB1();
}


void CParamDlg::OnDeltaposSpinLz5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_Z5)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaTranslation);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_Z5)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveB1();
}

void CParamDlg::OnDeltaposSpinDx6(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_DX6)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaAngle);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_DX6)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveZ1();
}


void CParamDlg::OnDeltaposSpinDy6(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_DY6)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaAngle);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_DY6)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveZ1();
}


void CParamDlg::OnDeltaposSpinDz6(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_DZ6)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaAngle);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_DZ6)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveZ1();
}
void CParamDlg::OnDeltaposSpinLx6(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_X6)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaTranslation);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_X6)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveZ1();
}


void CParamDlg::OnDeltaposSpinLy6(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_Y6)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaTranslation);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_Y6)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveZ1();
}


void CParamDlg::OnDeltaposSpinLz6(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString str;
	double a;
	GetDlgItem(IDC_EDIT_Z6)->GetWindowText(str);
	a=_ttof(str);
	a+=pNMUpDown->iDelta*(-m_deltaTranslation);
	str.Format(_T("%.1f"),a);
	GetDlgItem(IDC_EDIT_Z6)->SetWindowText(str);
	*pResult = 0;
	OnBnClickedSaveZ1();
}


void CParamDlg::OnHideZ0()
{
	m_pView->m_bShowZ0 = FALSE;
	m_btnHideZ0.EnableWindow(FALSE);
	m_btnShowZ0.EnableWindow(TRUE);
	//m_pView->InvalidateRect(NULL,FALSE); 	
	GetDlgItem(IDC_SPIN_DX3)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_DY3)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_DZ3)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_LX3)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_LY3)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_LZ3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DX3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DY3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DZ3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_X3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Y3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Z3)->EnableWindow(FALSE);
	m_pView->InvalidateRect(NULL,FALSE);
}

void CParamDlg::OnHideZ1()
{
	m_pView->m_bShowZ1 = FALSE;
	m_btnHideZ1.EnableWindow(FALSE);
	m_btnShowZ1.EnableWindow(TRUE);
	//m_pView->InvalidateRect(NULL,FALSE); 	
	GetDlgItem(IDC_SPIN_DX6)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_DY6)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_DZ6)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_LX6)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_LY6)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_LZ6)->EnableWindow(FALSE);	
	GetDlgItem(IDC_EDIT_DX6)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DY6)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DZ6)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_X6)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Y6)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Z6)->EnableWindow(FALSE);
	m_pView->InvalidateRect(NULL,FALSE);
}

void CParamDlg::OnHideA0()
{
	m_pView->m_bShowA0= FALSE;
	m_btnHideA0.EnableWindow(FALSE);
	m_btnShowA0.EnableWindow(TRUE);
	//m_pView->InvalidateRect(NULL,FALSE); 	
	GetDlgItem(IDC_SPIN_DX)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_DY)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_DZ)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_LX)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_LY)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_LZ)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DX)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DY)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DZ)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_X)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Y)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Z)->EnableWindow(FALSE);
	m_pView->InvalidateRect(NULL,FALSE);
}

void CParamDlg::OnHideA1()
{
	m_pView->m_bShowA1 = FALSE;
	m_btnHideA1.EnableWindow(FALSE);
	m_btnShowA1.EnableWindow(TRUE);
	//m_pView->InvalidateRect(NULL,FALSE);
	GetDlgItem(IDC_SPIN_DX4)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_DY4)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_DZ4)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_LX4)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_LY4)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_LZ4)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DX4)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DY4)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DZ4)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_X4)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Y4)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Z4)->EnableWindow(FALSE);
	m_pView->InvalidateRect(NULL,FALSE);
}

void CParamDlg::OnHideB0()
{
	m_pView->m_bShowB0 = FALSE;
	m_btnHideB0.EnableWindow(FALSE);
	m_btnShowB0.EnableWindow(TRUE);
	//m_pView->InvalidateRect(NULL,FALSE); 	
	GetDlgItem(IDC_SPIN_DX2)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_DY2)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_DZ2)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_LX2)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_LY2)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_LZ2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DX2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DY2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DZ2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_X2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Y2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Z2)->EnableWindow(FALSE);
	m_pView->InvalidateRect(NULL,FALSE);
}

void CParamDlg::OnHideB1()
{
	m_pView->m_bShowB1 = FALSE;
	m_btnHideB1.EnableWindow(FALSE);
	m_btnShowB1.EnableWindow(TRUE);
	//m_pView->InvalidateRect(NULL,FALSE); 	
	GetDlgItem(IDC_SPIN_DX5)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_DY5)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_DZ5)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_LX5)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_LY5)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_LZ5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DX5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DY5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DZ5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_X5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Y5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Z5)->EnableWindow(FALSE);
	m_pView->InvalidateRect(NULL,FALSE);
}

//////////////////////////////////////////////////////////////////////////
void CParamDlg::OnShowZ0()
{
	m_pView->m_bShowZ0 = TRUE;
	m_btnHideZ0.EnableWindow(TRUE);
	m_btnShowZ0.EnableWindow(FALSE);
	//m_pView->InvalidateRect(NULL,FALSE); 	
	GetDlgItem(IDC_SPIN_DX3)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_DY3)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_DZ3)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_LX3)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_LY3)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_LZ3)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DX3)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DY3)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DZ3)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_X3)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_Y3)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_Z3)->EnableWindow(TRUE);
	m_pView->InvalidateRect(NULL,FALSE);
}

void CParamDlg::OnShowZ1()
{
	m_pView->m_bShowZ1 = TRUE;
	m_btnHideZ1.EnableWindow(TRUE);
	m_btnShowZ1.EnableWindow(FALSE);
	//m_pView->InvalidateRect(NULL,FALSE); 	
	GetDlgItem(IDC_SPIN_DX6)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_DY6)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_DZ6)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_LX6)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_LY6)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_LZ6)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DX6)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DY6)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DZ6)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_X6)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_Y6)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_Z6)->EnableWindow(TRUE);
	m_pView->InvalidateRect(NULL,FALSE);
}



void CParamDlg::OnShowA0()
{
	m_pView->m_bShowA0 = TRUE;
	m_btnHideA0.EnableWindow(TRUE);
	m_btnShowA0.EnableWindow(FALSE);
	//m_pView->InvalidateRect(NULL,FALSE); 	
	GetDlgItem(IDC_SPIN_DX)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_DY)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_DZ)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_LX)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_LY)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_LZ)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DX)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DY)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DZ)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_X)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_Y)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_Z)->EnableWindow(TRUE);
	m_pView->InvalidateRect(NULL,FALSE);
}


void CParamDlg::OnShowA1()
{
	m_pView->m_bShowA1 = TRUE;
	m_btnHideA1.EnableWindow(TRUE);
	m_btnShowA1.EnableWindow(FALSE);
	//m_pView->InvalidateRect(NULL,FALSE); 	
	GetDlgItem(IDC_SPIN_DX4)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_DY4)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_DZ4)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_LX4)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_LY4)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_LZ4)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DX4)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DY4)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DZ4)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_X4)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_Y4)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_Z4)->EnableWindow(TRUE);
	m_pView->InvalidateRect(NULL,FALSE);
}


void CParamDlg::OnShowB0()
{
	m_pView->m_bShowB0 = TRUE;
	m_btnHideB0.EnableWindow(TRUE);
	m_btnShowB0.EnableWindow(FALSE);
	//m_pView->InvalidateRect(NULL,FALSE); 	
	GetDlgItem(IDC_SPIN_DX2)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_DY2)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_DZ2)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_LX2)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_LY2)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_LZ2)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DX2)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DY2)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DZ2)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_X2)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_Y2)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_Z2)->EnableWindow(TRUE);
	m_pView->InvalidateRect(NULL,FALSE);
}


void CParamDlg::OnShowB1()
{
	m_pView->m_bShowB1 = TRUE;
	m_btnHideB1.EnableWindow(TRUE);
	m_btnShowB1.EnableWindow(FALSE);
	//m_pView->InvalidateRect(NULL,FALSE); 	
	GetDlgItem(IDC_SPIN_DX5)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_DY5)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_DZ5)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_LX5)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_LY5)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_LZ5)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DX5)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DY5)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DZ5)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_X5)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_Y5)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_Z5)->EnableWindow(TRUE);
	m_pView->InvalidateRect(NULL,FALSE);
}
