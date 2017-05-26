// SettingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "KinectServer.h"
#include "SettingDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"


// CSettingDlg 对话框

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSettingDlg::IDD, pParent)
{

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_STARTTOSHOOT, m_checkStartToShoot);
	DDX_Control(pDX, IDC_CHECK_AUTO, m_checkAuto);
	DDX_Control(pDX, IDC_COMBO_SHOOTSTYLE, m_comboShootStyle);
	DDX_Control(pDX, IDC_CHECK_SAVEFARDATA, m_checkSaveFarData);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSettingDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSettingDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK_STARTTOSHOOT, &CSettingDlg::OnCheckStarttoshoot)
	ON_BN_CLICKED(IDC_CHECK_AUTO, &CSettingDlg::OnCheckAuto)
	ON_BN_CLICKED(IDC_CHECK_SAVEFARDATA, &CSettingDlg::OnCheckSavefardata)
END_MESSAGE_MAP()


// CSettingDlg 消息处理程序


void CSettingDlg::OnBnClickedOk()
{
	// 保存系统设置
	CString sPathRoot,sPath,str;
	GetModuleFileName(NULL,sPathRoot.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	int pos = sPathRoot.ReverseFind('\\');
	sPathRoot = sPathRoot.Left(pos);
	CString infoPath=sPathRoot+_T("\\初始文件\\info.ini");
	//是否程序启动时直接拍摄
	if (m_checkStartToShoot.GetCheck()) {
		m_pMainFrame->m_bStartToShoot = true;
		str = L"1";
	}else {
		m_pMainFrame->m_bStartToShoot = false;
		str = L"0";
	}
	WritePrivateProfileString(_T("sys"),_T("IsStartToShoot"),str,infoPath);
	str.ReleaseBuffer();
	//是否程序运行时自动拍摄
	if (m_checkAuto.GetCheck()) {
		m_pMainFrame->m_bAutoShoot = true;
		str = L"1";
	}else {
		m_pMainFrame->m_bAutoShoot = false;
		str = L"0";
	}
	WritePrivateProfileString(_T("sys"),_T("IsAutoShoot"),str,infoPath);
	str.ReleaseBuffer();
	//是否保存远程数据
	if (m_checkSaveFarData.GetCheck()) {
		m_pMainFrame->m_bSaveFarData = true;
		str = L"1";
	}else {
		m_pMainFrame->m_bSaveFarData = false;
		str = L"0";
	}
	WritePrivateProfileString(_T("sys"),_T("IsSaveFarData"),str,infoPath);
	str.ReleaseBuffer();
	//拍摄方式——0:拍摄整体、1:拍摄上半身
	int nIndex = m_comboShootStyle.GetCurSel();
	m_pMainFrame->m_nShootStyle = nIndex;
	str.Format(L"%d", nIndex);
	WritePrivateProfileString(_T("sys"),_T("ShootStyle"),str,infoPath);
	CDialogEx::OnOK();
	
}


void CSettingDlg::OnBnClickedCancel()
{
	// 不保存直接退出	 
	CDialogEx::OnCancel();
}


BOOL CSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	m_checkStartToShoot.SetCheck(m_pMainFrame->m_bStartToShoot);
	m_checkAuto.SetCheck(m_pMainFrame->m_bAutoShoot);
	m_checkSaveFarData.SetCheck(m_pMainFrame->m_bSaveFarData);
	m_comboShootStyle.InsertString(0,L"拍摄整体");
	m_comboShootStyle.InsertString(1,L"拍摄上半身");
	//m_comboShootStyle.AddString(L"拍摄整体");
	//m_comboShootStyle.AddString(L"拍摄上半身");
	m_comboShootStyle.SetCurSel(m_pMainFrame->m_nShootStyle);
	return TRUE;
}

//下面的这些消息响应是不需要的
void CSettingDlg::OnCheckStarttoshoot()
{
	
}

void CSettingDlg::OnCheckAuto()
{
	
}

void CSettingDlg::OnCheckSavefardata()
{
	
}


