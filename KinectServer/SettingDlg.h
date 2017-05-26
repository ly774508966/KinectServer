#pragma once
#include "afxwin.h"


// CSettingDlg �Ի���
class CMainFrame;
class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSettingDlg();
	CMainFrame*	m_pMainFrame;
// �Ի�������
	enum { IDD = IDD_DLG_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CButton m_checkStartToShoot;
	CButton m_checkAuto;
	CButton m_checkSaveFarData;
	CComboBox m_comboShootStyle;
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckStarttoshoot();
	afx_msg void OnCheckAuto();
	afx_msg void OnCheckSavefardata();
};
