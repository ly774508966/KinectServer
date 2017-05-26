#pragma once

#include "afxwin.h"
#include "resource.h"
#include "KinectServerDoc.h"
#include "afxcmn.h"

#include "NuiApi.h"
#include "ImageRenderer.h"
#include "Kinect.h"


//opencvԴ�ļ�
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "asmfitting.h"
//#include "../Nihe.h"
#include <math.h>

#ifdef _DEBUG 
#pragma comment(lib,"opencv_core249d.lib")
#pragma comment(lib,"opencv_highgui249d.lib")
#pragma comment(lib,"opencv_objdetect249d.lib")
#pragma comment(lib,"opencv_imgproc249d.lib")
#pragma comment(lib,"asmlibraryD.lib")
#else
#pragma comment(lib,"opencv_core249.lib")
#pragma comment(lib,"opencv_highgui249.lib")
#pragma comment(lib,"opencv_objdetect249.lib")
#pragma comment(lib,"opencv_imgproc249.lib")
#pragma comment(lib,"asmlibrary.lib")
#endif

// CRightView ������ͼ
class CMainFrame;
class CLeftView;
class CLeftView2;
class CListenSocket;
class CClientSocket;
class CRightView : public CFormView
{
	DECLARE_DYNCREATE(CRightView)

protected:
	CRightView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CRightView();

public:
	enum { IDD = IDD_RIGHTVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	CMainFrame*	m_pMainFrame;
	CLeftView*		m_pLeftView;
	CLeftView2*		m_pLeftView2;
	bool					m_bHasPeople;
	bool					m_bFinish;
	UINT				m_bSave;
	CKinect*			m_pKinect[2];
	CString				m_sPath;

	ImageRenderer*	m_pDrawColor;
	ID2D1Factory*	m_pD2DFactory;

	int				cBytesPerPixel;
	static const int	cStatusMessageMaxLen = MAX_PATH*2;
	int				m_nSensorCount;

	bool				m_bSaveByTimes;//�Ƿ�������
	int				m_nSaveTimes;//ѭ���������
	int				m_nSaveCurrentTime;//��ǰ�������

	//Z������������ƽ�淽�̲���
	double			m_dZ_a;
	double			m_dZ_b;
	double			m_dZ_c;
	double			m_dZ_d;
	double			m_dZ_error;
	bool				m_bZ_up;

	//A������ƽ�淽�̲���
	double			m_dA_a;
	double			m_dA_b;
	double			m_dA_c;
	double			m_dA_d;
	double			m_dA_error;
	bool				m_bA_up;

	//B������ƽ�淽�̲���
	double			m_dB_a;
	double			m_dB_b;
	double			m_dB_c;
	double			m_dB_d;
	double			m_dB_error;
	bool				m_bB_up;

	BYTE				ColorByte[1228802];
	BYTE				ColorByte_new[1228802];
	int				ColorSize;
	short			m_ShowID;

	int				m_nPCNum;
	CString			m_sIP[5];
	CClientSocket*	m_pClientSocket[5];

	float      m_Ra0[3][3];     //��ת����a
	float      m_Ta[1][3];     //ƽ�ƾ���
	float      m_Rb0[3][3];    //��ת����z
	float      m_Tb[1][3];
	float      m_Rz0[3][3];     //��ת����a
	float      m_Tz0[1][3];     //ƽ�ƾ���
	float      m_Ra1[3][3];     //��ת����a
	float      m_Ta1[1][3];     //ƽ�ƾ���
	float      m_Rb1[3][3];    //��ת����z
	float      m_Tb1[1][3];
	float      m_Rz1[3][3];     //��ת����a
	float      m_Tz1[1][3];     //ƽ�ƾ���
	float		R[3][3];
	float		T[1][3];

	//����һ�����۾�
	double		ptEyeLeftX0[3];//�����ϱ�ԵX
	double		ptEyeLeftY0[3];//�����ϱ�ԵY
	double		dEyeLeftParam0[3];//��ϳ���ϵ��,��ֵΪn+1ʱ����ʽ����Ϊn
	double		ptEyeLeftX1[3];//�����±�ԵX
	double		ptEyeLeftY1[3];//�����±�ԵY
	double		dEyeLeftParam1[3];//��ϳ���ϵ��,��ֵΪn+1ʱ����ʽ����Ϊn
	//����һ�����۾�
	double ptEyeRightX0[3];//�����ϱ�ԵX
	double ptEyeRightY0[3];//�����ϱ�ԵY
	double dEyeRightParam0[3];//��ϳ���ϵ��,��ֵΪn+1ʱ����ʽ����Ϊn
	double ptEyeRightX1[3];//�����±�ԵX
	double ptEyeRightY1[3];//�����±�ԵY
	double dEyeRightParam1[3];//��ϳ���ϵ��,��ֵΪn+1ʱ����ʽ����Ϊn

	CStatic		m_sNoteText;
	int			m_nNoteTime;

	int			m_nPicW;
	int			m_nPicH;
	bool        m_bFilterGround;
public:
	void		Init(CRect rect);
	void		OpenKinect();
	bool		CreateFirstConnected();
	void		InitKinect(int index);
	void		BeginGrab();
	CString SetFileTimePath(int index);
	void		GetDepthData(int index,int count);
	void		SaveDepthData(int index);
	void		SaveDepthDataOne(CString fname,float* PointsBuffer);
	void		SaveDepthDataAll(CString fname,float* PointsBuffer);
	void		SetTimeTxt(CString str);
	void		DoCmdPro(UINT cmd,CString fname,UINT UsePointNum,char *FileData);
	void		ReadSysInfo();
	void		MySendCmd(int Cmd);
	void		ShowPic(CStatic* pWnd,CString fname ,int x,int y) ;

	bool		IfAtGround(CString fname, int i, int j, float xx, float yy, float depth);//�Ƿ���˵���

	//���¶��Ǵ���������ߵĺ���
	int		PrintPara(double* Para, int SizeSrc);
	int		ParalimitRow(double* Para, int SizeSrc, int Row);
	int		Paralimit(double* Para, int SizeSrc);
	int		ParaPreDealA(double* Para, int SizeSrc, int Size);
	int		ParaDealA(double* Para, int SizeSrc);
	int		ParaPreDealB(double* Para, int SizeSrc, int OffSet);
	int		ParaDealB(double* Para, int SizeSrc);
	int		ParaDeal(double* Para, int SizeSrc);
	int		GetParaBuffer(double* Para, const double* X, const double* Y, int Amount, int SizeSrc);
	int		CalNihe(const double* BufferX, const double* BufferY, int Amount, int SizeSrc, double* ParaResK);
	
	void		rgb2hsv(int r,int g,int b,HSV& hsv);//��rgb�ռ�ת����hsv�ռ�
	void		Mat3Trans(float input[][3],float output[][3]);
	void		HideButtons();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedSaveOne();
	afx_msg void OnBnClickedSaveByTimes();
	afx_msg void OnBnClickedSaveLots();
	afx_msg void OnBnClickedBtnSwitch();
	afx_msg void OnBiaodingGround();

	afx_msg void OnBnClickedDegree1();
	afx_msg void OnBnClickedDegreeUp1();
	afx_msg void OnBnClickedDegreeDown1();

	afx_msg void OnBnClickedDegree2();
	afx_msg void OnBnClickedDegreeUp2();
	afx_msg void OnBnClickedDegreeDown2();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//������ɫ����������Ϊbmp��ʽͼƬ�����ڽ�����������������ӳ��
	HRESULT SaveBitmapToFile(LONG lWidth, LONG lHeight, WORD wBitsPerPixel, LPCWSTR lpszFilePath);

public:
	CButton m_btnSaveOne;
};


