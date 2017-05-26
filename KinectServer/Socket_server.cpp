#include "Stdafx.h"
#include "Resource.h"
//#include "../KinectDepthDoc.h"
#include "RightView.h"
#include "Socket_server.h"

CServerSocket  RecieveSocket[40];
int			   RecieveNum; 
CServerSocket::CServerSocket()
{
	readcount = 0;
	//m_bConnected = TRUE;
//	m_Buff=new char(1024*1024);
	memset(m_Buff,0,sizeof(m_Buff));
	memset(m_Buff1,0,sizeof(m_Buff1));
}
CServerSocket::~CServerSocket()
{
}
 
void CServerSocket::SendCmd(FARDATA fardata,char FileData[])
{
	memcpy(m_Buff,&fardata,sizeof(fardata));
	//memcpy(m_Buff+sizeof(fardata),FileData,sizeof(float)*640*480*3+1);
	Send(m_Buff,sizeof(fardata));
}
void CServerSocket::SendCmd(FARDATA fardata)
{
	memcpy(m_Buff,&fardata,sizeof(fardata));
	Send(m_Buff,sizeof(fardata));
}
void CServerSocket::OnReceive(int nErrorCode)
{
	int n = Receive(m_Buff1,1024*1024);
	memcpy(m_Buff+readcount,m_Buff1,n);
	readcount += n;
	FARDATA *fardata;
	fardata=new FARDATA;
	memcpy(fardata,m_Buff,sizeof(*fardata));
	if(readcount < sizeof(float)*640*480*4+sizeof(*fardata))    //一次数据总长度
		return;

	CString sname="";
	sname.Format("%s",fardata->sName);
	char* buff=m_Buff+sizeof(*fardata);
	//m_pView->PostMessage(WM_USER+10,(WPARAM) fardata,(LPARAM)m_Buff);
	m_pView->CmdProc(fardata->cmd,sname,640*480*4,buff);
	readcount = 0;
}

CListenSocket::CListenSocket(CRightView* pView)
{
	m_pView = pView;
}
CListenSocket::~CListenSocket()
{
}

void CListenSocket::OnAccept(int nErrorCode)
{
	int len = sizeof(m_ClientAddr);
	Accept(RecieveSocket[++RecieveNum]);
	RecieveSocket[RecieveNum].SetLink(m_pView,RecieveNum);
}

void CListenSocket::SendCmd(FARDATA fardata,char FileData[])
{
	for (int i=1;i<=RecieveNum;i++)
	{
		if (RecieveSocket[i])
			RecieveSocket[i].SendCmd(fardata,FileData);
	}
}
void CListenSocket::SendCmd(FARDATA fardata)
{
	for (int i=1;i<=RecieveNum;i++)
	{
		if (RecieveSocket[i])
			RecieveSocket[i].SendCmd(fardata);
	}
}