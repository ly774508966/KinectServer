// MyEdit.cpp : ʵ���ļ�
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



// CMyEdit ��Ϣ�������




void CMyEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// system: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CEdit::OnChar(nChar, nRepCnt, nFlags);
}
