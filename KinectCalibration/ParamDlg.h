#pragma once
#include "afxwin.h"

// CParamDlg 对话框
class CMainFrame;
class CKinectCalibrationView;
class CParamDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CParamDlg)

public:
	CParamDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CParamDlg();
	int m_nTimes;//定时器次数
	float m_deltaAngle;
	float m_deltaTranslation;
	CString m_strTimer;
	CMainFrame *m_pFrm;
	CKinectCalibrationView *m_pView;

// 对话框数据
	enum { IDD = IDD_DLG_PARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSave();
	void SaveParam();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedSaveZ0();
	afx_msg void OnBnClickedSaveZ1();
	afx_msg void OnBnClickedSaveA0();
	afx_msg void OnBnClickedSaveA1();
	afx_msg void OnBnClickedSaveB0();
	afx_msg void OnBnClickedSaveB1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDeltaposSpinDx(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinDy(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinDz(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinLx(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinLy(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinLz(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinDx2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinDy2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinDz2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinLx2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinLy2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinLz2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinDx3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinDy3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinDz3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinLx3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinLy3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinLz3(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnDeltaposSpinDx4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinDy4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinDz4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinLx4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinLy4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinLz4(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnDeltaposSpinDx5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinDy5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinDz5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinLx5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinLy5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinLz5(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnDeltaposSpinDx6(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinDy6(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinDz6(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinLx6(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinLy6(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinLz6(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHideZ0();
	afx_msg void OnHideZ1();
	afx_msg void OnHideA0();
	afx_msg void OnHideA1();
	afx_msg void OnHideB0();
	afx_msg void OnHideB1();
	CButton m_btnHideZ0;
	CButton m_btnHideZ1;
	CButton m_btnHideA0;
	CButton m_btnHideA1;
	CButton m_btnHideB0;
	CButton m_btnHideB1;
	CButton m_btnShowZ0;
	CButton m_btnShowZ1;
	CButton m_btnShowA0;
	CButton m_btnShowA1;
	CButton m_btnShowB0;
	CButton m_btnShowB1;
	afx_msg void OnShowZ1();
	afx_msg void OnShowZ0();
	
	afx_msg void OnShowA0();
	afx_msg void OnShowA1();
	afx_msg void OnShowB0();
	afx_msg void OnShowB1();
	int m_nDegreePerKey;
};
