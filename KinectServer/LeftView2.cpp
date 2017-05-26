// LeftView.cpp : ʵ���ļ�
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
	// system: �ڴ����ר�ô����/����û���
	cs.style |=	  WS_CLIPSIBLINGS			//�����Ӵ���ʹ�õ�Windows��������ػ�ʱ���������Ӵ��������ǵ�����
		| WS_CLIPCHILDREN;			//����������ʹ�õ�Windows��������ػ�ʱ�ü��Ӵ��������ǵ�����
	return CFormView::PreCreateWindow(cs);
}

void CLeftView2::OnDraw(CDC* pDC)
{
	// system: �ڴ����ר�ô����/����û���
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
	//HWND hWnd = this->GetSafeHwnd();	//�õ�һ�����ڶ���CWnd����������ָ��ľ����HWND��  
	//HDC hDC = ::GetDC(hWnd);	//GetDC�ú�������һָ�����ڵĿͻ������������Ļ����ʾ�豸�����Ļ����ľ��,
	//if(this->SetWindowPixelFormat(hDC)==FALSE)	//�������ظ�ʽ
	//	return 0;
	//if(this->CreateViewGLContext(hDC)==FALSE)	//����RC��ѡΪ����
	//	return 0;
	//if(!this->InitGL())			//��ʼ��openGL
	//	return 0;
	g_pDC2 = new CClientDC(this);
	PIXELFORMATDESCRIPTOR pixelDesc=
    {
        sizeof(PIXELFORMATDESCRIPTOR),           //nSize�ṹ����
        1,                                       //nVersion�ṹ�汾
        PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL| 
        PFD_DOUBLEBUFFER|PFD_SUPPORT_GDI,        //dwFlags����OpenGL��δ�������
        PFD_TYPE_RGBA,  //iPixelType,��ɫģʽ����������PFD_TYPE_RGBA��ζ��ÿһλ(bit)�������rgb��������ֵ��PFD_TYPE_COLORINDEX��ζ��ÿһλ��������ڲ�ɫ���ұ��е�����ֵ
        24,   //cColorBits������ָ��һ����ɫ��λ������RGBA��˵��λ��������ɫ�к졢�̡�����������ռ��λ��������ɫ������ֵ��˵��ָ���Ǳ��е���ɫ����
        0,0,0,0,0,0,  //cRedBits��cRedShifts��cGreenBits��cGreenShifts��cBlueBits��cBlueShifts��,�����������ã�һ����0
        0,                                       //cAlphaBits,RGB��ɫ������Alpha��λ��                            
        0,                                 //cAlphaShift���Ѿ��������ã���0                   
        0,                                       //cAcuumBits�ۼƻ����λ��
        0,0,0,0,                                 //cAcuumRedBits/cAcuumGreenBits/cAcuumBlueBits/cAcuumAlphaBits,�����������ã���0
        32,                                      //cDepthBits��Ȼ����λ��
        0,                                       //cStencilBits,ģ�建���λ��
        0,                                       //cAuxBuffers�����������λ����һ����0
        PFD_MAIN_PLANE,                          //iLayerType,˵����������ͣ��ɺ�����0�������ڵİ汾������
        0,0,0,0                                  //bReserved,dwLayerMask,dwVisibleMask,dwDamageMask,������0
    };
	m_GLPixelIndex = ChoosePixelFormat(g_pDC2->GetSafeHdc(),&pixelDesc);//ѡ������������ظ�ʽ
	if(m_GLPixelIndex==0)
	{
		this->m_GLPixelIndex = 1;//Ĭ�ϵ����ظ�ʽ
	}
	if(DescribePixelFormat(g_pDC2->GetSafeHdc(),m_GLPixelIndex,sizeof(PIXELFORMATDESCRIPTOR),&pixelDesc)==0)
	{
		return FALSE;
	}
	if(SetPixelFormat(g_pDC2->GetSafeHdc(),m_GLPixelIndex,&pixelDesc)==FALSE)
	{
		return FALSE;
	}
	if(!InitGL())			//��ʼ��openGL
		return 0;
	g_pRC2 = wglCreateContext(g_pDC2->GetSafeHdc());
	return 0;
}
void CLeftView2::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// system: �ڴ˴������Ϣ����������
    /*
    OnSizeͨ��glViewport(0, 0, width, height)�������ӿں��ӿ����ꡣ
    glViewport�ĵ�һ�������������ӿ����½ǵ��������꣬�������ĸ��������ӿڵĿ�Ⱥ͸߶ȡ�

    OnSize�е�glMatrixMode���������þ���ģʽ�ģ���������ѡ�GL_MODELVIEW��GL_PROJECTION�� GL_TEXTURE��
    GL_MODELVIEW��ʾ��ʵ������ϵת����������ϵ��
    GL_PROJECTION��ʾ����������ϵת����������ϵ��
    GL_TEXTURE��ʾ�Ӷ������������ϵ��ճ�����������ϵ�ı任��

    glLoadIdentity��ʼ�����̾���(project matrix)
    gluOrtho2D�ѹ��̾������ó���ʾһ����άֱ����ʾ����
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
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);//͸��ͶӰ
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
	// system: �ڴ˴������Ϣ����������
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
	glTranslatef(0.0f,0.0f,-3.0f);						//��������1.5,������6,�൱���ƶ���ͷһ������������뾵ͷ��
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
// 	//�����ͼ����
// 	if (m_fDegreeY<=0&&m_fDegreeY>=-90)
// 	{
// 		DrawZ1();
// 		DrawZ0();
// 		DrawB1();
// 		DrawB0();
// 		DrawA1();
// 		DrawA0();		
// 	}
// 	//�Һ���ͼ����
// 	else if (m_fDegreeY>0&&m_fDegreeY<=90)
// 	{
// 		DrawZ1();
// 		DrawZ0();
// 		DrawA1();
// 		DrawA0();
// 		DrawB1();
// 		DrawB0();
// 	}
// 	//��ǰ��ͼ����
// 	else if(m_fDegreeY>=-180&&m_fDegreeY<=-90)
// 	{
// 		DrawB1();
// 		DrawB0();
// 		DrawA1();
// 		DrawA0();
// 		DrawZ1();
// 		DrawZ0();
// 	}
// 	//��ǰ��ͼ����Ϊ90�ȵ�180������
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
	//�����ļ���ͷ
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
	//�����ļ���ͷ
	//////////////////////////////////////////////////////////////////////////
	//�����ļ���β �Ƿ����ַ�����־
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
	fclose(p_txt);//	vector <POINT3D>::iterator pItVector1,pItVector2;//Ϊ�ַ����鶨���α�iterator

}

bool CLeftView2::SetWindowPixelFormat(HDC hDC)
{
    PIXELFORMATDESCRIPTOR pixelDesc=
    {
        sizeof(PIXELFORMATDESCRIPTOR),           //nSize�ṹ����
        1,                                       //nVersion�ṹ�汾
        PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL| 
        PFD_DOUBLEBUFFER|PFD_SUPPORT_GDI,        //dwFlags����OpenGL��δ�������
         /*
         wFlags�ܽ������±�־��
            PFD_DRAW_TO_WINDOW ʹ֮���ڴ��ڻ��������豸���ڻ�ͼ��
            PFD_DRAW_TO_BITMAP ʹ֮�����ڴ��е�λͼ��ͼ��
            PFD_SUPPORT_GDI ʹ֮�ܵ���GDI������ע�����ָ����PFD_DOUBLEBUFFER�����ѡ���Ч����
            PFD_SUPPORT_OpenGL ʹ֮�ܵ���OpenGL������
            PFD_GENERIC_FORMAT �����������ظ�ʽ��Windows GDI��������ɵ�����Ӳ���豸��������֧�֣�����ָ����һ�
            PFD_NEED_PALETTE ���߻������Ƿ���Ҫ��ɫ�壬�����������ɫ��ʹ��24�� 32λɫ�����Ҳ��Ḳ�ǵ�ɫ�壻
            PFD_NEED_SYSTEM_PALETTE �����־ָ���������Ƿ��ϵͳ��ɫ�嵱���������ɫ���һ���֣�
            PFD_DOUBLEBUFFER ָ��ʹ����˫��������ע��GDI������ʹ����˫�������Ĵ����л�ͼ����
            PFD_STEREO ָ�����һ������Ƿ�����ͼ������֯��
                        PFD_SWAP_LAYER_BUFFERS
         */
        PFD_TYPE_RGBA,  //iPixelType,��ɫģʽ����������PFD_TYPE_RGBA��ζ��ÿһλ(bit)�������rgb��������ֵ��PFD_TYPE_COLORINDEX��ζ��ÿһλ��������ڲ�ɫ���ұ��е�����ֵ
        24,   //cColorBits������ָ��һ����ɫ��λ������RGBA��˵��λ��������ɫ�к졢�̡�����������ռ��λ��������ɫ������ֵ��˵��ָ���Ǳ��е���ɫ����
        0,0,0,0,0,0,  //cRedBits��cRedShifts��cGreenBits��cGreenShifts��cBlueBits��cBlueShifts��,�����������ã�һ����0
                  //cRedBits��cGreenBits��cBlueBits������������Ӧ������ʹ�õ�λ����
                      //cRedShift��cGreenShift��cBlue-Shift������������������ɫ��ʼ��ƫ������ռ��λ����
        0,                                       //cAlphaBits,RGB��ɫ������Alpha��λ��                            
        0,                                 //cAlphaShift���Ѿ��������ã���0                   
        0,                                       //cAcuumBits�ۼƻ����λ��
        0,0,0,0,                                 //cAcuumRedBits/cAcuumGreenBits/cAcuumBlueBits/cAcuumAlphaBits,�����������ã���0
        32,                                      //cDepthBits��Ȼ����λ��
        0,                                       //cStencilBits,ģ�建���λ��
        0,                                       //cAuxBuffers�����������λ����һ����0
        PFD_MAIN_PLANE,                          //iLayerType,˵����������ͣ��ɺ�����0�������ڵİ汾������
                                                 //PFD_MAIN_PLANE,PFD_OVER_LAY_PLANE,PFD_UNDERLAY_PLANE
        0,0,0,0                                  //bReserved,dwLayerMask,dwVisibleMask,dwDamageMask,������0
    };
    m_GLPixelIndex = ChoosePixelFormat(hDC,&pixelDesc);//ѡ������������ظ�ʽ
    /*
    ChoosePixelFormat��������������һ����hDc����һ����һ��ָ��PIXELFORMATDESCRIPTOR�ṹ��ָ��&pixelDesc
    �ú������ش����ظ�ʽ������ֵ,�������0���ʾʧ�ܡ�
    ���纯��ʧ�ܣ�����ֻ�ǰ�����ֵ��Ϊ1���� DescribePixelFormat�õ����ظ�ʽ������
    ����������һ��û�õ�֧�ֵ����ظ�ʽ����ChoosePixelFormat���᷵������Ҫ������ظ�ʽ��ӽ���һ��ֵ
    һ�����ǵõ�һ�����ظ�ʽ������ֵ����Ӧ�����������ǾͿ��Ե���SetPixelFormat�������ظ�ʽ������ֻ������һ�Ρ�
    */
    if(m_GLPixelIndex==0)
    {//ѡ��ʧ��
        this->m_GLPixelIndex = 1;//Ĭ�ϵ����ظ�ʽ
        //��Ĭ�ϵ����ظ�ʽ��������
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
    //WglCreateContext��������һ���µ�OpenGL��Ⱦ������(RC)
    //����������������ڻ��Ƶ���hdc���ص��豸
    //�����Ⱦ�������к��豸������(dc)һ�������ظ�ʽ.
    this->m_hRC = wglCreateContext(hDC);//����RC

    if(this->m_hRC==NULL)
    {//����ʧ��
        return FALSE;
    }

    /*
    wglMakeCurrent �����趨OpenGL��ǰ�߳�(�߳������)����Ⱦ������
    �Ժ�����߳����е�OpenGL���ö��������hdc��ʶ���豸�ϻ��ơ�
    ��Ҳ����ʹ��wglMakeCurrent �������ı�����̵߳ĵ�ǰ��Ⱦ����
    ʹ֮�����ǵ�ǰ����Ⱦ������
    */
    if(wglMakeCurrent(hDC,this->m_hRC)==FALSE)
    {//ѡΪ��ǰRCʧ��
        return FALSE;
    }
    return TRUE;
}
void CLeftView2::Destory()
{	
	::ReleaseDC(m_hWnd, m_hDC);

	// system: �ڴ˴������Ϣ����������
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
	// system: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nChar)
	{
	case VK_RIGHT:   //��
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
