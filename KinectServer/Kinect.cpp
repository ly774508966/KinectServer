#include "Stdafx.h"
#include "Kinect.h"
#include "math.h"
#include "RightView.h"

CKinect::CKinect(CRightView* rightview)
{
	m_pRightView=rightview;
	m_hNextColorFrameEvent=INVALID_HANDLE_VALUE;
	m_hNextDepthFrameEvent= INVALID_HANDLE_VALUE;
	m_hNextSkeletonEvent=INVALID_HANDLE_VALUE;
	m_hColorStreamHandle=INVALID_HANDLE_VALUE;
	m_hDepthStreamHandle=INVALID_HANDLE_VALUE;
}
CKinect::~CKinect()
{
	if (m_hNextDepthFrameEvent != INVALID_HANDLE_VALUE)
		CloseHandle(m_hNextDepthFrameEvent);
	if (m_hNextColorFrameEvent != INVALID_HANDLE_VALUE)
		CloseHandle(m_hNextColorFrameEvent);
	if (m_hNextSkeletonEvent != INVALID_HANDLE_VALUE)
		CloseHandle(m_hNextSkeletonEvent);
}

bool CKinect::CreateFirstConnected(int index)
{
	HRESULT hr;
	if (index<0)
		return false;
	INuiSensor * pNuiSensor=NULL;
	hr = NuiCreateSensorByIndex(index, &pNuiSensor);
	if (S_OK != hr)
	{
		AfxMessageBox(_T("初始化失败"));
		return false;
	}
	hr = pNuiSensor->NuiStatus();
	m_pNuiSensor = pNuiSensor;
	pNuiSensor->Release();
	if (NULL == m_pNuiSensor || FAILED(hr))
	{
		//AfxMessageBox("初始化失败");
		return false;
	}
	BSTR bstr=m_pNuiSensor->NuiDeviceConnectionId();
	m_sDeviceId=bstr;
	m_nDeviceNum=index;

	Init();
	return true;
}

bool CKinect::Init()
{
	HRESULT hr;  
	//NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX
	hr=m_pNuiSensor->NuiInitialize(NUI_INITIALIZE_FLAG_USES_COLOR | NUI_INITIALIZE_FLAG_USES_DEPTH | NUI_INITIALIZE_FLAG_USES_SKELETON);

	m_hNextColorFrameEvent= CreateEvent( NULL, TRUE, FALSE, NULL );
	m_hColorStreamHandle= NULL; //保存彩色图像数据流的句柄，用以提取数据

	m_hNextDepthFrameEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
	m_hDepthStreamHandle = NULL; //保存深度像数据流的句柄，用以提取数据

	m_hNextSkeletonEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
	hr=m_pNuiSensor->NuiSkeletonTrackingEnable(m_hNextSkeletonEvent, NUI_SKELETON_TRACKING_FLAG_ENABLE_SEATED_SUPPORT);
	hr=m_pNuiSensor->NuiImageStreamOpen(NUI_IMAGE_TYPE_COLOR, NUI_IMAGE_RESOLUTION_640x480,0, 2, m_hNextColorFrameEvent, &m_hColorStreamHandle);
	//open an image stream
	hr=m_pNuiSensor->NuiImageStreamOpen( NUI_IMAGE_TYPE_DEPTH, NUI_IMAGE_RESOLUTION_640x480,0, 2, m_hNextDepthFrameEvent, &m_hDepthStreamHandle);

	hr=m_pNuiSensor->NuiImageStreamSetImageFrameFlags(m_hDepthStreamHandle,0);//设置默认模式,此型号只有远距离模式


	
	return true;
}

void CKinect::Shutdown()
{
	m_pNuiSensor->NuiShutdown();
}

void CKinect::GrabImage(UINT bSave)
{
	HRESULT hr;
	if (bSave==0)                  //
	{
		if (WaitForSingleObject(m_hNextColorFrameEvent,200)==0)
		{
			hr = m_pNuiSensor->NuiImageStreamGetNextFrame(m_hColorStreamHandle, 0, &m_ImageFrame_color);
			if (FAILED(hr))
				return;
			m_pTextureColor = m_ImageFrame_color.pFrameTexture;            
			m_pTextureColor->LockRect(0, &m_LockedRectColor, NULL, 0);
			if (m_LockedRectColor.Pitch != 0)
			{
				//m_pDrawColor->Draw(static_cast<BYTE *>(m_LockedRectColor.pBits), m_LockedRectColor.size);
				memcpy(m_pRightView->ColorByte,static_cast<BYTE *>(m_LockedRectColor.pBits),m_LockedRectColor.size);
				m_pRightView->ColorSize=m_LockedRectColor.size;
			}
			m_pTextureColor->UnlockRect(0);
			m_pNuiSensor->NuiImageStreamReleaseFrame(m_hColorStreamHandle, &m_ImageFrame_color);
		}
		else
		{
			/*AfxMessageBox(_T("未能等到相机返回的数据！"));*/
			//m_pNuiSensor[m_ShowID]->NuiShutdown();
			//m_pNuiSensor[m_ShowID]->Release();
			//hr = NuiCreateSensorByIndex(0, &m_pNuiSensor[m_ShowID]);
			//CreateFirstConnected();
			//InitKinect(m_ShowID);
		}
	}
	else
	{	
		memset(m_PointsBuffer,0,sizeof(float)*640*480*4);
		for (int j=0;j<1;j++)
		{
			//处理颜色部分
			if (WaitForSingleObject(m_hNextColorFrameEvent, 200)==0)
			{
				GetColorData(j);
			}
			//处理深度部分
			if (WaitForSingleObject(m_hNextDepthFrameEvent,200)==0)
			{
				//程序进入不到这里
				GetDepthData(j);
			}
		}
		
	}
}

void CKinect::GetColorData(int getcount)
{
	HRESULT hr;
	hr = m_pNuiSensor->NuiImageStreamGetNextFrame(m_hColorStreamHandle, 0, &m_ImageFrame_color);
	if (FAILED(hr))
	{
		goto ReleaseFrameColor;
	}
	m_pTextureColor =m_ImageFrame_color.pFrameTexture;
	hr = m_pTextureColor->LockRect(0, &m_LockedRectColor, NULL, 0);
	if (FAILED(hr))
	{
		m_pTextureColor->UnlockRect(0);
		goto ReleaseFrameColor;
	}
	/*hr = SaveBitmapToFile(static_cast<BYTE *>(m_LockedRectColor.pBits), 640, 480, 32, _T("../"));*/
	if (m_LockedRectColor.Pitch != 0)
	{
		//m_pDrawColor->Draw(static_cast<BYTE *>(m_LockedRectColor.pBits), m_LockedRectColor.size);
		memcpy(m_pRightView->ColorByte,static_cast<BYTE *>(m_LockedRectColor.pBits),m_LockedRectColor.size);
		m_pRightView->ColorSize=m_LockedRectColor.size;
	}
	m_pTextureColor->UnlockRect(0);
ReleaseFrameColor:
	// Release the frame
	m_pNuiSensor->NuiImageStreamReleaseFrame(m_hColorStreamHandle, &m_ImageFrame_color);
}

void CKinect::GetDepthData(int getcount)
{
	//add
	getcount = 1;

	HRESULT hr;
	BOOL nearMode=0;
	hr = m_pNuiSensor->NuiImageStreamGetNextFrame(m_hDepthStreamHandle, 0, &m_ImageFrame_depth);
	//add
	if (FAILED(hr))
	{
		goto ReleaseFrame;
	}
	hr = m_pNuiSensor->NuiImageFrameGetDepthImagePixelFrameTexture(
		m_hDepthStreamHandle, &m_ImageFrame_depth, &nearMode, &pTextureDepth1);	
	if (FAILED(hr))//add
	{
		goto ReleaseFrame;
	}

	NUI_LOCKED_RECT LockedRect1;
	hr = pTextureDepth1->LockRect(0, &LockedRect1, NULL, 0);
	if (FAILED(hr))
	{
		goto ReleaseFrame;
	}
	NUI_DEPTH_IMAGE_PIXEL * pBufferRun1 = reinterpret_cast<NUI_DEPTH_IMAGE_PIXEL *>(LockedRect1.pBits);

	INuiCoordinateMapper* pMapper;
	m_pNuiSensor->NuiGetCoordinateMapper(&pMapper);
	NUI_COLOR_IMAGE_POINT *ColorPoints = new NUI_COLOR_IMAGE_POINT[640 * 480];
	 //将深度数据影射到彩色图
	hr = pMapper->MapDepthFrameToColorFrame(NUI_IMAGE_RESOLUTION_640x480,640 * 480,
											(NUI_DEPTH_IMAGE_PIXEL*)LockedRect1.pBits,NUI_IMAGE_TYPE_COLOR,NUI_IMAGE_RESOLUTION_640x480,640 * 480, ColorPoints); 
	if (FAILED(hr))
	{
		pTextureDepth1->UnlockRect(0);
		goto ReleaseFrame;
	}

	byte *pColorRun = (byte*)(m_LockedRectColor.pBits);  
	//memcpy(m_pRightView->ColorByte_new,static_cast<BYTE *>(m_LockedRectColor.pBits),m_LockedRectColor.size);
	int points=0;
	int hRun=0 ;
	bool bInto = false;//仅测试用

	if (getcount==1)
	{
		for(int i=0;i<480;i++)           //保存点
		{
			for(int j=0;j<640;j++) 
			{
				int code=4*(ColorPoints[i*640+j].x+640*ColorPoints[i*640+j].y);  //对应的彩色图的哪一个点

				m_PointsBuffer[4*(i*640+j)+1]=pColorRun[code];
				m_PointsBuffer[4*(i*640+j)+2]=pColorRun[code+1];
				m_PointsBuffer[4*(i*640+j)+3]=pColorRun[code+2];

				USHORT realDepth=pBufferRun1->depth;
				if( realDepth> Mindepth && realDepth< Maxdepth)  //有效点
				{
					bInto = true;
					m_PointsBuffer[4*(i*640+j)]=realDepth;
				}
				pBufferRun1++;
			}
		}
	}
	else{}
	if(bInto==false)
		OutputDebugStringW(L"数据为空！请检查原因");
	delete  ColorPoints;
	pTextureDepth1->UnlockRect(0);
	pTextureDepth1->Release();
	//m_pNuiSensor->NuiImageStreamReleaseFrame(m_hDepthStreamHandle, &m_ImageFrame_depth);

ReleaseFrame:
	// Release the frame
	m_pNuiSensor->NuiImageStreamReleaseFrame(m_hDepthStreamHandle, &m_ImageFrame_depth);
}

void CKinect::Degree0()
{
	if (m_pNuiSensor!=NULL)
	{
		m_pNuiSensor->NuiCameraElevationSetAngle(0);
	}
}
void CKinect::Up()
{
	if (m_pNuiSensor!=NULL)
	{
		long degree;
		m_pNuiSensor->NuiCameraElevationGetAngle(&degree);
		m_pNuiSensor->NuiCameraElevationSetAngle(degree+3);
	}
}
void CKinect::Down()
{
	if (m_pNuiSensor!=NULL)
	{
		long degree;
		m_pNuiSensor->NuiCameraElevationGetAngle(&degree);
		m_pNuiSensor->NuiCameraElevationSetAngle(degree-3);
	}
}

void CKinect::rgb2hsv(int r,int g,int b,HSV& hsv)
{
	int max = r>g?(r>b?r:b):(g>b?g:b);
	int min = r<g?(r<b?r:b):(g<b?g:b);
	if(max == min)
		hsv.h = 0;
	else if(max==r&&g>=b)
		hsv.h = 60*(g-b)/(max - min) + 0;
	else if(max==r&&g<b)
		hsv.h = 60*(g-b)/(max - min) + 360;
	else if(max==g)
		hsv.h = 60*(b-r)/(max - min) + 120;
	else if(max==b)
		hsv.h = 60*(r-g)/(max - min) + 240;
	else
		return;
	if(max == 0)
		hsv.s = 0;
	else
		hsv.s = (max - min)/max;
	hsv.v = max;
}

HRESULT CKinect::SaveBitmapToFile(BYTE* pBitmapBits, LONG lWidth, LONG lHeight, WORD wBitsPerPixel, LPCWSTR lpszFilePath)
{
	DWORD dwByteCount = lWidth * lHeight * (wBitsPerPixel / 8);

	BITMAPINFOHEADER bmpInfoHeader = {0};

	bmpInfoHeader.biSize        = sizeof(BITMAPINFOHEADER);  // Size of the header
	bmpInfoHeader.biBitCount    = wBitsPerPixel;             // Bit count
	bmpInfoHeader.biCompression = BI_RGB;                    // Standard RGB, no compression
	bmpInfoHeader.biWidth       = lWidth;                    // Width in pixels
	bmpInfoHeader.biHeight      = -lHeight;                  // Height in pixels, negative indicates it's stored right-side-up
	bmpInfoHeader.biPlanes      = 1;                         // Default
	bmpInfoHeader.biSizeImage   = dwByteCount;               // Image size in bytes

	BITMAPFILEHEADER bfh = {0};

	bfh.bfType    = 0x4D42;                                           // 'M''B', indicates bitmap
	bfh.bfOffBits = bmpInfoHeader.biSize + sizeof(BITMAPFILEHEADER);  // Offset to the start of pixel data
	bfh.bfSize    = bfh.bfOffBits + bmpInfoHeader.biSizeImage;        // Size of image + headers

	// Create the file on disk to write to
	HANDLE hFile = CreateFileW(lpszFilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// Return if error opening file
	if (NULL == hFile) 
	{
		return E_ACCESSDENIED;
	}

	DWORD dwBytesWritten = 0;

	// Write the bitmap file header
	if ( !WriteFile(hFile, &bfh, sizeof(bfh), &dwBytesWritten, NULL) )
	{
		CloseHandle(hFile);
		return E_FAIL;
	}

	// Write the bitmap info header
	if ( !WriteFile(hFile, &bmpInfoHeader, sizeof(bmpInfoHeader), &dwBytesWritten, NULL) )
	{
		CloseHandle(hFile);
		return E_FAIL;
	}

	// Write the RGB Data
	if ( !WriteFile(hFile, pBitmapBits, bmpInfoHeader.biSizeImage, &dwBytesWritten, NULL) )
	{
		CloseHandle(hFile);
		return E_FAIL;
	}    

	// Close the file
	CloseHandle(hFile);
	return S_OK;
}
