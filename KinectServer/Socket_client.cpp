// LData.cpp : LCell 类的实现

#include "stdafx.h"
#include "Socket_client.h"
#include "RightView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CClientSocket::CClientSocket()
{
	memset(m_Buff1,0,sizeof(m_Buff1));
	memset(m_Buff,0,sizeof(m_Buff));
	m_nReadCount=0;
	m_nLeftCount=1024*1024;
}

CClientSocket::~CClientSocket()
{
	
}

void CClientSocket::OnReceive(int nErrorCode)
{
	int n=0;
	if (m_nLeftCount<1024*1024)
		n = Receive(m_Buff1,m_nLeftCount);
	else
		n = Receive(m_Buff1,1024*1024);
	memcpy(m_Buff+m_nReadCount,m_Buff1,n);
	m_nReadCount += n;
	struct FARDATA fardata;
	memcpy(&fardata,m_Buff,sizeof(fardata));

	if(m_nReadCount < fardata.length+sizeof(fardata))
	{
		m_nLeftCount=fardata.length+sizeof(fardata)-m_nReadCount;
		return;
	}
	CString sName;
	sName.Format(_T("%s"),fardata.sName);
	//从Z0处传来的信息为：cmd=6,sName=***Z0,length正常
	m_pView->DoCmdPro(fardata.cmd,sName,fardata.length,m_Buff+sizeof(fardata));
	m_nReadCount = 0;
	m_nLeftCount=1024*1024;
	//CSocket::OnReceive(nErrorCode);
	//return;
}

void CClientSocket::SendCmd(FARDATA fardata,float *FileData)
{
	memcpy(m_Buff,&fardata,sizeof(fardata));
	memcpy(m_Buff+sizeof(fardata),FileData,fardata.length+1);
	Send(m_Buff,fardata.length+sizeof(fardata));
	//CSocket::OnSend(nErrorCode);
}

void CClientSocket::SendCmd(FARDATA fardata)
{
	memcpy(m_Buff,&fardata,sizeof(fardata));
	Send(m_Buff,sizeof(fardata));
	//CSocket::OnSend(nErrorCode);
}

/*void CClientSocket::OnConnect(int nErrorCode)
{
	//0   The function executed successfully.
	/*if (0 != nErrorCode)
	{
		AfxMessageBox("通信连接失败！");
		Close();
		/*switch( nErrorCode )
		{
		case WSAEADDRINUSE: 
			AfxMessageBox("The specified address is already in use.\n");
			break;
		case WSAEADDRNOTAVAIL: 
			AfxMessageBox("The specified address is not available from the local machine.\n");
			break;
		case WSAEAFNOSUPPORT: 
			AfxMessageBox("Addresses in the specified family cannot be used with this socket.\n");
			break;
		case WSAECONNREFUSED: 
			AfxMessageBox("The attempt to connect was forcefully rejected.\n");
			break;
		case WSAEDESTADDRREQ: 
			AfxMessageBox("A destination address is required.\n");
			break;
		case WSAEFAULT: 
			AfxMessageBox("The lpSockAddrLen argument is incorrect.\n");
			break;
		case WSAEINVAL: 
			AfxMessageBox("The socket is already bound to an address.\n");
			break;
		case WSAEISCONN: 
			AfxMessageBox("The socket is already connected.\n");
			break;
		case WSAEMFILE: 
			AfxMessageBox("No more file descriptors are available.\n");
			break;
		case WSAENETUNREACH: 
			AfxMessageBox("The network cannot be reached from this host at this time.\n");
			break;
		case WSAENOBUFS: 
			AfxMessageBox("No buffer space is available. The socket cannot be connected.\n");
			break;
		case WSAENOTCONN: 
			AfxMessageBox("The socket is not connected.\n");
			break;
		case WSAENOTSOCK: 
			AfxMessageBox("The descriptor is a file, not a socket.\n");
			break;
		case WSAETIMEDOUT: 
			AfxMessageBox("The attempt to connect timed out without establishing a connection. \n");
			break;
		default:
			TCHAR szError[256];
			wsprintf(szError, "OnConnect error: %d", nErrorCode);
			AfxMessageBox(szError);
			break;
		}
	}
	CAsyncSocket::OnConnect(nErrorCode);
}*/