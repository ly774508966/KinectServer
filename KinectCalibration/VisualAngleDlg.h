#pragma once


// CVisualAngleDlg 对话框
class CMainFrame;
class CKinectCalibrationView;
class CVisualAngleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisualAngleDlg)

public:
	CVisualAngleDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVisualAngleDlg();
	afx_msg void OnYang();
	afx_msg void OnZheng();
	afx_msg void OnFu();
	afx_msg void OnBei();
	afx_msg void OnZuo();
	afx_msg void OnYou();
	afx_msg void OnZhouCeShi();
// 对话框数据
	enum { IDD = IDD_ANGLE };
public:
	CMainFrame* pFrm;
	CKinectCalibrationView* pView;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnZuoHou();
	afx_msg void OnYouHou();
	afx_msg void OnZouQian();
	afx_msg void OnYouQian();
};
