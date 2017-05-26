// ColorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MainFrm.h"
#include "KinectCalibration.h"
#include "KinectCalibrationView.h"
#include "ColorDlg.h"
#include "afxdialogex.h"


// CColorDlg 对话框

IMPLEMENT_DYNAMIC(CColorDlg, CDialogEx)

CColorDlg::CColorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CColorDlg::IDD, pParent)
{

}

CColorDlg::~CColorDlg()
{
}

void CColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_colorCtrlZ0);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON2, m_colorCtrlZ1);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON3, m_colorCtrlA0);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON4, m_colorCtrlA1);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON5, m_colorCtrlB0);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON6, m_colorCtrlB1);
	DDX_Control(pDX, IDC_CHECK1, m_ctrlUseZ0);
	DDX_Control(pDX, IDC_CHECK2, m_ctrlUseZ1);
	DDX_Control(pDX, IDC_CHECK3, m_ctrlUseA0);
	DDX_Control(pDX, IDC_CHECK4, m_ctrlUseA1);
	DDX_Control(pDX, IDC_CHECK5, m_ctrlUseB0);
	DDX_Control(pDX, IDC_CHECK6, m_ctrlUseB1);
}


BEGIN_MESSAGE_MAP(CColorDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SAVE, &CColorDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &CColorDlg::OnBnClickedColorZ0)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON2, &CColorDlg::OnBnClickedColorZ1)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON3, &CColorDlg::OnBnClickedColorA0)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON4, &CColorDlg::OnBnClickedColorA1)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON5, &CColorDlg::OnBnClickedColorB0)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON6, &CColorDlg::OnBnClickedColorB1)
END_MESSAGE_MAP()


// CColorDlg 消息处理程序


BOOL CColorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	CKinectCalibrationView* pView = (CKinectCalibrationView*)pFrm->GetActiveView();
	m_colorCtrlZ0.SetColor(pView->m_colorZ0);
	m_colorCtrlZ1.SetColor(pView->m_colorZ1);
	m_colorCtrlA0.SetColor(pView->m_colorA0);
	m_colorCtrlA1.SetColor(pView->m_colorA1);
	m_colorCtrlB0.SetColor(pView->m_colorB0);
	m_colorCtrlB1.SetColor(pView->m_colorB1);
	m_ctrlUseZ0.SetCheck(pView->m_bUseZ0);
	m_ctrlUseZ1.SetCheck(pView->m_bUseZ1);
	m_ctrlUseA0.SetCheck(pView->m_bUseA0);
	m_ctrlUseA1.SetCheck(pView->m_bUseA1);
	m_ctrlUseB0.SetCheck(pView->m_bUseB0);
	m_ctrlUseB1.SetCheck(pView->m_bUseB1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CColorDlg::OnBnClickedSave()
{
	//首先将这些值传回给View类，并重绘
	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	CKinectCalibrationView* pView = (CKinectCalibrationView*)pFrm->GetActiveView();
	pView->m_colorZ0 = m_colorCtrlZ0.GetColor();
	pView->m_colorZ1 = m_colorCtrlZ1.GetColor();
	pView->m_colorA0 = m_colorCtrlA0.GetColor();
	pView->m_colorA1 = m_colorCtrlA1.GetColor();
	pView->m_colorB0 = m_colorCtrlB0.GetColor();
	pView->m_colorB1 = m_colorCtrlB1.GetColor();
	pView->m_bUseZ0 = m_ctrlUseZ0.GetCheck();
	pView->m_bUseZ1 = m_ctrlUseZ1.GetCheck();
	pView->m_bUseA0 = m_ctrlUseA0.GetCheck();
	pView->m_bUseA1 = m_ctrlUseA1.GetCheck();
	pView->m_bUseB0 = m_ctrlUseB0.GetCheck();
	pView->m_bUseB1 = m_ctrlUseB1.GetCheck();
	pView->InvalidateRect(NULL,FALSE);
	//再将这些值保存到ini文件中去
	CString m_sPath;
	GetModuleFileName(NULL,m_sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	int pos = m_sPath.ReverseFind('\\');
	m_sPath = m_sPath.Left(pos);
	FILE *fp;
	CString infoPath=m_sPath+_T("\\初始文件\\info.ini");
	CString str;
	str.Format(_T("%d"),GetRValue(pView->m_colorZ0));
	WritePrivateProfileString(_T("sys"),_T("Z0_R"),str,infoPath);
	str.Format(_T("%d"),GetGValue(pView->m_colorZ0));
	WritePrivateProfileString(_T("sys"),_T("Z0_G"),str,infoPath);
	str.Format(_T("%d"),GetBValue(pView->m_colorZ0));
	WritePrivateProfileString(_T("sys"),_T("Z0_B"),str,infoPath);
	str.Format(_T("%d"),pView->m_bUseZ0);
	WritePrivateProfileString(_T("sys"),_T("Z0_USE"),str,infoPath);

	str.Format(_T("%d"),GetRValue(pView->m_colorZ1));
	WritePrivateProfileString(_T("sys"),_T("Z1_R"),str,infoPath);
	str.Format(_T("%d"),GetGValue(pView->m_colorZ1));
	WritePrivateProfileString(_T("sys"),_T("Z1_G"),str,infoPath);
	str.Format(_T("%d"),GetBValue(pView->m_colorZ1));
	WritePrivateProfileString(_T("sys"),_T("Z1_B"),str,infoPath);
	str.Format(_T("%d"),pView->m_bUseZ1);
	WritePrivateProfileString(_T("sys"),_T("Z1_USE"),str,infoPath);

	str.Format(_T("%d"),GetRValue(pView->m_colorA0));
	WritePrivateProfileString(_T("sys"),_T("A0_R"),str,infoPath);
	str.Format(_T("%d"),GetGValue(pView->m_colorA0));
	WritePrivateProfileString(_T("sys"),_T("A0_G"),str,infoPath);
	str.Format(_T("%d"),GetBValue(pView->m_colorA0));
	WritePrivateProfileString(_T("sys"),_T("A0_B"),str,infoPath);
	str.Format(_T("%d"),pView->m_bUseA0);
	WritePrivateProfileString(_T("sys"),_T("A0_USE"),str,infoPath);

	str.Format(_T("%d"),GetRValue(pView->m_colorA1));
	WritePrivateProfileString(_T("sys"),_T("A1_R"),str,infoPath);
	str.Format(_T("%d"),GetGValue(pView->m_colorA1));
	WritePrivateProfileString(_T("sys"),_T("A1_G"),str,infoPath);
	str.Format(_T("%d"),GetBValue(pView->m_colorA1));
	WritePrivateProfileString(_T("sys"),_T("A1_B"),str,infoPath);
	str.Format(_T("%d"),pView->m_bUseA1);
	WritePrivateProfileString(_T("sys"),_T("A1_USE"),str,infoPath);

	str.Format(_T("%d"),GetRValue(pView->m_colorB0));
	WritePrivateProfileString(_T("sys"),_T("B0_R"),str,infoPath);
	str.Format(_T("%d"),GetGValue(pView->m_colorB0));
	WritePrivateProfileString(_T("sys"),_T("B0_G"),str,infoPath);
	str.Format(_T("%d"),GetBValue(pView->m_colorB0));
	WritePrivateProfileString(_T("sys"),_T("B0_B"),str,infoPath);
	str.Format(_T("%d"),pView->m_bUseB0);
	WritePrivateProfileString(_T("sys"),_T("B0_USE"),str,infoPath);

	str.Format(_T("%d"),GetRValue(pView->m_colorB1));
	WritePrivateProfileString(_T("sys"),_T("B1_R"),str,infoPath);
	str.Format(_T("%d"),GetGValue(pView->m_colorB1));
	WritePrivateProfileString(_T("sys"),_T("B1_G"),str,infoPath);
	str.Format(_T("%d"),GetBValue(pView->m_colorB1));
	WritePrivateProfileString(_T("sys"),_T("B1_B"),str,infoPath);
	str.Format(_T("%d"),pView->m_bUseB1);
	WritePrivateProfileString(_T("sys"),_T("B1_USE"),str,infoPath);
}


void CColorDlg::OnBnClickedColorZ0()
{
}


void CColorDlg::OnBnClickedColorZ1()
{

}


void CColorDlg::OnBnClickedColorA0()
{

}


void CColorDlg::OnBnClickedColorA1()
{

}


void CColorDlg::OnBnClickedColorB0()
{

}


void CColorDlg::OnBnClickedColorB1()
{

}
