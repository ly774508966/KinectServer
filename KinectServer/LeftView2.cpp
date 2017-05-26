// LeftView.cpp : 实现文件
//

#include "stdafx.h"
#include "KinectServer.h"
#include "LeftView2.h"
#include "MainFrm.h"

// CLeftView2
extern HGLRC g_pRC2;
extern CDC* g_pDC2;
IMPLEMENT_DYNCREATE(CLeftView2, CFormView)

CLeftView2::CLeftView2()
	: CFormView(CLeftView2::IDD)
{
	m_GLPixelIndex = 0;
	m_hRC = NULL;
	m_nShowTime = 0;
	m_bRotateShow = false;
	m_fDegreeDelta = 1;
}

CLeftView2::~CLeftView2()
{

}

void CLeftView2::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLeftView2, CFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


#ifdef _DEBUG
void CLeftView2::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CLeftView2::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG
BOOL CLeftView2::PreCreateWindow(CREATESTRUCT& cs)
{
	// system: 在此添加专用代码和/或调用基类
	cs.style |=	  WS_CLIPSIBLINGS			//创建子窗口使用的Windows风格，用于重绘时剪裁其他子窗口所覆盖的区域
		| WS_CLIPCHILDREN;			//创建父窗口使用的Windows风格，用于重绘时裁剪子窗口所覆盖的区域
	return CFormView::PreCreateWindow(cs);
}

void CLeftView2::OnDraw(CDC* pDC)
{
	// system: 在此添加专用代码和/或调用基类
	CKinectServerDoc* pDoc = (CKinectServerDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	wglMakeCurrent(g_pDC2->GetSafeHdc(),g_pRC2);
	CPaintDC dc(this);
	this->DrawGL();
	SwapBuffers(dc.m_hDC);
	wglMakeCurrent(g_pDC2->GetSafeHdc(),NULL);
}
int CLeftView2::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	//HWND hWnd = this->GetSafeHwnd();	//得到一个窗口对象（CWnd的派生对象）指针的句柄（HWND）  
	//HDC hDC = ::GetDC(hWnd);	//GetDC该函数检索一指定窗口的客户区域或整个屏幕的显示设备上下文环境的句柄,
	//if(this->SetWindowPixelFormat(hDC)==FALSE)	//设置像素格式
	//	return 0;
	//if(this->CreateViewGLContext(hDC)==FALSE)	//创建RC并选为所用
	//	return 0;
	//if(!this->InitGL())			//初始化openGL
	//	return 0;
	g_pDC2 = new CClientDC(this);
	PIXELFORMATDESCRIPTOR pixelDesc=
    {
        sizeof(PIXELFORMATDESCRIPTOR),           //nSize结构长度
        1,                                       //nVersion结构版本
        PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL| 
        PFD_DOUBLEBUFFER|PFD_SUPPORT_GDI,        //dwFlags告诉OpenGL如何处理像素
        PFD_TYPE_RGBA,  //iPixelType,颜色模式，包括两种PFD_TYPE_RGBA意味着每一位(bit)组代表着rgb各分量的值。PFD_TYPE_COLORINDEX意味着每一位组代表着在彩色查找表中的索引值
        24,   //cColorBits定义了指定一个颜色的位数。对RGBA来说，位数是在颜色中红、绿、蓝各分量所占的位数。对颜色的索引值来说，指的是表中的颜色数。
        0,0,0,0,0,0,  //cRedBits、cRedShifts、cGreenBits、cGreenShifts、cBlueBits、cBlueShifts用,基本不被采用，一般置0
        0,                                       //cAlphaBits,RGB颜色缓存中Alpha的位数                            
        0,                                 //cAlphaShift，已经不被采用，置0                   
        0,                                       //cAcuumBits累计缓存的位数
        0,0,0,0,                                 //cAcuumRedBits/cAcuumGreenBits/cAcuumBlueBits/cAcuumAlphaBits,基本不被采用，置0
        32,                                      //cDepthBits深度缓存的位数
        0,                                       //cStencilBits,模板缓存的位数
        0,                                       //cAuxBuffers，辅助缓存的位数，一般置0
        PFD_MAIN_PLANE,                          //iLayerType,说明层面的类型，可忽略置0，是早期的版本，包括
        0,0,0,0                                  //bReserved,dwLayerMask,dwVisibleMask,dwDamageMask,必须置0
    };
	m_GLPixelIndex = ChoosePixelFormat(g_pDC2->GetSafeHdc(),&pixelDesc);//选择最相近的像素格式
	if(m_GLPixelIndex==0)
	{
		this->m_GLPixelIndex = 1;//默认的像素格式
	}
	if(DescribePixelFormat(g_pDC2->GetSafeHdc(),m_GLPixelIndex,sizeof(PIXELFORMATDESCRIPTOR),&pixelDesc)==0)
	{
		return FALSE;
	}
	if(SetPixelFormat(g_pDC2->GetSafeHdc(),m_GLPixelIndex,&pixelDesc)==FALSE)
	{
		return FALSE;
	}
	if(!InitGL())			//初始化openGL
		return 0;
	g_pRC2 = wglCreateContext(g_pDC2->GetSafeHdc());
	return 0;
}
void CLeftView2::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// system: 在此处添加消息处理程序代码
    /*
    OnSize通过glViewport(0, 0, width, height)定义了视口和视口坐标。
    glViewport的第一、二个参数是视口左下角的像素坐标，第三、四个参数是视口的宽度和高度。

    OnSize中的glMatrixMode是用来设置矩阵模式的，它有三个选项：GL_MODELVIEW、GL_PROJECTION、 GL_TEXTURE。
    GL_MODELVIEW表示从实体坐标系转到人眼坐标系。
    GL_PROJECTION表示从人眼坐标系转到剪裁坐标系。
    GL_TEXTURE表示从定义纹理的坐标系到粘贴纹理的坐标系的变换。

    glLoadIdentity初始化工程矩阵(project matrix)
    gluOrtho2D把工程矩阵设置成显示一个二维直角显示区域。
    */
    GLsizei width,height;
    width = cx;
    height = cy;
    if (height==0)                                        // Prevent A Divide By Zero By
    {
        height=1;                                        // Making Height Equal One
    }
	wglMakeCurrent(g_pDC2->GetSafeHdc(),g_pRC2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	// Calculate The Aspect Ratio Of The Window
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);//透视投影
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glViewport(0,0,width,height);
	wglMakeCurrent(NULL,NULL);
}
BOOL CLeftView2::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	return CFormView::OnEraseBkgnd(pDC);
}
void CLeftView2::OnDestroy()
{
	CFormView::OnDestroy();
	// system: 在此处添加消息处理程序代码
	if (wglGetCurrentContext()!=NULL)
	{
		wglMakeCurrent(NULL,NULL);
	}
	if (g_pRC2)
	{
		wglDeleteContext(g_pRC2);
		g_pRC2 = NULL;
	}
	if (g_pDC2)
	{
		delete g_pDC2;
		g_pDC2 = NULL;
	}
	//Destory();
}
void CLeftView2::ShowPoint(CString filename)
{
	ReadPoint(filename);
	Invalidate(FALSE);
}
void CLeftView2::OnRotate()
{
	m_nShowTime = 0;
	while (m_bRotateShow)
	{
		Invalidate(FALSE);
		m_nShowTime++;
		Sleep(1000);
	}
}
void CLeftView2::DrawGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Clear Screen And Depth Buffer
	
	glLoadIdentity();                                    // Reset The Current Modelview Matrix
	glClearColor(15/255.0,56/255.0,120/255.0,0.0);
	glTranslatef(0.0f,0.0f,-3.0f);						//物体左移1.5,向内移6,相当于移动镜头一样，让物体进入镜头中
	CRect rect;
	GetClientRect(&rect);
	GLfloat scale=0.9*0.001*GLfloat(rect.Height())/prBoxSize.y;
	glScalef(scale,scale,scale);

	glRotatef(m_fDegreeY,0.0f,1.0f,0.0f);
	m_fDegreeY += m_fDegreeDelta;
	if (m_fDegreeY>360.0)
	{
		m_fDegreeY -= 360.0;
	}
	
	glBegin(GL_POINTS);

	DrawAll();
// 
// 	//左后视图方向
// 	if (m_fDegreeY<=0&&m_fDegreeY>=-90)
// 	{
// 		DrawZ1();
// 		DrawZ0();
// 		DrawB1();
// 		DrawB0();
// 		DrawA1();
// 		DrawA0();		
// 	}
// 	//右后视图方向
// 	else if (m_fDegreeY>0&&m_fDegreeY<=90)
// 	{
// 		DrawZ1();
// 		DrawZ0();
// 		DrawA1();
// 		DrawA0();
// 		DrawB1();
// 		DrawB0();
// 	}
// 	//左前视图方向
// 	else if(m_fDegreeY>=-180&&m_fDegreeY<=-90)
// 	{
// 		DrawB1();
// 		DrawB0();
// 		DrawA1();
// 		DrawA0();
// 		DrawZ1();
// 		DrawZ0();
// 	}
// 	//右前视图方向，为90度到180度区间
// 	else
// 	{
// 		DrawA1();
// 		DrawA0();
// 		DrawB1();
// 		DrawB0();
// 		DrawZ1();
// 		DrawZ0();
// 	}            
	glEnd();
	glFlush();
}

void CLeftView2::ReadPointAll(CString sType)
{
	m_pPointsList.clear();
// 	m_pointsZ0_new.clear();
// 	m_pointsZ1_new.clear();
// 	m_pointsA0_new.clear();
// 	m_pointsA1_new.clear();
// 	m_pointsB0_new.clear();
// 	m_pointsB1_new.clear();
	
	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();

	ReadPoint(pFrm->m_sTargetPath + _T("all_new") + sType);

// 	ReadPoint(pFrm->m_sGetName + _T("Z0_new") + sType);
// 	ReadPoint(pFrm->m_sGetName + _T("Z1_new") + sType);
// 	ReadPoint(pFrm->m_sGetName + _T("A0_new") + sType);
// 	ReadPoint(pFrm->m_sGetName + _T("A1_new") + sType);
// 	ReadPoint(pFrm->m_sGetName + _T("B0_new") + sType);
// 	ReadPoint(pFrm->m_sGetName + _T("B1_new") + sType);

}

void CLeftView2::ReadPoint(CString filename)
{
	USES_CONVERSION;
	FILE *p_txt= fopen(W2A(filename),"r");
	if (p_txt == NULL)
	{
		fclose(p_txt);
		return ;
	}
	//////////////////////////////////////////////////////////////////////////
	//检索文件开头
	//   int nSize = sizeof('\n');
	TCHAR tHead ;
	int nBegin = 0;
	tHead = fgetc(p_txt);//   tHead = fgetc(p_txt);
	switch(tHead)
	{
	case EOF://
		nBegin = 0;
		break;
	case '!'://Catia
		//OnFileOpenCATIA(p_txt);
		return;
		// nBegin = 50;
		break;
	case '#': //Geomagic    
		nBegin = 30;
		break;
	default:
		nBegin = 0;
		break;
	}
	fseek(p_txt , nBegin , SEEK_SET);
	//检索文件开头
	//////////////////////////////////////////////////////////////////////////
	//检索文件结尾 是否有字符串标志
	fseek(p_txt ,-14L , SEEK_END);
	char  schar[14]="";
	fgets(schar , 13 , p_txt);
	schar[13] = ('\0');
	CString str;
	str.Format(_T("%s"),schar);
	int nEndCloud = str.Find(_T("cloud"));
	int nEnd = -1;
	if (nEndCloud == -1)
		nEnd = EOF;
	else if (nEndCloud != 6)
	{
		nEndCloud = nEndCloud - 20;
		nEnd = fseek(p_txt ,nEndCloud , SEEK_END);
	}

	//////////////////////////////////////////////////////////////////////////
	fseek(p_txt , nBegin , SEEK_SET);

	MY_POINT3D f_points;

	if (filename.Find(_T("all"))!=-1)
	{
		m_pPointsList.clear();//	POINT3D f_xyz;
		while (fscanf(p_txt,"%f %f %f\r\n",&f_points.x,&f_points.y,&f_points.z) != nEnd)
			m_pPointsList.push_back(f_points);
	}
	//if (filename.Find(_T("Z0"))!=-1)
	//{
	//	m_pointsZ0_new.clear();//	POINT3D f_xyz;
	//	while (fscanf(p_txt,"%f %f %f %f %f %f",&f_points.x,&f_points.y,&f_points.z,&f_points.r,&f_points.g,&f_points.b) != nEnd)
	//		m_pointsZ0_new.push_back(f_points);
	//}
	//if (filename.Find(_T("Z1"))!=-1)
	//{
	//	m_pointsZ1_new.clear();//	POINT3D f_xyz;
	//	while (fscanf(p_txt,"%f %f %f %f %f %f",&f_points.x,&f_points.y,&f_points.z,&f_points.r,&f_points.g,&f_points.b) != nEnd)
	//		m_pointsZ1_new.push_back(f_points);
	//}
	//if (filename.Find(_T("A0"))!=-1)
	//{
	//	m_pointsA0_new.clear();//	POINT3D f_xyz;
	//	while (fscanf(p_txt,"%f %f %f %f %f %f",&f_points.x,&f_points.y,&f_points.z,&f_points.r,&f_points.g,&f_points.b) != nEnd)
	//		m_pointsA0_new.push_back(f_points);
	//}
	//if (filename.Find(_T("A1"))!=-1)
	//{
	//	m_pointsA1_new.clear();//	POINT3D f_xyz;
	//	while (fscanf(p_txt,"%f %f %f %f %f %f",&f_points.x,&f_points.y,&f_points.z,&f_points.r,&f_points.g,&f_points.b) != nEnd)
	//		m_pointsA1_new.push_back(f_points);
	//}
	//if (filename.Find(_T("B0"))!=-1)
	//{
	//	m_pointsB0_new.clear();//	POINT3D f_xyz;
	//	while (fscanf(p_txt,"%f %f %f %f %f %f",&f_points.x,&f_points.y,&f_points.z,&f_points.r,&f_points.g,&f_points.b) != nEnd)
	//		m_pointsB0_new.push_back(f_points);
	//}
	//if (filename.Find(_T("B1"))!=-1)
	//{
	//	m_pointsB1_new.clear();//	POINT3D f_xyz;
	//	while (fscanf(p_txt,"%f %f %f %f %f %f",&f_points.x,&f_points.y,&f_points.z,&f_points.r,&f_points.g,&f_points.b) != nEnd)
	//		m_pointsB1_new.push_back(f_points);
	//}  
	fclose(p_txt);//	vector <POINT3D>::iterator pItVector1,pItVector2;//为字符数组定义游标iterator

}

bool CLeftView2::SetWindowPixelFormat(HDC hDC)
{
    PIXELFORMATDESCRIPTOR pixelDesc=
    {
        sizeof(PIXELFORMATDESCRIPTOR),           //nSize结构长度
        1,                                       //nVersion结构版本
        PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL| 
        PFD_DOUBLEBUFFER|PFD_SUPPORT_GDI,        //dwFlags告诉OpenGL如何处理像素
         /*
         wFlags能接收以下标志：
            PFD_DRAW_TO_WINDOW 使之能在窗口或者其他设备窗口画图；
            PFD_DRAW_TO_BITMAP 使之能在内存中的位图画图；
            PFD_SUPPORT_GDI 使之能调用GDI函数（注：如果指定了PFD_DOUBLEBUFFER，这个选项将无效）；
            PFD_SUPPORT_OpenGL 使之能调用OpenGL函数；
            PFD_GENERIC_FORMAT 假如这种象素格式由Windows GDI函数库或由第三方硬件设备驱动程序支持，则需指定这一项；
            PFD_NEED_PALETTE 告诉缓冲区是否需要调色板，本程序假设颜色是使用24或 32位色，并且不会覆盖调色板；
            PFD_NEED_SYSTEM_PALETTE 这个标志指明缓冲区是否把系统调色板当作它自身调色板的一部分；
            PFD_DOUBLEBUFFER 指明使用了双缓冲区（注：GDI不能在使用了双缓冲区的窗口中画图）；
            PFD_STEREO 指明左、右缓冲区是否按立体图像来组织。
                        PFD_SWAP_LAYER_BUFFERS
         */
        PFD_TYPE_RGBA,  //iPixelType,颜色模式，包括两种PFD_TYPE_RGBA意味着每一位(bit)组代表着rgb各分量的值。PFD_TYPE_COLORINDEX意味着每一位组代表着在彩色查找表中的索引值
        24,   //cColorBits定义了指定一个颜色的位数。对RGBA来说，位数是在颜色中红、绿、蓝各分量所占的位数。对颜色的索引值来说，指的是表中的颜色数。
        0,0,0,0,0,0,  //cRedBits、cRedShifts、cGreenBits、cGreenShifts、cBlueBits、cBlueShifts用,基本不被采用，一般置0
                  //cRedBits、cGreenBits、cBlueBits用来表明各相应分量所使用的位数。
                      //cRedShift、cGreenShift、cBlue-Shift用来表明各分量从颜色开始的偏移量所占的位数。
        0,                                       //cAlphaBits,RGB颜色缓存中Alpha的位数                            
        0,                                 //cAlphaShift，已经不被采用，置0                   
        0,                                       //cAcuumBits累计缓存的位数
        0,0,0,0,                                 //cAcuumRedBits/cAcuumGreenBits/cAcuumBlueBits/cAcuumAlphaBits,基本不被采用，置0
        32,                                      //cDepthBits深度缓存的位数
        0,                                       //cStencilBits,模板缓存的位数
        0,                                       //cAuxBuffers，辅助缓存的位数，一般置0
        PFD_MAIN_PLANE,                          //iLayerType,说明层面的类型，可忽略置0，是早期的版本，包括
                                                 //PFD_MAIN_PLANE,PFD_OVER_LAY_PLANE,PFD_UNDERLAY_PLANE
        0,0,0,0                                  //bReserved,dwLayerMask,dwVisibleMask,dwDamageMask,必须置0
    };
    m_GLPixelIndex = ChoosePixelFormat(hDC,&pixelDesc);//选择最相近的像素格式
    /*
    ChoosePixelFormat接受两个参数：一个是hDc，另一个是一个指向PIXELFORMATDESCRIPTOR结构的指针&pixelDesc
    该函数返回此像素格式的索引值,如果返回0则表示失败。
    假如函数失败，我们只是把索引值设为1并用 DescribePixelFormat得到像素格式描述。
    假如你申请一个没得到支持的像素格式，则ChoosePixelFormat将会返回与你要求的像素格式最接近的一个值
    一旦我们得到一个像素格式的索引值和相应的描述，我们就可以调用SetPixelFormat设置像素格式，并且只需设置一次。
    */
    if(m_GLPixelIndex==0)
    {//选择失败
        this->m_GLPixelIndex = 1;//默认的像素格式
        //用默认的像素格式进行设置
        //
        if(DescribePixelFormat(hDC,this->m_GLPixelIndex,sizeof(PIXELFORMATDESCRIPTOR),&pixelDesc)==0)
        {
            return FALSE;
        }
    }
    if(SetPixelFormat(hDC,this->m_GLPixelIndex,&pixelDesc)==FALSE)
    {
        return FALSE;
    }
    return TRUE;
}
bool CLeftView2::CreateViewGLContext(HDC hDC)
{
    //WglCreateContext函数创建一个新的OpenGL渲染描述表(RC)
    //此描述表必须适用于绘制到由hdc返回的设备
    //这个渲染描述表将有和设备上下文(dc)一样的像素格式.
    this->m_hRC = wglCreateContext(hDC);//创建RC

    if(this->m_hRC==NULL)
    {//创建失败
        return FALSE;
    }

    /*
    wglMakeCurrent 函数设定OpenGL当前线程(线程相关性)的渲染环境。
    以后这个线程所有的OpenGL调用都是在这个hdc标识的设备上绘制。
    你也可以使用wglMakeCurrent 函数来改变调用线程的当前渲染环境
    使之不再是当前的渲染环境。
    */
    if(wglMakeCurrent(hDC,this->m_hRC)==FALSE)
    {//选为当前RC失败
        return FALSE;
    }
    return TRUE;
}
void CLeftView2::Destory()
{	
	::ReleaseDC(m_hWnd, m_hDC);

	// system: 在此处添加消息处理程序代码
	if(wglGetCurrentContext()!=NULL)
	{
		wglMakeCurrent(NULL,NULL);
	}
	if(this->m_hRC!=NULL)
	{
		wglDeleteContext(this->m_hRC);
		this->m_hRC = NULL;
	}
}
bool CLeftView2::InitGL(void)
{
	glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
	glClearColor(15/255.0,56/255.0,120/255.0,0.0);						// Black Background

	glEnable(GL_BLEND);									// Enables Depth Testing
	glBlendFunc(GL_SRC_ALPHA,GL_ZERO);
	glClearDepth(1.0f);                                  // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
	glEnable(GL_COLOR_MATERIAL);                            // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);                                // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);    // Really Nice Perspective Calculations
	return TRUE;                                        // Initialization Went OK
}
void CLeftView2::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// system: 在此添加消息处理程序代码和/或调用默认值
	switch(nChar)
	{
	case VK_RIGHT:   //右
		Invalidate(FALSE);
		break;
	case VK_ESCAPE:
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CLeftView2::DrawAll()
{
	int len = m_pPointsList.size();
	if (!m_pPointsList.empty())
	{
		vector<MY_POINT3D>::iterator pItPoint3d;
		for (pItPoint3d = m_pPointsList.begin() ; pItPoint3d != m_pPointsList.end()-1 ; ++pItPoint3d)
		{
			glColor3f(1.0,1.0,1.0);
			glVertex3f(pItPoint3d->x-prBoxCenter.x, pItPoint3d->y-prBoxCenter.y ,pItPoint3d->z-prBoxCenter.z);
		} 
	}  
}

void CLeftView2::DrawZ0()
{
	int len = m_pointsZ0_new.size();
	if (!m_pointsZ0_new.empty())
	{
		vector<POINT6D>::iterator pItPoint3d;
		for (pItPoint3d = m_pointsZ0_new.begin() ; pItPoint3d != m_pointsZ0_new.end()-1 ; ++pItPoint3d)
		{
			glColor3f(1.0,1.0,1.0);
			glVertex3f(pItPoint3d->x-prBoxCenter.x, pItPoint3d->y-prBoxCenter.y ,pItPoint3d->z-prBoxCenter.z);
		} 
	}  
}
void CLeftView2::DrawZ1()
{
	if (!m_pointsZ1_new.empty())
	{
		int len = m_pointsZ1_new.size();
		vector<POINT6D>::iterator pItPoint3d;
		for (pItPoint3d = m_pointsZ1_new.begin() ; pItPoint3d != m_pointsZ1_new.end()-1 ; ++pItPoint3d)
		{
			glColor3f(1.0,1.0,1.0);
			glVertex3f(pItPoint3d->x-prBoxCenter.x, pItPoint3d->y-prBoxCenter.y ,pItPoint3d->z-prBoxCenter.z);
		} 
	}  
}
void CLeftView2::DrawA0()
{
	if (!m_pointsA0_new.empty())
	{
		vector<POINT6D>::iterator pItPoint3d;
		for (pItPoint3d = m_pointsA0_new.begin() ; pItPoint3d != m_pointsA0_new.end()-1 ; ++pItPoint3d)
		{
			glColor3f(1.0,1.0,1.0);
			glVertex3f(pItPoint3d->x-prBoxCenter.x, pItPoint3d->y-prBoxCenter.y ,pItPoint3d->z-prBoxCenter.z);
		} 
	}  
}
void CLeftView2::DrawA1()
{
	if (!m_pointsA1_new.empty())
	{
		vector<POINT6D>::iterator pItPoint3d;
		for (pItPoint3d = m_pointsA1_new.begin() ; pItPoint3d != m_pointsA1_new.end()-1 ; ++pItPoint3d)
		{
			glColor3f(1.0,1.0,1.0);
			glVertex3f(pItPoint3d->x-prBoxCenter.x, pItPoint3d->y-prBoxCenter.y ,pItPoint3d->z-prBoxCenter.z);
		} 
	}  
}
void CLeftView2::DrawB0()
{
	if (!m_pointsB0_new.empty())
	{
		vector<POINT6D>::iterator pItPoint3d;
		for (pItPoint3d = m_pointsB0_new.begin() ; pItPoint3d != m_pointsB0_new.end()-1 ; ++pItPoint3d)
		{
			glColor3f(1.0,1.0,1.0);
			glVertex3f(pItPoint3d->x-prBoxCenter.x, pItPoint3d->y-prBoxCenter.y ,pItPoint3d->z-prBoxCenter.z);
		} 
	}  
}
void CLeftView2::DrawB1()
{
	if (!m_pointsB1_new.empty())
	{
		vector<POINT6D>::iterator pItPoint3d;
		for (pItPoint3d = m_pointsB1_new.begin() ; pItPoint3d != m_pointsB1_new.end()-1 ; ++pItPoint3d)
		{
			glColor3f(1.0,1.0,1.0);
			glVertex3f(pItPoint3d->x-prBoxCenter.x, pItPoint3d->y-prBoxCenter.y ,pItPoint3d->z-prBoxCenter.z);
		} 
	}  
}
