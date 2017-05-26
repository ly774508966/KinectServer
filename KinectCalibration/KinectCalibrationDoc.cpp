
// KinectCalibrationDoc.cpp : CKinectCalibrationDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "KinectCalibration.h"
#endif

#include "KinectCalibrationDoc.h"
#include "KinectCalibrationView.h"
#include <propkey.h>
#include "ParamDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CKinectCalibrationDoc

IMPLEMENT_DYNCREATE(CKinectCalibrationDoc, CDocument)

BEGIN_MESSAGE_MAP(CKinectCalibrationDoc, CDocument)
	
	//ON_COMMAND(ID_SET_PARAM, &CKinectCalibrationDoc::OnSetParam)
END_MESSAGE_MAP()


// CKinectCalibrationDoc 构造/析构

CKinectCalibrationDoc::CKinectCalibrationDoc()
{

}

CKinectCalibrationDoc::~CKinectCalibrationDoc()
{
}

BOOL CKinectCalibrationDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// (SDI 文档将重用该文档)

	return TRUE;
}




// CKinectCalibrationDoc 序列化

void CKinectCalibrationDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{

	}
	else
	{

	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CKinectCalibrationDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CKinectCalibrationDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CKinectCalibrationDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CKinectCalibrationDoc 诊断

#ifdef _DEBUG
void CKinectCalibrationDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CKinectCalibrationDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CKinectCalibrationDoc 命令
CView* CKinectCalibrationDoc::GetView(CRuntimeClass *pViewClass)
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL ) 
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(pViewClass))
			return pView;
	}
	return NULL;
}

//void CKinectCalibrationDoc::OnFileOpen()
//{
//	CString sPathname;
//	CString sFileExt;//文件的扩展名
//
//	LPTSTR lpszFilter = _T("ASCII Data Files(*.txt , *TXT)|*.txt|ASCII Data Files(*.asc , *ASC)|*.asc|All Files(*.*)|*.*||");
//	CFileDialog p_dlg(true,_T(".txt"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT,lpszFilter,NULL);
//	pView = (CKinectCalibrationView*)GetView(RUNTIME_CLASS(CKinectCalibrationView));
//	if (p_dlg.DoModal() == IDOK)
//	{
//		POSITION pos = p_dlg.GetStartPosition();
//		while(pos!=NULL)
//		{
//			sPathname = p_dlg.GetPathName();
//			pView->ShowPoint(sPathname);
//		}
//		pView->InvalidateRect(NULL,FALSE);	
//	}
//	else 
//		return ;
//
//	//sFileExt.MakeLower();
//	//if (sFileExt!=_T("txt") && sFileExt!=_T("asc"))
//	//{
//	//	return ;
//	//}
//}

void CKinectCalibrationDoc::ViewReadSysInfo()
{
	//pView = (CKinectCalibrationView*)GetView(RUNTIME_CLASS(CKinectCalibrationView));
	//pView->ReadSysInfo();
}

void CKinectCalibrationDoc::ViewChangeMatrix(CString filename)
{
	//pView = (CKinectCalibrationView*)GetView(RUNTIME_CLASS(CKinectCalibrationView));
	//pView->ChangeMatrix(filename);
}
