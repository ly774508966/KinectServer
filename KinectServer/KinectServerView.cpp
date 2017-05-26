
// KinectServerView.cpp : CKinectServerView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CKinectServerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CKinectServerView ����/����

CKinectServerView::CKinectServerView()
{
	// system: �ڴ˴���ӹ������

}

CKinectServerView::~CKinectServerView()
{
}

BOOL CKinectServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// system: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CKinectServerView ����

void CKinectServerView::OnDraw(CDC* /*pDC*/)
{
	CKinectServerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// system: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CKinectServerView ��ӡ


void CKinectServerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CKinectServerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CKinectServerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// system: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CKinectServerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// system: ��Ӵ�ӡ����е��������
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


// CKinectServerView ���

#ifdef _DEBUG
void CKinectServerView::AssertValid() const
{
	CView::AssertValid();
}

void CKinectServerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKinectServerDoc* CKinectServerView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKinectServerDoc)));
	return (CKinectServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CKinectServerView ��Ϣ�������
