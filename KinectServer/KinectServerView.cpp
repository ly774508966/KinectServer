
// KinectServerView.cpp : CKinectServerView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "KinectServer.h"
#endif

#include "KinectServerDoc.h"
#include "KinectServerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKinectServerView

IMPLEMENT_DYNCREATE(CKinectServerView, CView)

BEGIN_MESSAGE_MAP(CKinectServerView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CKinectServerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CKinectServerView 构造/析构

CKinectServerView::CKinectServerView()
{
	// system: 在此处添加构造代码

}

CKinectServerView::~CKinectServerView()
{
}

BOOL CKinectServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// system: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CKinectServerView 绘制

void CKinectServerView::OnDraw(CDC* /*pDC*/)
{
	CKinectServerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// system: 在此处为本机数据添加绘制代码
}


// CKinectServerView 打印


void CKinectServerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CKinectServerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CKinectServerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// system: 添加额外的打印前进行的初始化过程
}

void CKinectServerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// system: 添加打印后进行的清理过程
}

void CKinectServerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CKinectServerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CKinectServerView 诊断

#ifdef _DEBUG
void CKinectServerView::AssertValid() const
{
	CView::AssertValid();
}

void CKinectServerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKinectServerDoc* CKinectServerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKinectServerDoc)));
	return (CKinectServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CKinectServerView 消息处理程序
