#pragma once

#include "afxwin.h"
#include "resource.h"
#include "KinectServerDoc.h"
#include "afxcmn.h"
#include "CPoint3D.h"
#include <vector>
using namespace std;
// CLeftView 窗体视图
class CMainFrame;
class CLeftView : public CFormView
{
	DECLARE_DYNCREATE(CLeftView)

protected:
	CLeftView();           // 动态创建所使用的受保护的构造函数
	virtual ~CLeftView();

public:
	enum { IDD = IDD_LEFTVIEW2 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:

	BYTE m_btRGB_Z0[640*480*3];
	BYTE m_btRGB_Z1[640*480*3];
	BYTE m_btRGB_A0[640*480*3];
	BYTE m_btRGB_A1[640*480*3];
	BYTE m_btRGB_B0[640*480*3];
	BYTE m_btRGB_B1[640*480*3];

	int m_nBytesWidth;

	void ShowPoint(CString filename);
	void ReadPoint(CString filename);
	void DrawZ0(CDC* pDC);
	void DrawZ1(CDC* pDC);
	void DrawA0(CDC* pDC);
	void DrawA1(CDC* pDC);
	void DrawB0(CDC* pDC);
	void DrawB1(CDC* pDC);
	CString m_sBmpPath;

	void Destory();					//销毁窗口函数
	BITMAPINFO bmi;
	HGLRC m_hRC;		// 绘制环境，HGLRC是一个指向rendering context的句柄
	HDC	m_hDC;			//Windows 设备环境句柄
	CRect m_rect;

	bool m_bFirstDraw;//只绘制一次

	CMainFrame* m_pMainFrame;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnDraw(CDC* pDC);

	HRESULT SaveBitmapToFile(BYTE* pBitmapBits, LONG lWidth, LONG lHeight, WORD wBitsPerPixel, LPCWSTR lpszFilePath);
};


