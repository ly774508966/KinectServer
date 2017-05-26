#pragma once
#include "NuiApi.h"

//700,1700是最开始的参数，但有时候会超出，所有做了适量的修改
#define Mindepth 200
#define Maxdepth 2000

//#define Mindepth -1
//#define Maxdepth 10000

struct HSV{
	int h;
	int s;
	int v;
};

class CRightView;
class CKinect
{
public:
	CKinect(CRightView* rightView);
	~CKinect();

public:
	CRightView*	m_pRightView;
	HANDLE		m_hColorStreamHandle;
	HANDLE		m_hNextColorFrameEvent;
	HANDLE		m_hDepthStreamHandle;
	HANDLE		m_hNextDepthFrameEvent;
	HANDLE		m_hNextSkeletonEvent;


	int			m_nColorWidth ;
	int			m_nColorHeight;

	INuiSensor	*m_pNuiSensor;
	CString		m_sDeviceId;
	int			m_nDeviceNum;

	NUI_IMAGE_FRAME m_ImageFrame_color;
	INuiFrameTexture* m_pTextureColor;
	NUI_LOCKED_RECT m_LockedRectColor;

	NUI_IMAGE_FRAME m_ImageFrame_depth;
	INuiFrameTexture * pTextureDepth1;

	int		m_nLinePoint[480];
	int		m_nhangEnd;
	int		m_nhangRun;
	float	m_PointsBuffer[480*640*4];  //距离+RGB

	CString					m_sPath;
	int						m_nCount;

protected:
	
public:
	bool CreateFirstConnected(int index);
	bool Init();
	void Shutdown();
	void GrabImage(UINT bSave);
	void GetColorData(int getcount);
	void GetDepthData(int getcount);
	void Degree0();
	void Up();
	void Down();
	/*bool IfFilter(CString fname, int i, int j, float xx, float yy, float depth);*/
	void rgb2hsv(int r,int g,int b,HSV& hsv);
	HRESULT SaveBitmapToFile(BYTE* pBitmapBits, LONG lWidth, LONG lHeight, WORD wBitsPerPixel, LPCWSTR lpszFilePath);
};