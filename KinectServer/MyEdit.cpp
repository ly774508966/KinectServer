// MyEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "KinectServer.h"
#include "MyEdit.h"


// CMyEdit

IMPLEMENT_DYNAMIC(CMyEdit, CEdit)

CMyEdit::CMyEdit()
{

}

CMyEdit::~CMyEdit()
{
}


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()



// CMyEdit 消息处理程序




void CMyEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// system: 在此添加消息处理程序代码和/或调用默认值

	CEdit::OnChar(nChar, nRepCnt, nFlags);
}
