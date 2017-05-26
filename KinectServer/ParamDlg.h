#pragma once


// CParamDlg 对话框

class CParamDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CParamDlg)

public:
	CParamDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CParamDlg();
	int m_nTimes;//定时器次数
	// 对话框数据
	enum { IDD = IDD_DLG_PARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void SaveParam();

	afx_msg void OnBnClickedOk();
	afx_msg void OnDeltaposSpinDx(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinDy(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinDz(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinLx(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinLy(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinLz(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
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
	afx_msg void OnBnClickedSave();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
