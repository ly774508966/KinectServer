#pragma once
#include "afxcolorbutton.h"
#include "afxwin.h"


// CColorDlg 对话框

class CColorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CColorDlg)

public:
	CColorDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CColorDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_COLOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CMFCColorButton m_colorCtrlZ0;
	CMFCColorButton m_colorCtrlZ1;
	CMFCColorButton m_colorCtrlA0;
	CMFCColorButton m_colorCtrlA1;
	CMFCColorButton m_colorCtrlB0;
	CMFCColorButton m_colorCtrlB1;
	CButton m_ctrlUseZ0;
	CButton m_ctrlUseZ1;
	CButton m_ctrlUseA0;
	CButton m_ctrlUseA1;
	CButton m_ctrlUseB0;
	CButton m_ctrlUseB1;
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedColorZ0();
	afx_msg void OnBnClickedColorZ1();
	afx_msg void OnBnClickedColorA0();
	afx_msg void OnBnClickedColorA1();
	afx_msg void OnBnClickedColorB0();
	afx_msg void OnBnClickedColorB1();
};
