// VisualAngleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KinectCalibration.h"
#include "VisualAngleDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "KinectCalibrationView.h"

// CVisualAngleDlg �Ի���

IMPLEMENT_DYNAMIC(CVisualAngleDlg, CDialogEx)

CVisualAngleDlg::CVisualAngleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVisualAngleDlg::IDD, pParent)
{

}

CVisualAngleDlg::~CVisualAngleDlg()
{
}

void CVisualAngleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVisualAngleDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON18, &CVisualAngleDlg::OnYang)
	ON_BN_CLICKED(IDC_BUTTON1, &CVisualAngleDlg::OnZheng)
	ON_BN_CLICKED(IDC_BUTTON17, &CVisualAngleDlg::OnFu)
	ON_BN_CLICKED(IDC_BUTTON4, &CVisualAngleDlg::OnBei)
	ON_BN_CLICKED(IDC_BUTTON3, &CVisualAngleDlg::OnZuo)
	ON_BN_CLICKED(IDC_BUTTON19, &CVisualAngleDlg::OnYou)
	ON_BN_CLICKED(IDC_BUTTON5, &CVisualAngleDlg::OnZhouCeShi)
	ON_BN_CLICKED(IDC_BUTTON2, &CVisualAngleDlg::OnZuoHou)
	ON_BN_CLICKED(IDC_BUTTON15, &CVisualAngleDlg::OnYouHou)
	ON_BN_CLICKED(IDC_BUTTON16, &CVisualAngleDlg::OnZouQian)
	ON_BN_CLICKED(IDC_BUTTON20, &CVisualAngleDlg::OnYouQian)
END_MESSAGE_MAP()


// CVisualAngleDlg ��Ϣ�������

//����ͼ
void CVisualAngleDlg::OnYang()
{
	pView->m_fDegreeX = -90;
	pView->m_fDegreeY = 180;
	pView->m_fDegreeZ = 0;
	pView->InvalidateRect(NULL,FALSE);
}

//����ͼ
void CVisualAngleDlg::OnZheng()
{
	pView->m_fDegreeX = 0;
	pView->m_fDegreeY = 180;
	pView->m_fDegreeZ = 0;
	pView->InvalidateRect(NULL,FALSE);
}

//����ͼ
void CVisualAngleDlg::OnFu()
{
	pView->m_fDegreeX = 90;
	pView->m_fDegreeY = 180;
	pView->m_fDegreeZ = 0;
	pView->InvalidateRect(NULL,FALSE);
}

//����ͼ
void CVisualAngleDlg::OnBei()
{
	pView->m_fDegreeX = 0;
	pView->m_fDegreeY = 0;
	pView->m_fDegreeZ = 0;
	pView->InvalidateRect(NULL,FALSE);
}

//����ͼ
void CVisualAngleDlg::OnZuo()
{
	pView->m_fDegreeX = 0;
	pView->m_fDegreeY = -90;
	pView->m_fDegreeZ = 0;
	pView->InvalidateRect(NULL,FALSE);
}

//����ͼ
void CVisualAngleDlg::OnYou()
{
	pView->m_fDegreeX = 0;
	pView->m_fDegreeY = 90;
	pView->m_fDegreeZ = 0;
	pView->InvalidateRect(NULL,FALSE);
}

//�����ͼ
void CVisualAngleDlg::OnZhouCeShi()
{
	pView->m_fDegreeX = 30.0;
	pView->m_fDegreeY = -150.0;
	pView->m_fDegreeZ = 0;
	pView->InvalidateRect(NULL,FALSE);
}

void CVisualAngleDlg::OnZuoHou()
{
	pView->m_fDegreeX = 0;
	pView->m_fDegreeY = -45.0;
	pView->m_fDegreeZ = 0;
	pView->InvalidateRect(NULL,FALSE);
}


void CVisualAngleDlg::OnYouHou()
{
	pView->m_fDegreeX = 0;
	pView->m_fDegreeY = 45.0;
	pView->m_fDegreeZ = 0;
	pView->InvalidateRect(NULL,FALSE);
}

void CVisualAngleDlg::OnZouQian()
{
	pView->m_fDegreeX = 0;
	pView->m_fDegreeY = -135.0;
	pView->m_fDegreeZ = 0;
	pView->InvalidateRect(NULL,FALSE);
}

void CVisualAngleDlg::OnYouQian()
{
	pView->m_fDegreeX = 0;
	pView->m_fDegreeY = 135.0;
	pView->m_fDegreeZ = 0;
	pView->InvalidateRect(NULL,FALSE);
}

BOOL CVisualAngleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	pFrm = (CMainFrame*)AfxGetMainWnd();
	pView = (CKinectCalibrationView*)pFrm->GetActiveView();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
