#pragma once

#include "afxwin.h"
#include "resource.h"
#include "KinectServerDoc.h"
#include "afxcmn.h"
#include "CPoint3D.h"
#include <vector>
using namespace std;
// CLeftView2 窗体视图

class CLeftView2 : public CFormView
{
	DECLARE_DYNCREATE(CLeftView2)

protected:
	CLeftView2();           // 动态创建所使用的受保护的构造函数
	virtual ~CLeftView2();

public:
	enum { IDD = IDD_LEFTVIEW2 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	vector<POINT6D>  m_pointsZ0_new;
	vector<POINT6D>  m_pointsZ1_new;
	vector<POINT6D>  m_pointsA0_new;
	vector<POINT6D>  m_pointsA1_new;
	vector<POINT6D>  m_pointsB0_new;
	vector<POINT6D>  m_pointsB1_new;
	vector<MY_POINT3D>  m_pPointsList;
	POINT3D prBoxCenter;
	POINT3D prBoxSize;

	void ShowPoint(CString filename);
	void ReadPoint(CString filename);
	void ReadPointAll(CString sType);
	void DrawGL();
	void DrawAll();
	void DrawZ0();
	void DrawZ1();
	void DrawA0();
	void DrawA1();
	void DrawB0();
	void DrawB1();

	bool CreateViewGLContext (HDC hDC);
	bool SetWindowPixelFormat(HDC hDC);  // 创建绘制环境(RC)并使之成为当前绘制环境
	void Destory();					//销毁窗口函数
	bool InitGL(void);		// 初始化openGL
	void OnRotate();

	int m_GLPixelIndex;		//像素格式的索引值
	HGLRC m_hRC;		// 绘制环境，HGLRC是一个指向rendering context的句柄
	HDC	m_hDC;			//Windows 设备环境句柄
	int m_nShowTime;
	bool m_bRotateShow;
	float m_fDegreeY;
	float m_fDegreeDelta;
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
};


