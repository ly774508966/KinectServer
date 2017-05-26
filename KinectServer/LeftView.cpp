// LeftView.cpp : 实现文件
//

#include "stdafx.h"
#include "KinectServer.h"
#include "LeftView.h"
#include "MainFrm.h"





// CLeftView
extern HGLRC g_pRC;
extern CDC* g_pDC;
IMPLEMENT_DYNCREATE(CLeftView, CFormView)

	CLeftView::CLeftView()
	: CFormView(CLeftView::IDD)
{
	m_hRC = NULL;
	m_bFirstDraw = false;
}

CLeftView::~CLeftView()
{

}

void CLeftView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLeftView, CFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CLeftView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG
BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |=	  WS_CLIPSIBLINGS			//创建子窗口使用的Windows风格，用于重绘时剪裁其他子窗口所覆盖的区域
		| WS_CLIPCHILDREN;			//创建父窗口使用的Windows风格，用于重绘时裁剪子窗口所覆盖的区域
	return CFormView::PreCreateWindow(cs);
}

void CLeftView::OnDraw(CDC* pDC)
{
	CKinectServerDoc* pDoc = (CKinectServerDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (m_bFirstDraw==true)
	{
		DrawZ0(pDC);
		DrawZ1(pDC);
		DrawA0(pDC);
		DrawA1(pDC);
		DrawB0(pDC);
		DrawB1(pDC);
		m_bFirstDraw = false;
	}
}
int CLeftView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_nBytesWidth = 640*3;
	ZeroMemory(&bmi,sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = 640;
	bmi.bmiHeader.biHeight = -480;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biCompression = BI_RGB;
	return 0;
}
void CLeftView::OnSize(UINT nType, int cx, int cy)
{
	this->GetClientRect(&m_rect);
	CFormView::OnSize(nType, cx, cy);
}
BOOL CLeftView::OnEraseBkgnd(CDC* pDC)
{
	//return TRUE;
	return CFormView::OnEraseBkgnd(pDC);
}
void CLeftView::OnDestroy()
{
	CFormView::OnDestroy();
}

void CLeftView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// system: 在此添加消息处理程序代码和/或调用默认值
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


//TODO：从这里查看该怎么修改该逻辑
void CLeftView::DrawZ0(CDC* pDC)
{
	//int iBytesWidth = (640*24+31)/32*4;
	HANDLE hMem = GlobalAlloc(GMEM_ZEROINIT,640*480*3);
	BYTE* pImage = (BYTE*)GlobalAlloc(GMEM_ZEROINIT,m_nBytesWidth*480*3);

	for (int i=0;i<480;i++)
	{
		for (int j=0;j<640;j++)
		{
			*(pImage + i*m_nBytesWidth + j*3 + 0) = m_btRGB_Z0[3*(i*640+j)+0];
			*(pImage + i*m_nBytesWidth + j*3 + 1) = m_btRGB_Z0[3*(i*640+j)+1];
			*(pImage + i*m_nBytesWidth + j*3 + 2) = m_btRGB_Z0[3*(i*640+j)+2];
		}
	}
	//保存到Z0图像
	m_pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	CString	m_sPath;
	m_sPath = m_pMainFrame->m_sTargetPath;
	SaveBitmapToFile(pImage, 640, 480, 24, m_sPath +  _T("Z0.bmp"));

	SetStretchBltMode(pDC->GetSafeHdc(), STRETCH_HALFTONE);//添加这行代码可以实现无失真缩放
	StretchDIBits(pDC->GetSafeHdc(),0,0,m_rect.Width()/2,m_rect.Height()/3,
		0,0,640,480,pImage,&bmi,DIB_RGB_COLORS,SRCCOPY);
	GlobalUnlock(hMem);
	GlobalFree(hMem);
}

void CLeftView::DrawZ1(CDC* pDC)
{
	HANDLE hMem = GlobalAlloc(GMEM_ZEROINIT,640*480*3);
	BYTE* pImage = (BYTE*)GlobalAlloc(GMEM_ZEROINIT,m_nBytesWidth*480*3);

	for (int i=0;i<480;i++)
	{
		for (int j=0;j<640;j++)
		{
			*(pImage + i*m_nBytesWidth + j*3 + 0) = m_btRGB_Z1[3*(i*640+j)+0];
			*(pImage + i*m_nBytesWidth + j*3 + 1) = m_btRGB_Z1[3*(i*640+j)+1];
			*(pImage + i*m_nBytesWidth + j*3 + 2) = m_btRGB_Z1[3*(i*640+j)+2];
		}
	}
	//保存到Z1图像
	m_pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	CString	m_sPath;
	m_sPath = m_pMainFrame->m_sTargetPath;
	SaveBitmapToFile(pImage, 640, 480, 24, m_sPath +  _T("Z1.bmp"));

	SetStretchBltMode(pDC->GetSafeHdc(), STRETCH_HALFTONE);//添加这行代码可以实现无失真缩放
	StretchDIBits(pDC->GetSafeHdc(),m_rect.Width()/2,0,m_rect.Width()/2,m_rect.Height()/3,
		0,0,640,480,pImage,&bmi,DIB_RGB_COLORS,SRCCOPY);
	GlobalUnlock(hMem);
	GlobalFree(hMem);
}

void CLeftView::DrawA0(CDC* pDC)
{
	HANDLE hMem = GlobalAlloc(GMEM_ZEROINIT,640*480*3);
	BYTE* pImage = (BYTE*)GlobalAlloc(GMEM_ZEROINIT,m_nBytesWidth*480*3);

	for (int i=0;i<480;i++)
	{
		for (int j=0;j<640;j++)
		{
			*(pImage + i*m_nBytesWidth + j*3 + 0) = m_btRGB_A0[3*(i*640+j)+0];
			*(pImage + i*m_nBytesWidth + j*3 + 1) = m_btRGB_A0[3*(i*640+j)+1];
			*(pImage + i*m_nBytesWidth + j*3 + 2) = m_btRGB_A0[3*(i*640+j)+2];
		}
	}
	//保存到A0图像
	m_pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	CString	m_sPath;
	m_sPath = m_pMainFrame->m_sTargetPath;
	SaveBitmapToFile(pImage, 640, 480, 24, m_sPath +  _T("A0.bmp"));

	SetStretchBltMode(pDC->GetSafeHdc(), STRETCH_HALFTONE);//添加这行代码可以实现无失真缩放
	StretchDIBits(pDC->GetSafeHdc(),0,m_rect.Height()/3,m_rect.Width()/2,m_rect.Height()/3,
		0,0,640,480,pImage,&bmi,DIB_RGB_COLORS,SRCCOPY);
	GlobalUnlock(hMem);
	GlobalFree(hMem);
}

void CLeftView::DrawA1(CDC* pDC)
{
	HANDLE hMem = GlobalAlloc(GMEM_ZEROINIT,640*480*3);
	BYTE* pImage = (BYTE*)GlobalAlloc(GMEM_ZEROINIT,m_nBytesWidth*480*3);

	for (int i=0;i<480;i++)
	{
		for (int j=0;j<640;j++)
		{
			*(pImage + i*m_nBytesWidth + j*3 + 0) = m_btRGB_A1[3*(i*640+j)+0];
			*(pImage + i*m_nBytesWidth + j*3 + 1) = m_btRGB_A1[3*(i*640+j)+1];
			*(pImage + i*m_nBytesWidth + j*3 + 2) = m_btRGB_A1[3*(i*640+j)+2];
		}
	}
	//保存到A1图像
	m_pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	CString	m_sPath;
	m_sPath = m_pMainFrame->m_sTargetPath;
	SaveBitmapToFile(pImage, 640, 480, 24, m_sPath +  _T("A1.bmp"));

	SetStretchBltMode(pDC->GetSafeHdc(), STRETCH_HALFTONE);//添加这行代码可以实现无失真缩放
	StretchDIBits(pDC->GetSafeHdc(),m_rect.Width()/2,m_rect.Height()/3,m_rect.Width()/2,m_rect.Height()/3,
		0,0,640,480,pImage,&bmi,DIB_RGB_COLORS,SRCCOPY);
	GlobalUnlock(hMem);
	GlobalFree(hMem);
}

void CLeftView::DrawB0(CDC* pDC)
{
	HANDLE hMem = GlobalAlloc(GMEM_ZEROINIT,640*480*3);
	BYTE* pImage = (BYTE*)GlobalAlloc(GMEM_ZEROINIT,m_nBytesWidth*480*3);

	for (int i=0;i<480;i++)
	{
		for (int j=0;j<640;j++)
		{
			*(pImage + i*m_nBytesWidth + j*3 + 0) = m_btRGB_B0[3*(i*640+j)+0];
			*(pImage + i*m_nBytesWidth + j*3 + 1) = m_btRGB_B0[3*(i*640+j)+1];
			*(pImage + i*m_nBytesWidth + j*3 + 2) = m_btRGB_B0[3*(i*640+j)+2];
		}
	}
	//保存到B0图像
	m_pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	CString	m_sPath;
	m_sPath = m_pMainFrame->m_sTargetPath;
	SaveBitmapToFile(pImage, 640, 480, 24, m_sPath +  _T("B0.bmp"));

	SetStretchBltMode(pDC->GetSafeHdc(), STRETCH_HALFTONE);//添加这行代码可以实现无失真缩放
	StretchDIBits(pDC->GetSafeHdc(),0,m_rect.Height()/3*2,m_rect.Width()/2,m_rect.Height()/3,
		0,0,640,480,pImage,&bmi,DIB_RGB_COLORS,SRCCOPY);
	GlobalUnlock(hMem);
	GlobalFree(hMem);
}

void CLeftView::DrawB1(CDC* pDC)
{
	HANDLE hMem = GlobalAlloc(GMEM_ZEROINIT,640*480*3);
	BYTE* pImage = (BYTE*)GlobalAlloc(GMEM_ZEROINIT,m_nBytesWidth*480*3);

	for (int i=0;i<480;i++)
	{
		for (int j=0;j<640;j++)
		{
			*(pImage + i*m_nBytesWidth + j*3 + 0) = m_btRGB_B1[3*(i*640+j)+0];
			*(pImage + i*m_nBytesWidth + j*3 + 1) = m_btRGB_B1[3*(i*640+j)+1];
			*(pImage + i*m_nBytesWidth + j*3 + 2) = m_btRGB_B1[3*(i*640+j)+2];
		}
	}
	//保存到B1图像
	m_pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	CString	m_sPath;
	m_sPath = m_pMainFrame->m_sTargetPath;
	SaveBitmapToFile(pImage, 640, 480, 24, m_sPath +  _T("B1.bmp"));

	SetStretchBltMode(pDC->GetSafeHdc(), STRETCH_HALFTONE);//添加这行代码可以实现无失真缩放
	StretchDIBits(pDC->GetSafeHdc(),m_rect.Width()/2,m_rect.Height()/3*2,m_rect.Width()/2,m_rect.Height()/3,
		0,0,640,480,pImage,&bmi,DIB_RGB_COLORS,SRCCOPY);
	GlobalUnlock(hMem);
	GlobalFree(hMem);
}

HRESULT CLeftView::SaveBitmapToFile(BYTE* pBitmapBits, LONG lWidth, LONG lHeight, WORD wBitsPerPixel, LPCWSTR lpszFilePath)
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
