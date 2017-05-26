/************************************************************************/
/*                        ������ά���Ź�˾                              */
/*                           COpenGL.h                                  */
/*                        ��д�ˣ�����                                  */
/*                        ���ڣ�  �������������ʮ����                  */
/*                        ��;��  ��װOpenGL�йز�����������MFC         */                                                       
/************************************************************************/
/**/
#ifndef   __COPENGL_H__
#define   __COPENGL_H__
 
#include "MyClass.h"  //��ά�㡢��������ά�㡢��ɫ����ά��������
                      //�������    �� �� �� ת ����ֵ ��������
                      //�任����    ƽ��  ��X\Y\Z����һ����ת 
                      //            ������������ת
                      //            ������ת��Z��ƽ�з���
////////////////////////////////////////////////////////////////////////////
#include <wingdi.h>//win32 API ��ͼ�����
#pragma comment(lib,"gdi32.lib")//
////////////////////////////////////////////////////////////////////////////


class __declspec(dllexport) COpenGL        //Set OpenGL Condition in CView 
{
public:
////////////////////////////////////////////////////////////////////////////////
	//�����ͼ����mouse view operator   
	//����     �� �� �� ����button - left middle right wheel   
	//������   ���� �ſ� ˫�� �ƶ� ת�� operator - down  up  d-down  move  
	void OnRButtonUp(UINT nFlags, CPoint point);
	void OnRButtonDown(UINT nFlags, CPoint point);
	void OnRButtonDblClk(UINT nFlags, CPoint point);
	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnMButtonUp(UINT nFlags, CPoint point);
	void OnMButtonDown(UINT nFlags, CPoint point);
	void OnMButtonDblClk(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonDblClk(UINT nFlags, CPoint point);	

////////////////////////////////////////////////////////////////////////////////////////////////////////
//  char ch  = 
	//  'l' or 'L' - Left View    
	//  'r' or 'R'  - Right View  
	//   other  -  one view
	void GetViewModelProjectMatrix(char  ch , GLint  Viewport[4], GLdouble Modelmatrix[16] , GLdouble Projmatrix[16]);//view model project matrix
	//��ȡ Viewport  �� ��ͼ����   Modelmatrix  �� ģ�;���   Projmatrix  �� ͶӰ����
	void GetRotate(char ch , GLdouble  Matrix[4][4]);//��ת����
	void SetRotate(char ch , GLdouble  Matrix[4][4]);//rotate matrix
	tagCVector GetScaling(char ch);//���ű���
	void SetScaling(char ch , tagCVector&  fScaling);//scaling
	tagCVector GetTranslate(char ch);//ƽ����
	void SetTranslate(char  ch , tagCVector&  fTranslate);//translate
	tagCVector GetRotateCenter(char ch);//��ת����
	void SetRotateCenter(char  ch , tagCVector&  fRotateCenter);// rotate center
//  char ch
////////////////////////////////////////////////////////////////////////////////////////////////////////	

////////////////////////////////////////////////////////////////////////////////////////////////////////
	void GetLookAtData(tagCVector& fEyePos, tagCVector& fAspectPos, tagCVector& fUpAspect);
	//�ӵ����� look view point    
	// fEyePos -�ӵ� viewpiont    fAspectPos - ��������viewbox center     fUpAspect -������� camera up aspect
	void SetLookAtData(tagCVector&  fEyePos , tagCVector&  fAspectPos , tagCVector&  fUpAspect);
	tagCVector GetPerspectiveProjectionData();
	//��ά͸��ͶӰ����
      //m_fPerspective.x - �Ƕ� angle  
	  //m_fPerspective.y - �����ӵ��������near position     Frustum 3D
	  //m_fPerspective.z - �����ӵ���Զ����far position      Frustum 3D
	void SetPerspectiveProjectionData(tagCVector&  fPerspective);//3D Perspective 
	                          //m_fPerspective;//3D Perspective Projection 
	                          //m_fPerspective.x - angle  
	                          //m_fPerspective.y - near position Frustum 3D
	                          //m_fPerspective.z - far position  Frustum 3D
	GLdouble GetOrthoScaleZAxis();//����ͶӰ  Z������Y�������
	void SetOrthoScaleZAxis(GLdouble& dOrthScale_Z);//3D Ortho   z axis  scale
	bool IsTwoView();//�ж��Ƿ��зִ���  CView::OnDraw(CDC *pDC) is or not two view	
	void SetTwoView(bool bBTwoView);//�����зִ������ set two view or not
	void GetBox(tagCVector&   fBoxCenter, tagCVector& fBoxSize);//���ݰ�Χ�� ���� ��߳�box   fBoxCenter  -  center point   fBoxSize  -  box size
	void SetBox(tagCVector&   fBoxCenter, tagCVector& fBoxSize);
	tagColor GetBfColor();//ǰ����ɫ
	void SetBfColor(tagColor& fBfColor);//before color
	tagColor GetBkColor();//������ɫ
	void SetBkColor(tagColor& fBkColor);//back color
	BYTE GetProjectionMode();//ͶӰģʽ
	void SetProjectionMode(BYTE bProjectionMode);//ͶӰģʽ
	                             //0 - Orthographic 2D Projection  
	                             //1 - Orthographic 3D Projection  default 
	                             //2 - 3D Perspective Projection  
	                             //3 - Frustum 3D Perspective Projection
///////////////////////////////////////////////////////////////////////////////////////////////////
	void OnDrawRight();//�зִ��� �Ҵ�������  CView::OnDraw(CDC *pDC) set right view projection data 
	void OnInitRenderOpenGL();//��ʼ����������  �����з��󴰿� CView::OnDraw(CDC *pDC)  one view and left view
	void OnInitUpdateData();//��ʼ��COpenGL�ڲ�����  CView::CView()
	void OnInitUpdatePartData();//��ʼ��COpenGL�ڲ����ֲ���  update part data
	void SwapBufferOpenGL();//˫���� CView::OnDraw(CDC *pDC)
	void OnSizeOpenGL(UINT nType, int cx, int cy);//���ô��ڴ�С  set view size CView::OnSize(UINT nType, int cx, int cy)
	bool OnDestroyOpenGL();//�ͷ�OpenGL��Դ destroy opengl rc	//CView::OnDestroy() 	//
	bool OnInitOpenGL(HWND hWnd);//��ȡWindows�ֱ� ��ʼ���������� get windows handle int  CView::OnCreate(LPCREATESTRUCT lpCreateStruct)  OnInitOpenGL(GetSafeHwnd())
	COpenGL();
    ~COpenGL();

protected:

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void OnMouseScalePart(CPoint point , CRect& pRect , tagCVector& fScaling , tagCVector& fTranslate);
	//�������ֲ��Ŵ�
	//scale part by select in rectangle  return fscaling  and fTranslate
	void OnMouseRotateZAxis(CPoint point,tagCVector& fRotateCenter, GLint  Viewport[4], GLdouble Modelmatrix[16] , GLdouble Projmatrix[16], GLdouble Matrix[][4]);
	//�������ƴ�ֱ����Ļ������ת	
	//rotate around fRotateCenter in screen  return  Matrix
	void OnMouseRotate(CPoint point,GLdouble Matrix[4][4]);
	//������������ת	
	//rotate by mouse move     
	void OnMouseTranslate(CPoint point,CSize& nSize,tagCVector& fScaling ,tagCVector& fTranslate);
	//����ƽ��    
	//translate view - size is nSize by mouse move  return fTranslate
	void OnMouseMoveTransform(UINT  nFlags , CPoint point);
	//����м��������б任	
	//transform by mouse middle
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void OnComputeProjectionParameter();//����ͶӰ���� compute project parameter (y,z) int m_fPerspective and m_fEyePos
	void OnMouseDownRect(CPoint point);//����зִ���  �ж���굥���������Ҵ���if view divide into parts  ,it jugdes mouse down in which view
	void OnDrawMiddle();//���з��� view divide into two  , draw middle rectangle
	void OnTransformOpenGL(char ch);//�任����  transform matrix translate rotate  get matrix
	void OnProjectionCOpenGL(GLint xGL, GLint yGL, GLsizei xGLWidth, GLsizei yGLHeight);
	//ͶӰ����  (xGL , yGL) - ���Ͻ��ӵ�    (xGLWidth , yGLHeight) - ��ͼ����������С
	//opengl projection set
	//(xGL , yGL) - view leftup point     (xGLWidth , yGLHeight) - view size
	void PrintString(const char *str);//������ά���� print 3d string
	void RasterFont();//��ʼ������string raster
	bool CreateCViewCOpenGLContext();//����OpenGL�豸��  create CView COpenGL Context
	bool SetWindowPixelFormat();//����Windows��������  set windows pixel format

protected:
///////////////////////////////////////////////////////////////////////////////////////////
/////COpenGL Data 
	HWND       m_hWnd;//windows handle  active
	HDC        m_hDC;//dc handle  about windows
	HGLRC      m_hRC;//rc handle

    CSize      m_nSize;//windows view size
    GLuint     m_nFont;// 3d font
	BYTE       m_bProjectionMode;//0 - Orthographic 2D Projection  
	                             //1 - Orthographic 3D Projection  
	                             //2 - 3D Perspective Projection  
	                             //3 - Frustum 3D Perspective Projection
    tagColor   m_fBkColor;// set opengl back color
	tagColor   m_fBfColor;// set opengl before color
	tagCVector m_fBoxSize;// box size half (length width height) x y z
	tagCVector m_fBoxCenter;// box center vertex
	GLdouble   m_dBoxMaxSize;// half length of max edge of Box
	bool       m_bBTwoView;//is or not two view   left and right  
	BYTE       m_bMouseLeftRight;//Left Button Down in Left View or Right View
                                 //0-no  1-Left View  2-Right View
///////////////////////////////////////////////////////////////////////////////////////
///projection data
	GLdouble   m_dOrthScale_Z;//Orthographic 3D Projection  z axis ratio    
	tagCVector m_fPerspective;//3D Perspective Projection 
	                          //m_fPerspective.x - angle  
	                          //m_fPerspective.y - near position Frustum 3D
	                          //m_fPerspective.z - far position  Frustum 3D
	
	tagCVector m_fEyePos;//3D Perspective Projection  Eye position
	tagCVector m_fAspectPos;////3D Perspective Projection  eye aspect position
	tagCVector m_fUpAspect;//3D Perspective Projection up aspect
/////////////////////////////////////////////////////////////////////////////////////////
////one view data
	tagCVector m_fRotateCenter;//set opengl rotate center 
	tagCVector m_fTranslate;//set opengl translate dxyz
	tagCVector m_fScaling;//m_fScaling (x,y,z)   on x y z axis scaling
    GLint      viewport[4];//view matrix
    GLdouble   modelmatrix[16],projmatrix[16];//model projection matrix
    GLdouble   matrix[4][4];//i - clos  j - rows 
	                        //rotate matrix all -left hand criterion	
/////////////////////////////////////////////////////////////////////////////////////////
////left view data
	tagCVector m_fLRotateCenter;//set left view opengl rotate center 
	tagCVector m_fLTranslate;//set left view opengl translate dxyz
	tagCVector m_fLScaling;//m_fLScaling (x,y,z)   on  left view x y z axis scaling
    GLint      lviewport[4];// left view matrix
    GLdouble   lmodelmatrix[16],lprojmatrix[16];// left view model projection matrix
    GLdouble   lmatrix[4][4];//i - clos  j - rows 
	                        //rotate matrix  left view -left hand criterion	
/////////////////////////////////////////////////////////////////////////////////////////
////right view data
	tagCVector m_fRRotateCenter;//set right view opengl rotate center 
	tagCVector m_fRTranslate;//set right view opengl translate dxyz
	tagCVector m_fRScaling;//m_fRScaling (x,y,z)   on  right view x y z axis scaling
    GLint      rviewport[4];// right view matrix
    GLdouble   rmodelmatrix[16],rprojmatrix[16];// right view model projection matrix
    GLdouble   rmatrix[4][4];//i - clos  j - rows 
	                        //rotate matrix  right view -left hand criterion
///////////////////////////////////////////////////////////////////////////////////
	CPoint     m_nMouseMovePos;// mouse move position
	CPoint     m_nMouseDownPos;// mouse down position
	
};

#endif