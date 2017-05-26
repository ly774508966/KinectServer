#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CBmpDlg 对话框
class CMainFrame;
class CKinectCalibrationView;
class CBmpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBmpDlg)

public:
	CBmpDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBmpDlg();
	CMainFrame *m_pFrm;
	CKinectCalibrationView *m_pView;
// 对话框数据
	enum { IDD = IDD_DIALOG_BMP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void InitParam();
	afx_msg void OnSave();
	afx_msg void OnOrigin();
	CSliderCtrl m_slider_delta_z0;
	CSliderCtrl m_slider_delta_a0;
	CSliderCtrl m_slider_delta_b0;
	CSliderCtrl m_slider_delta_z1;
	CSliderCtrl m_slider_delta_a1;
	CSliderCtrl m_slider_delta_b1;
	CStatic m_label_delta_z0;
	CStatic m_label_delta_a0;
	CStatic m_label_delta_b0;
	CStatic m_label_delta_z1;
	CStatic m_label_delta_a1;
	CStatic m_label_delta_b1;
	CStatic m_label_contrast_z0;
	CStatic m_label_contrast_a0;
	CStatic m_label_contrast_b0;
	CStatic m_label_contrast_z1;
	CStatic m_label_contrast_a1;
	CStatic m_label_contrast_b1;
	CStatic m_label_light_z0;
	CStatic m_label_light_a0;
	CStatic m_label_light_b0;
	CStatic m_label_light_z1;
	CStatic m_label_light_a1;
	CStatic m_label_light_b1;
	CSliderCtrl m_slider_contrast_z0;
	CSliderCtrl m_slider_contrast_a0;
	CSliderCtrl m_slider_contrast_b0;
	CSliderCtrl m_slider_contrast_z1;
	CSliderCtrl m_slider_contrast_a1;
	CSliderCtrl m_slider_contrast_b1;
	CSliderCtrl m_slider_light_z0;
	CSliderCtrl m_slider_light_a0;
	CSliderCtrl m_slider_light_b0;
	CSliderCtrl m_slider_light_z1;
	CSliderCtrl m_slider_light_a1;
	CSliderCtrl m_slider_light_b1;
	bool m_bChangeZ0;
	bool m_bChangeA0;
	bool m_bChangeB0;
	bool m_bChangeZ1;
	bool m_bChangeA1;
	bool m_bChangeB1;
	bool m_bShowZ0;
	bool m_bShowA0;
	bool m_bShowB0;
	bool m_bShowZ1;
	bool m_bShowA1;
	bool m_bShowB1;
	CString m_sFilepath;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CButton m_btn_showhide_z0;
	CButton m_btn_showhide_a0;
	CButton m_btn_showhide_b0;
	CButton m_btn_showhide_z1;
	CButton m_btn_showhide_a1;
	CButton m_btn_showhide_b1;
	afx_msg void OnShowhideZ0();
	afx_msg void OnShowhideA0();
	afx_msg void OnShowhideB0();
	afx_msg void OnShowhideZ1();
	afx_msg void OnShowhideA1();
	afx_msg void OnShowhideB1();
};
