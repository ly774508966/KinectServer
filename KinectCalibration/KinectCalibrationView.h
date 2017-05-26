
// KinectCalibrationView.h : CKinectCalibrationView ��Ľӿ�
//

#pragma once
#include "resource.h"
#include <vector>
#include "KinectCalibrationDoc.h"
using namespace std;
class COpenGL;
const float PARAM_X = (float)(1.0 / 525.0);
const float PARAM_Y = (float)(1.0 / 525.0);
#define BMP_WIDTH 640
#define BMP_HEIGHT 480
/***********************************************************************************
ϵ��������޷�������ֹ�������Ŀǰ��������ܲ����ƣ������ܺܺõؽ���������
ԭ�����������ʽ��ͬһ�г���һ��ϵ��������ʽ�Ľⲻ��
��Ȼ�����������⣬����һ���������⣬Ҳ��ͬ����˼·�����ڶ���������Ĵ���ܲ����ƣ��д��Ż�
����Ϊ��λ����
***********************************************************************************/
//�Ѷ�ά��������һά�����ת����Ҳ����ֱ���ö�ά���飬ֻ���ҵ�ϰ���ǲ��ö�ά����
#define ParaBuffer(Buffer,Row,Col) (*(Buffer + (Row) * (SizeSrc + 1) + (Col)))
#define WEISHU 3//����ά��

class CKinectCalibrationView : public CView
{
protected: // �������л�����
	CKinectCalibrationView();
	DECLARE_DYNCREATE(CKinectCalibrationView)

// ����
public:
	CKinectCalibrationDoc* GetDocument() const;
	//vector<vector<POINT6D> >  m_pPointsList;
	vector<POINT6D>  m_pPointsList[6];
	float							m_fDeltaDegree;
	vector<POINT6D>  m_pointsZ0;
	vector<POINT6D>  m_pointsZ1;
	vector<POINT6D>  m_pointsA0;
	vector<POINT6D>  m_pointsA1;
	vector<POINT6D>  m_pointsB0;
	vector<POINT6D>  m_pointsB1;
	vector<POINT6D>  m_pointsZ0_new;
	vector<POINT6D>  m_pointsZ1_new;
	vector<POINT6D>  m_pointsA0_new;
	vector<POINT6D>  m_pointsA1_new;
	vector<POINT6D>  m_pointsB0_new;
	vector<POINT6D>  m_pointsB1_new;
	vector<MyPoint>		m_myCloudA0;
	vector<MyPoint>		m_myCloudB0;
	vector<MyPoint>		m_myCloudZ0;
	vector<MyPoint>		m_myCloudA1;
	vector<MyPoint>		m_myCloudB1;
	vector<MyPoint>		m_myCloudZ1;

	SHORT m_nBmpZ0[BMP_HEIGHT][BMP_WIDTH];
	SHORT m_nBmpA0[BMP_HEIGHT][BMP_WIDTH];
	SHORT m_nBmpB0[BMP_HEIGHT][BMP_WIDTH];
	SHORT m_nBmpZ1[BMP_HEIGHT][BMP_WIDTH];
	SHORT m_nBmpA1[BMP_HEIGHT][BMP_WIDTH];
	SHORT m_nBmpB1[BMP_HEIGHT][BMP_WIDTH];
	CString m_sFilepath;
	bool		m_bNewFilepath;//�Ƿ������һ���µ�pcd�ļ�����·��
	//CBmpDlg *m_dlgBmp;

	bool							m_bShowZ0;
	bool							m_bShowZ1;
	bool							m_bShowA0;
	bool							m_bShowA1;
	bool							m_bShowB0;
	bool							m_bShowB1;
	POINT3D prBoxCenter;
	POINT3D prBoxSize;
	HGLRC m_hRC;		// ���ƻ�����HGLRC��һ��ָ��rendering context�ľ��
	HDC	m_hDC;			//Windows �豸�������

	COpenGL m_nViewOpenGL;

	int m_GLPixelIndex;		//���ظ�ʽ������ֵ�����ù������
	
	bool m_bInit;
	bool m_bLButtonDown;
	bool m_bRButtonDown;
	
	float m_fDegreeX;//���������ϵ�ת��
	float m_fDegreeY;
	float m_fDegreeZ;

	float m_fTranslateX;//����û������
	float m_fTranslateY;
	float m_fTranslateZ;

	CPoint m_oldpointL;
	CPoint m_oldpointR;
	POINT3D prMax , prMin;

	float      m_Ra0[3][3];     //��ת����
	float      m_Ta0[1][3];     //ƽ�ƾ���
	float		g_inverseRa0[3][3];//ԭ�任����������
	float      m_Rb0[3][3];    //��ת����
	float      m_Tb0[1][3];
	float		g_inverseRb0[3][3];//ԭ�任��������
	float      m_Rz0[3][3];     //��ת����
	float      m_Tz0[1][3];     //ƽ�ƾ���
	float		g_inverseRz0[3][3];//ԭ�任����������
	float      m_Ra1[3][3];     //��ת����
	float      m_Ta1[1][3];     //ƽ�ƾ���
	float		g_inverseRa1[3][3];//ԭ�任����������
	float      m_Rb1[3][3];    //��ת����
	float      m_Tb1[1][3];	  //ƽ�ƾ���
	float		g_inverseRb1[3][3];//ԭ�任����������
	float      m_Rz1[3][3];     //��ת����
	float      m_Tz1[1][3];     //ƽ�ƾ���
	float		g_inverseRz1[3][3];//ԭ�任����������

	float		g_T[1][3];
	float		g_R[3][3];	
	float		g_inverseR[3][3];//ԭ�任����������

	float m_deltaZ0;
	float m_contrastZ0;
	float m_lightZ0;
	float m_deltaA0;
	float m_contrastA0;
	float m_lightA0;
	float m_deltaB0;
	float m_contrastB0;
	float m_lightB0;
	float m_deltaZ1;
	float m_contrastZ1;
	float m_lightZ1;
	float m_deltaA1;
	float m_contrastA1;
	float m_lightA1;
	float m_deltaB1;
	float m_contrastB1;
	float m_lightB1;

	vector<float>disArray;//��¼ÿ���Ҷ�ֵ��Ӧ�ľ���

	float	  m_deltaAngle;
	float	  m_deltaTranslation;

	COLORREF m_colorZ0;
	COLORREF m_colorZ1;
	COLORREF m_colorA0;
	COLORREF m_colorA1;
	COLORREF m_colorB0;
	COLORREF m_colorB1;
	bool		m_bUseZ0;//�Ƿ�ʹ�õ�ɫ
	bool		m_bUseZ1;
	bool		m_bUseA0;
	bool		m_bUseA1;
	bool		m_bUseB0;
	bool		m_bUseB1;

	bool		m_bOpenOriginTxt;//�򿪵��Ƿ�Ϊԭʼ���ļ���Ҳ����û�г���ת��������ļ�
	bool		m_bOpenPcd;
// ����
public:
	inline double PointsDistance(CPoint point1,CPoint point2);
	void	ReadSysInfo();//��ȡsys.txt�ļ��е�����
	void ReadIniInfo();//��ȡinfo.ini�ļ��е�����
	void    ChangeMatrix(CString filename);
	void    OnSetParam();
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CKinectCalibrationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	bool CreateViewGLContext (HDC hDC);
	bool SetWindowPixelFormat(HDC hDC);  // �������ƻ���(RC)��ʹ֮��Ϊ��ǰ���ƻ���
	bool InitGL(void);		// ��ʼ��openGL
	void ShowPoint(CString filename);
	void ReadTxtPoint(CString filename);//��ȡtxt�ļ��еĵ���
	void ReadBmpFile(CString filename);//��ȡbmp�ļ��������pcd�ļ�һ���ȡ
	void ReadPcdPoint(CString filename);//��ȡpcd�ļ��еĵ���
	void GetCloudByBmp(CString filename);//�����������ͼ���ȡ��������
	void DrawGL();
	void DrawZ0();
	void DrawZ1();
	void DrawA0();
	void DrawA1();
	void DrawB0();
	void DrawB1();
	void Destory();					//���ٴ��ں���

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnCloseZ0();
	afx_msg void OnCloseZ1();
	afx_msg void OnCloseA0();
	afx_msg void OnCloseA1();
	afx_msg void OnCloseB0();
	afx_msg void OnCloseB1();
	afx_msg void OnResetView();
	afx_msg void OnCloseAll();
	afx_msg void OnFileOpen();
	afx_msg void OnSetColor();
	afx_msg void OnSetAngle();
	afx_msg void OnOpenOrigin();
	afx_msg void OnOpenAfterfilter();
	afx_msg void OnOpenPcd();
	afx_msg void OnUpdateOpenOriginTxt(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenfilterTxt(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenPcd(CCmdUI *pCmdUI);

	

	int PrintPara(double* Para, int SizeSrc);
	int ParalimitRow(double* Para, int SizeSrc, int Row);
	int Paralimit(double* Para, int SizeSrc);
	int ParaPreDealA(double* Para, int SizeSrc, int Size);
	int ParaDealA(double* Para, int SizeSrc);
	int ParaPreDealB(double* Para, int SizeSrc, int OffSet);
	int ParaDealB(double* Para, int SizeSrc);
	int ParaDeal(double* Para, int SizeSrc);
	int GetParaBuffer(double* Para, const double* X, const double* Y, int Amount, int SizeSrc);
	int CalcAll(const double* BufferX, const double* BufferY, int Amount, int SizeSrc, double* ParaResK);
	float CKinectCalibrationView::getA(float arcs[WEISHU][WEISHU], int n);
	void  getAStart(float arcs[WEISHU][WEISHU], int n, float ans[WEISHU][WEISHU]);
	bool GetMatrixInverse(float src[WEISHU][WEISHU], int n, float des[WEISHU][WEISHU]);
	afx_msg void OnSetBmp();
	afx_msg void OnHelp();
};

#ifndef _DEBUG  // KinectCalibrationView.cpp �еĵ��԰汾
inline CKinectCalibrationDoc* CKinectCalibrationView::GetDocument() const
   { return reinterpret_cast<CKinectCalibrationDoc*>(m_pDocument); }
#endif

