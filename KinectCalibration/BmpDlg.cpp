// BmpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "KinectCalibration.h"
#include "BmpDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "KinectCalibrationDoc.h"
#include "KinectCalibrationView.h"

// CBmpDlg 对话框

IMPLEMENT_DYNAMIC(CBmpDlg, CDialogEx)

CBmpDlg::CBmpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBmpDlg::IDD, pParent)
{
	m_bChangeZ0 = false;
	m_bChangeA0 = false;
	m_bChangeB0 = false;
	m_bChangeZ1 = false;
	m_bChangeA1 = false;
	m_bChangeB1 = false;
	m_bShowZ0 = true;
	m_bShowA0 = true;
	m_bShowB0 = true;
	m_bShowZ1 = true;
	m_bShowA1 = true;
	m_bShowB1 = true;
}

CBmpDlg::~CBmpDlg()
{
}

void CBmpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_DELTA_Z0, m_slider_delta_z0);
	DDX_Control(pDX, IDC_SLIDER_DELTA_A0, m_slider_delta_a0);
	DDX_Control(pDX, IDC_SLIDER_DELTA_B0, m_slider_delta_b0);
	DDX_Control(pDX, IDC_SLIDER_DELTA_Z1, m_slider_delta_z1);
	DDX_Control(pDX, IDC_SLIDER_DELTA_A1, m_slider_delta_a1);
	DDX_Control(pDX, IDC_SLIDER_DELTA_B1, m_slider_delta_b1);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST_Z0, m_slider_contrast_z0);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST_A0, m_slider_contrast_a0);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST_B0, m_slider_contrast_b0);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST_Z1, m_slider_contrast_z1);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST_A1, m_slider_contrast_a1);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST_B1, m_slider_contrast_b1);
	DDX_Control(pDX, IDC_SLIDER_LIGHT_Z0, m_slider_light_z0);
	DDX_Control(pDX, IDC_SLIDER_LIGHT_A0, m_slider_light_a0);
	DDX_Control(pDX, IDC_SLIDER_LIGHT_B0, m_slider_light_b0);
	DDX_Control(pDX, IDC_SLIDER_LIGHT_Z1, m_slider_light_z1);
	DDX_Control(pDX, IDC_SLIDER_LIGHT_A1, m_slider_light_a1);
	DDX_Control(pDX, IDC_SLIDER_LIGHT_B1, m_slider_light_b1);
	DDX_Control(pDX, IDC_STATIC_DELTA_Z0, m_label_delta_z0);
	DDX_Control(pDX, IDC_STATIC_DELTA_A0, m_label_delta_a0);
	DDX_Control(pDX, IDC_STATIC_DELTA_B0, m_label_delta_b0);
	DDX_Control(pDX, IDC_STATIC_DELTA_Z1, m_label_delta_z1);
	DDX_Control(pDX, IDC_STATIC_DELTA_A1, m_label_delta_a1);
	DDX_Control(pDX, IDC_STATIC_DELTA_B1, m_label_delta_b1);
	DDX_Control(pDX, IDC_STATIC_CONTRAST_Z0, m_label_contrast_z0);
	DDX_Control(pDX, IDC_STATIC_CONTRAST_A0, m_label_contrast_a0);
	DDX_Control(pDX, IDC_STATIC_CONTRAST_B0, m_label_contrast_b0);
	DDX_Control(pDX, IDC_STATIC_CONTRAST_Z1, m_label_contrast_z1);
	DDX_Control(pDX, IDC_STATIC_CONTRAST_A1, m_label_contrast_a1);
	DDX_Control(pDX, IDC_STATIC_CONTRAST_B1, m_label_contrast_b1);
	DDX_Control(pDX, IDC_STATIC_LIGHT_Z0, m_label_light_z0);
	DDX_Control(pDX, IDC_STATIC_LIGHT_A0, m_label_light_a0);
	DDX_Control(pDX, IDC_STATIC_LIGHT_B0, m_label_light_b0);
	DDX_Control(pDX, IDC_STATIC_LIGHT_Z1, m_label_light_z1);
	DDX_Control(pDX, IDC_STATIC_LIGHT_A1, m_label_light_a1);
	DDX_Control(pDX, IDC_STATIC_LIGHT_B1, m_label_light_b1);
	DDX_Control(pDX, IDC_BUTTON_SHOWHIDE_Z0, m_btn_showhide_z0);
	DDX_Control(pDX, IDC_BUTTON_SHOWHIDE_A0, m_btn_showhide_a0);
	DDX_Control(pDX, IDC_BUTTON_SHOWHIDE_B0, m_btn_showhide_b0);
	DDX_Control(pDX, IDC_BUTTON_SHOWHIDE_Z1, m_btn_showhide_z1);
	DDX_Control(pDX, IDC_BUTTON_SHOWHIDE_A1, m_btn_showhide_a1);
	DDX_Control(pDX, IDC_BUTTON_SHOWHIDE_B1, m_btn_showhide_b1);
}


BEGIN_MESSAGE_MAP(CBmpDlg, CDialogEx)
	ON_BN_CLICKED(ID_SAVE, &CBmpDlg::OnSave)
	ON_BN_CLICKED(IDC_ORIGIN, &CBmpDlg::OnOrigin)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_SHOWHIDE_Z0, &CBmpDlg::OnShowhideZ0)
	ON_BN_CLICKED(IDC_BUTTON_SHOWHIDE_A0, &CBmpDlg::OnShowhideA0)
	ON_BN_CLICKED(IDC_BUTTON_SHOWHIDE_B0, &CBmpDlg::OnShowhideB0)
	ON_BN_CLICKED(IDC_BUTTON_SHOWHIDE_Z1, &CBmpDlg::OnShowhideZ1)
	ON_BN_CLICKED(IDC_BUTTON_SHOWHIDE_A1, &CBmpDlg::OnShowhideA1)
	ON_BN_CLICKED(IDC_BUTTON_SHOWHIDE_B1, &CBmpDlg::OnShowhideB1)
END_MESSAGE_MAP()


// CBmpDlg 消息处理程序


BOOL CBmpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_pFrm = (CMainFrame*)AfxGetMainWnd();
	m_pView = (CKinectCalibrationView *)m_pFrm->GetActiveView();
	m_sFilepath = m_pView->m_sFilepath;
	InitParam();
	return TRUE;
}

void CBmpDlg::InitParam()
{
	//初始化间隔阈值
	int delta_min = 30;
	int delta_max = 60;
	m_slider_delta_z0.SetRange(delta_min, delta_max);
	m_slider_delta_a0.SetRange(delta_min, delta_max);
	m_slider_delta_b0.SetRange(delta_min, delta_max);
	m_slider_delta_z1.SetRange(delta_min, delta_max);
	m_slider_delta_a1.SetRange(delta_min, delta_max);
	m_slider_delta_b1.SetRange(delta_min, delta_max);
	m_slider_delta_z0.SetTicFreq(1);
	m_slider_delta_a0.SetTicFreq(1);
	m_slider_delta_b0.SetTicFreq(1);
	m_slider_delta_z1.SetTicFreq(1);
	m_slider_delta_a1.SetTicFreq(1);
	m_slider_delta_b1.SetTicFreq(1);
	m_slider_delta_z0.SetPos(10 * m_pView->m_deltaZ0);
	m_slider_delta_a0.SetPos(10 * m_pView->m_deltaA0);
	m_slider_delta_b0.SetPos(10 * m_pView->m_deltaB0);
	m_slider_delta_z1.SetPos(10 * m_pView->m_deltaZ1);
	m_slider_delta_a1.SetPos(10 * m_pView->m_deltaA1);
	m_slider_delta_b1.SetPos(10 * m_pView->m_deltaB1);
	CString str;
	str.Format(L"%.1f", m_slider_delta_z0.GetPos() / 10.0);
	m_label_delta_z0.SetWindowTextW(str);
	str.Format(L"%.1f", m_slider_delta_a0.GetPos() / 10.0);
	m_label_delta_a0.SetWindowTextW(str);
	str.Format(L"%.1f", m_slider_delta_b0.GetPos() / 10.0);
	m_label_delta_b0.SetWindowTextW(str);
	str.Format(L"%.1f", m_slider_delta_z1.GetPos() / 10.0);
	m_label_delta_z1.SetWindowTextW(str);
	str.Format(L"%.1f", m_slider_delta_a1.GetPos() / 10.0);
	m_label_delta_a1.SetWindowTextW(str);
	str.Format(L"%.1f", m_slider_delta_b1.GetPos() / 10.0);
	m_label_delta_b1.SetWindowTextW(str);
	//初始化对比度
	int contrast_min = 10;
	int contrast_max = 50;
	m_slider_contrast_z0.SetRange(contrast_min, contrast_max);
	m_slider_contrast_a0.SetRange(contrast_min, contrast_max);
	m_slider_contrast_b0.SetRange(contrast_min, contrast_max);
	m_slider_contrast_z1.SetRange(contrast_min, contrast_max);
	m_slider_contrast_a1.SetRange(contrast_min, contrast_max);
	m_slider_contrast_b1.SetRange(contrast_min, contrast_max);
	m_slider_contrast_z0.SetTicFreq(1);
	m_slider_contrast_a0.SetTicFreq(1);
	m_slider_contrast_b0.SetTicFreq(1);
	m_slider_contrast_z1.SetTicFreq(1);
	m_slider_contrast_a1.SetTicFreq(1);
	m_slider_contrast_b1.SetTicFreq(1);
	m_slider_contrast_z0.SetPos(10 * m_pView->m_contrastZ0);
	m_slider_contrast_a0.SetPos(10 * m_pView->m_contrastA0);
	m_slider_contrast_b0.SetPos(10 * m_pView->m_contrastB0);
	m_slider_contrast_z1.SetPos(10 * m_pView->m_contrastZ1);
	m_slider_contrast_a1.SetPos(10 * m_pView->m_contrastA1);
	m_slider_contrast_b1.SetPos(10 * m_pView->m_contrastB1);
	str.Format(L"%.1f", m_slider_contrast_z0.GetPos() / 10.0);
	m_label_contrast_z0.SetWindowTextW(str);
	str.Format(L"%.1f", m_slider_contrast_a0.GetPos() / 10.0);
	m_label_contrast_a0.SetWindowTextW(str);
	str.Format(L"%.1f", m_slider_contrast_b0.GetPos() / 10.0);
	m_label_contrast_b0.SetWindowTextW(str);
	str.Format(L"%.1f", m_slider_contrast_z1.GetPos() / 10.0);
	m_label_contrast_z1.SetWindowTextW(str);
	str.Format(L"%.1f", m_slider_contrast_a1.GetPos() / 10.0);
	m_label_contrast_a1.SetWindowTextW(str);
	str.Format(L"%.1f", m_slider_contrast_b1.GetPos() / 10.0);
	m_label_contrast_b1.SetWindowTextW(str);
	//初始化亮度
	int light_min = -150;
	int light_max = 150;
	m_slider_light_z0.SetRange(light_min, light_max);
	m_slider_light_a0.SetRange(light_min, light_max);
	m_slider_light_b0.SetRange(light_min, light_max);
	m_slider_light_z1.SetRange(light_min, light_max);
	m_slider_light_a1.SetRange(light_min, light_max);
	m_slider_light_b1.SetRange(light_min, light_max);
	m_slider_light_z0.SetTicFreq(1);
	m_slider_light_a0.SetTicFreq(1);
	m_slider_light_b0.SetTicFreq(1);
	m_slider_light_z1.SetTicFreq(1);
	m_slider_light_a1.SetTicFreq(1);
	m_slider_light_b1.SetTicFreq(1);
	m_slider_light_z0.SetPos(m_pView->m_lightZ0);
	m_slider_light_a0.SetPos(m_pView->m_lightA0);
	m_slider_light_b0.SetPos(m_pView->m_lightB0);
	m_slider_light_z1.SetPos(m_pView->m_lightZ1);
	m_slider_light_a1.SetPos(m_pView->m_lightA1);
	m_slider_light_b1.SetPos(m_pView->m_lightB1);
	str.Format(L"%d", m_slider_light_z0.GetPos());
	m_label_light_z0.SetWindowTextW(str);
	str.Format(L"%d", m_slider_light_a0.GetPos());
	m_label_light_a0.SetWindowTextW(str);
	str.Format(L"%d", m_slider_light_b0.GetPos());
	m_label_light_b0.SetWindowTextW(str);
	str.Format(L"%d", m_slider_light_z1.GetPos());
	m_label_light_z1.SetWindowTextW(str);
	str.Format(L"%d", m_slider_light_a1.GetPos());
	m_label_light_a1.SetWindowTextW(str);
	str.Format(L"%d", m_slider_light_b1.GetPos());
	m_label_light_b1.SetWindowTextW(str);
}

void CBmpDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar != NULL)
	{
		// 强制转换成CSliderCtrl
		CSliderCtrl* pSlider = (CSliderCtrl*)pScrollBar;
		CString str;
		// 根据CSliderCtrl ID 来判断是哪一个CSliderCtrl
		//首先是稀疏程度
		if (pSlider->GetDlgCtrlID() == IDC_SLIDER_DELTA_Z0) {
			if (m_pView->m_myCloudZ0.size() != 0) {
				m_pView->m_deltaZ0 = m_slider_delta_z0.GetPos() / 10.0;
				str.Format(L"%.1f", m_pView->m_deltaZ0);
				m_label_delta_z0.SetWindowTextW(str);
				m_pView->ReadBmpFile(m_sFilepath + L"Z0.bmp");
				m_pView->GetCloudByBmp(L"Z0");
				m_pView->InvalidateRect(NULL, FALSE);
			}else {
				m_slider_delta_z0.SetPos(10 * m_pView->m_deltaZ0);
			}
		}else if (pSlider->GetDlgCtrlID() == IDC_SLIDER_DELTA_A0) {
			if (m_pView->m_myCloudA0.size() != 0) {
				m_pView->m_deltaA0 = m_slider_delta_a0.GetPos() / 10.0;
				str.Format(L"%.1f", m_pView->m_deltaA0);
				m_label_delta_a0.SetWindowTextW(str);
				m_pView->ReadBmpFile(m_sFilepath + L"A0.bmp");
				m_pView->GetCloudByBmp(L"A0");
				m_pView->InvalidateRect(NULL, FALSE);
			}else {
				m_slider_delta_a1.SetPos(10 * m_pView->m_deltaA0);
			}
		}else if (pSlider->GetDlgCtrlID() == IDC_SLIDER_DELTA_B0) {
			if (m_pView->m_myCloudB0.size() != 0) {
				m_pView->m_deltaB0 = m_slider_delta_b0.GetPos() / 10.0;
				str.Format(L"%.1f", m_pView->m_deltaB0);
				m_label_delta_b0.SetWindowTextW(str);
				m_pView->ReadBmpFile(m_sFilepath + L"B0.bmp");
				m_pView->GetCloudByBmp(L"B0");
				m_pView->InvalidateRect(NULL, FALSE);
			}else {
				m_slider_delta_b0.SetPos(10 * m_pView->m_deltaB0);
			}
		}else if (pSlider->GetDlgCtrlID() == IDC_SLIDER_DELTA_Z1) {
			if (m_pView->m_myCloudZ1.size() != 0) {
				m_pView->m_deltaZ1 = m_slider_delta_z1.GetPos() / 10.0;
				str.Format(L"%.1f", m_pView->m_deltaZ1);
				m_label_delta_z1.SetWindowTextW(str);
				m_pView->ReadBmpFile(m_sFilepath + L"Z1.bmp");
				m_pView->GetCloudByBmp(L"Z1");
				m_pView->InvalidateRect(NULL, FALSE);
			}else {
				m_slider_delta_z1.SetPos(10 * m_pView->m_deltaZ1);
			}
		}else if (pSlider->GetDlgCtrlID() == IDC_SLIDER_DELTA_A1) {
			if (m_pView->m_myCloudA1.size() != 0) {
				m_pView->m_deltaA1 = m_slider_delta_a1.GetPos() / 10.0;
				str.Format(L"%.1f", m_pView->m_deltaA1);
				m_label_delta_a1.SetWindowTextW(str);
				m_pView->ReadBmpFile(m_sFilepath + L"A1.bmp");
				m_pView->GetCloudByBmp(L"A1");
				m_pView->InvalidateRect(NULL, FALSE);
			}else {
				m_slider_delta_a1.SetPos(10 * m_pView->m_deltaA1);
			}
		}else if (pSlider->GetDlgCtrlID() == IDC_SLIDER_DELTA_B1) {
			if (m_pView->m_myCloudB1.size() != 0) {
				m_pView->m_deltaB1 = m_slider_delta_b1.GetPos() / 10.0;
				str.Format(L"%.1f", m_pView->m_deltaB1);
				m_label_delta_b1.SetWindowTextW(str);
				m_pView->ReadBmpFile(m_sFilepath + L"B1.bmp");
				m_pView->GetCloudByBmp(L"B1");
				m_pView->InvalidateRect(NULL, FALSE);
			}else {
				m_slider_delta_b1.SetPos(10 * m_pView->m_deltaB1);
			}
		}
		//然后是对比度
		else if (pSlider->GetDlgCtrlID() == IDC_SLIDER_CONTRAST_Z0) {
			if (m_pView->m_myCloudZ0.size() != 0) {
				m_pView->m_contrastZ0 = m_slider_contrast_z0.GetPos() / 10.0;
				str.Format(L"%.1f", m_pView->m_contrastZ0);
				m_label_contrast_z0.SetWindowTextW(str);
				m_pView->ReadBmpFile(m_sFilepath + L"Z0.bmp");
				m_pView->GetCloudByBmp(L"Z0");
				m_pView->InvalidateRect(NULL, FALSE);
			}else {
				m_slider_contrast_z0.SetPos(10 * m_pView->m_contrastZ0);
			}
		}else if (pSlider->GetDlgCtrlID() == IDC_SLIDER_CONTRAST_A0) {
			if (m_pView->m_myCloudA0.size() != 0) {
				m_pView->m_contrastA0 = m_slider_contrast_a0.GetPos() / 10.0;
				str.Format(L"%.1f", m_pView->m_contrastA0);
				m_label_contrast_a0.SetWindowTextW(str);
				m_pView->ReadBmpFile(m_sFilepath + L"A0.bmp");
				m_pView->GetCloudByBmp(L"A0");
				m_pView->InvalidateRect(NULL, FALSE);
			}else {
				m_slider_contrast_a0.SetPos(10 * m_pView->m_contrastA0);
			}
		}else if (pSlider->GetDlgCtrlID() == IDC_SLIDER_CONTRAST_B0) {
			if (m_pView->m_myCloudB0.size() != 0) {
				m_pView->m_contrastB0 = m_slider_contrast_b0.GetPos() / 10.0;
				str.Format(L"%.1f", m_pView->m_contrastB0);
				m_label_contrast_b0.SetWindowTextW(str);
				m_pView->ReadBmpFile(m_sFilepath + L"B0.bmp");
				m_pView->GetCloudByBmp(L"B0");
				m_pView->InvalidateRect(NULL, FALSE);
			}else {
				m_slider_contrast_b0.SetPos(10 * m_pView->m_contrastB0);
			}
		}else if (pSlider->GetDlgCtrlID() == IDC_SLIDER_CONTRAST_Z1) {
			if (m_pView->m_myCloudZ1.size() != 0) {
				m_pView->m_contrastZ1 = m_slider_contrast_z1.GetPos() / 10.0;
				str.Format(L"%.1f", m_pView->m_contrastZ1);
				m_label_contrast_z1.SetWindowTextW(str);
				m_pView->ReadBmpFile(m_sFilepath + L"Z1.bmp");
				m_pView->GetCloudByBmp(L"Z1");
				m_pView->InvalidateRect(NULL, FALSE);
			}else {
				m_slider_contrast_z1.SetPos(10 * m_pView->m_contrastZ1);
			}
		}else if (pSlider->GetDlgCtrlID() == IDC_SLIDER_CONTRAST_A1) {
			if (m_pView->m_myCloudA1.size() != 0) {
				m_pView->m_contrastA1 = m_slider_contrast_a1.GetPos() / 10.0;
				str.Format(L"%.1f", m_pView->m_contrastA1);
				m_label_contrast_a1.SetWindowTextW(str);
				m_pView->ReadBmpFile(m_sFilepath + L"A1.bmp");
				m_pView->GetCloudByBmp(L"A1");
				m_pView->InvalidateRect(NULL, FALSE);
			}else {
				m_slider_contrast_a1.SetPos(10 * m_pView->m_contrastA1);
			}
		}else if (pSlider->GetDlgCtrlID() == IDC_SLIDER_CONTRAST_B1) {
			if (m_pView->m_myCloudB1.size() != 0) {
				m_pView->m_contrastB1 = m_slider_contrast_b1.GetPos() / 10.0;
				str.Format(L"%.1f", m_pView->m_contrastB1);
				m_label_contrast_b1.SetWindowTextW(str);
				m_pView->ReadBmpFile(m_sFilepath + L"B1.bmp");
				m_pView->GetCloudByBmp(L"B1");
				m_pView->InvalidateRect(NULL, FALSE);
			}else {
				m_slider_contrast_b1.SetPos(10 * m_pView->m_contrastB1);
			}
		}
		//最后是亮度
		else if (pSlider->GetDlgCtrlID() == IDC_SLIDER_LIGHT_Z0) {
			if (m_pView->m_myCloudZ0.size() != 0) {
				m_pView->m_lightZ0 = m_slider_light_z0.GetPos();
				str.Format(L"%d", m_slider_light_z0.GetPos());
				m_label_light_z0.SetWindowTextW(str);
				m_pView->ReadBmpFile(m_sFilepath + L"Z0.bmp");
				m_pView->GetCloudByBmp(L"Z0");
				m_pView->InvalidateRect(NULL, FALSE);
			}else {
				m_slider_light_z0.SetPos(m_pView->m_lightZ0);
			}
		}else if (pSlider->GetDlgCtrlID() == IDC_SLIDER_LIGHT_A0) {
			if (m_pView->m_myCloudA0.size() != 0) {
				m_pView->m_lightA0 = m_slider_light_a0.GetPos();
				str.Format(L"%d", m_slider_light_a0.GetPos());
				m_label_light_a0.SetWindowTextW(str);
				m_pView->ReadBmpFile(m_sFilepath + L"A0.bmp");
				m_pView->GetCloudByBmp(L"A0");
				m_pView->InvalidateRect(NULL, FALSE);
			}else {
				m_slider_light_a0.SetPos(m_pView->m_lightA0);
			}
		}else if (pSlider->GetDlgCtrlID() == IDC_SLIDER_LIGHT_B0) {
			if (m_pView->m_myCloudB0.size() != 0) {
				m_pView->m_lightB0 = m_slider_light_b0.GetPos();
				str.Format(L"%d", m_slider_light_b0.GetPos());
				m_label_light_b0.SetWindowTextW(str);
				m_pView->ReadBmpFile(m_sFilepath + L"B0.bmp");
				m_pView->GetCloudByBmp(L"B0");
				m_pView->InvalidateRect(NULL, FALSE);
			}else {
				m_slider_light_b0.SetPos(m_pView->m_lightB0);
			}
		}else if (pSlider->GetDlgCtrlID() == IDC_SLIDER_LIGHT_Z1) {
			if (m_pView->m_myCloudZ1.size() != 0) {
				m_pView->m_lightZ1 = m_slider_light_z1.GetPos();
				str.Format(L"%d", m_slider_light_z1.GetPos());
				m_label_light_z1.SetWindowTextW(str);
				m_pView->ReadBmpFile(m_sFilepath + L"Z1.bmp");
				m_pView->GetCloudByBmp(L"Z1");
				m_pView->InvalidateRect(NULL, FALSE);
			}else {
				m_slider_light_z1.SetPos(m_pView->m_lightZ1);
			}
		}else if (pSlider->GetDlgCtrlID() == IDC_SLIDER_LIGHT_A1) {
			if (m_pView->m_myCloudA1.size() != 0) {
				m_pView->m_lightA1 = m_slider_light_a1.GetPos();
				str.Format(L"%d", m_slider_light_a1.GetPos());
				m_label_light_a1.SetWindowTextW(str);
				m_pView->ReadBmpFile(m_sFilepath + L"A1.bmp");
				m_pView->GetCloudByBmp(L"A1");
				m_pView->InvalidateRect(NULL, FALSE);
			}else {
				m_slider_light_a1.SetPos(m_pView->m_lightA1);
			}
		}else if (pSlider->GetDlgCtrlID() == IDC_SLIDER_LIGHT_B1) {
			if (m_pView->m_myCloudB1.size() != 0) {
				m_pView->m_lightB1 = m_slider_light_b1.GetPos();
				str.Format(L"%d", m_slider_light_b1.GetPos());
				m_label_light_b1.SetWindowTextW(str);
				m_pView->ReadBmpFile(m_sFilepath + L"B1.bmp");
				m_pView->GetCloudByBmp(L"B1");
				m_pView->InvalidateRect(NULL, FALSE);
			}else {
				m_slider_light_b1.SetPos(m_pView->m_lightB1);
			}
		}
	}
}

void CBmpDlg::OnShowhideZ0()
{
	if (m_bShowZ0 == true) {
		m_btn_showhide_z0.SetWindowTextW(L"显示");
		m_bShowZ0 = false;
		m_pView->m_bShowZ0 = false;
		m_pView->InvalidateRect(NULL, FALSE);
	}else {
		m_btn_showhide_z0.SetWindowTextW(L"隐藏");
		m_bShowZ0 = true;
		m_pView->m_bShowZ0 = true;
		m_pView->InvalidateRect(NULL, FALSE);
	}
}


void CBmpDlg::OnShowhideA0()
{
	if (m_bShowA0 == true) {
		m_btn_showhide_a0.SetWindowTextW(L"显示");
		m_bShowA0 = false;
		m_pView->m_bShowA0 = false;
		m_pView->InvalidateRect(NULL, FALSE);
	}else {
		m_btn_showhide_a0.SetWindowTextW(L"隐藏");
		m_bShowA0 = true;
		m_pView->m_bShowA0 = true;
		m_pView->InvalidateRect(NULL, FALSE);
	}
}


void CBmpDlg::OnShowhideB0()
{
	if (m_bShowB0 == true) {
		m_btn_showhide_b0.SetWindowTextW(L"显示");
		m_bShowB0 = false;
		m_pView->m_bShowB0 = false;
		m_pView->InvalidateRect(NULL, FALSE);
	}else {
		m_btn_showhide_b0.SetWindowTextW(L"隐藏");
		m_bShowB0 = true;
		m_pView->m_bShowB0 = true;
		m_pView->InvalidateRect(NULL, FALSE);
	}
}


void CBmpDlg::OnShowhideZ1()
{
	if (m_bShowZ1 == true) {
		m_btn_showhide_z1.SetWindowTextW(L"显示");
		m_bShowZ1 = false;
		m_pView->m_bShowZ1 = false;
		m_pView->InvalidateRect(NULL, FALSE);
	}
	else {
		m_btn_showhide_z1.SetWindowTextW(L"隐藏");
		m_bShowZ1 = true;
		m_pView->m_bShowZ1 = true;
		m_pView->InvalidateRect(NULL, FALSE);
	}
}


void CBmpDlg::OnShowhideA1()
{
	if (m_bShowA1 == true) {
		m_btn_showhide_a1.SetWindowTextW(L"显示");
		m_bShowA1 = false;
		m_pView->m_bShowA1 = false;
		m_pView->InvalidateRect(NULL, FALSE);
	}
	else {
		m_btn_showhide_a1.SetWindowTextW(L"隐藏");
		m_bShowA1 = true;
		m_pView->m_bShowA1 = true;
		m_pView->InvalidateRect(NULL, FALSE);
	}
}


void CBmpDlg::OnShowhideB1()
{
	if (m_bShowB1 == true) {
		m_btn_showhide_b1.SetWindowTextW(L"显示");
		m_bShowB1 = false;
		m_pView->m_bShowB1 = false;
		m_pView->InvalidateRect(NULL, FALSE);
	}
	else {
		m_btn_showhide_b1.SetWindowTextW(L"隐藏");
		m_bShowB1 = true;
		m_pView->m_bShowB1 = true;
		m_pView->InvalidateRect(NULL, FALSE);
	}
}

void CBmpDlg::OnSave()
{
	if (::MessageBox(this->m_hWnd, L"请注意，该操作会将当前所有参数保存至本地，之后再还原将重置为当前保存的参数!\n是否确认？\n", L"提示", MB_YESNO) == IDYES)
	{
		CString m_sPath;
		GetModuleFileName(NULL, m_sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
		int pos = m_sPath.ReverseFind('\\');
		m_sPath = m_sPath.Left(pos);
		FILE *fp;
		CString infoPath = m_sPath + _T("\\初始文件\\info.ini");
		CString str;
		str.Format(L"%.1f", m_slider_delta_z0.GetPos() / 10.0);
		WritePrivateProfileString(_T("sys"), _T("Z0_delta"), str, infoPath);
		str.Format(L"%.1f", m_slider_delta_a0.GetPos() / 10.0);
		WritePrivateProfileString(_T("sys"), _T("A0_delta"), str, infoPath);
		str.Format(L"%.1f", m_slider_delta_b0.GetPos() / 10.0);
		WritePrivateProfileString(_T("sys"), _T("B0_delta"), str, infoPath);
		str.Format(L"%.1f", m_slider_delta_z1.GetPos() / 10.0);
		WritePrivateProfileString(_T("sys"), _T("Z1_delta"), str, infoPath);
		str.Format(L"%.1f", m_slider_delta_a1.GetPos() / 10.0);
		WritePrivateProfileString(_T("sys"), _T("A1_delta"), str, infoPath);
		str.Format(L"%.1f", m_slider_delta_b1.GetPos() / 10.0);
		WritePrivateProfileString(_T("sys"), _T("B1_delta"), str, infoPath);
		str.Format(L"%.1f", m_slider_contrast_z0.GetPos() / 10.0);
		WritePrivateProfileString(_T("sys"), _T("Z0_contrast"), str, infoPath);
		str.Format(L"%.1f", m_slider_contrast_a0.GetPos() / 10.0);
		WritePrivateProfileString(_T("sys"), _T("A0_contrast"), str, infoPath);
		str.Format(L"%.1f", m_slider_contrast_b0.GetPos() / 10.0);
		WritePrivateProfileString(_T("sys"), _T("B0_contrast"), str, infoPath);
		str.Format(L"%.1f", m_slider_contrast_z1.GetPos() / 10.0);
		WritePrivateProfileString(_T("sys"), _T("Z1_contrast"), str, infoPath);
		str.Format(L"%.1f", m_slider_contrast_a1.GetPos() / 10.0);
		WritePrivateProfileString(_T("sys"), _T("A1_contrast"), str, infoPath);
		str.Format(L"%.1f", m_slider_contrast_b1.GetPos() / 10.0);
		WritePrivateProfileString(_T("sys"), _T("B1_contrast"), str, infoPath);
		str.Format(L"%d", m_slider_light_z0.GetPos());
		WritePrivateProfileString(_T("sys"), _T("Z0_light"), str, infoPath);
		str.Format(L"%d", m_slider_light_a0.GetPos());
		WritePrivateProfileString(_T("sys"), _T("A0_light"), str, infoPath);
		str.Format(L"%d", m_slider_light_b0.GetPos());
		WritePrivateProfileString(_T("sys"), _T("B0_light"), str, infoPath);
		str.Format(L"%d", m_slider_light_z1.GetPos());
		WritePrivateProfileString(_T("sys"), _T("Z1_light"), str, infoPath);
		str.Format(L"%d", m_slider_light_a1.GetPos());
		WritePrivateProfileString(_T("sys"), _T("A1_light"), str, infoPath);
		str.Format(L"%d", m_slider_light_b1.GetPos());
		WritePrivateProfileString(_T("sys"), _T("B1_light"), str, infoPath);
	}
}

void CBmpDlg::OnOrigin()
{
	m_pView->ReadIniInfo();
	InitParam();
	if (m_pView->m_myCloudZ0.size() != 0) {
		m_pView->ReadBmpFile(m_sFilepath + L"Z0.bmp");
		m_pView->GetCloudByBmp(L"Z0");
	}
	if (m_pView->m_myCloudA0.size() != 0) {
		m_pView->ReadBmpFile(m_sFilepath + L"A0.bmp");
		m_pView->GetCloudByBmp(L"A0");
	}
	if (m_pView->m_myCloudB0.size() != 0) {
		m_pView->ReadBmpFile(m_sFilepath + L"B0.bmp");
		m_pView->GetCloudByBmp(L"B0");
	}
	if (m_pView->m_myCloudZ1.size() != 0) {
		m_pView->ReadBmpFile(m_sFilepath + L"Z1.bmp");
		m_pView->GetCloudByBmp(L"Z1");
	}
	if (m_pView->m_myCloudA1.size() != 0) {
		m_pView->ReadBmpFile(m_sFilepath + L"A1.bmp");
		m_pView->GetCloudByBmp(L"A1");
	}
	if (m_pView->m_myCloudB1.size() != 0) {
		m_pView->ReadBmpFile(m_sFilepath + L"B1.bmp");
		m_pView->GetCloudByBmp(L"B1");
	}
	m_pView->InvalidateRect(NULL, FALSE);
}
