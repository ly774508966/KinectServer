#pragma once
#include <afxsock.h>		

class CRightView;
struct FARDATA
{
	UINT cmd;
	UINT UsePointNum;
	char sName[100];
};
class CServerSocket : public CAsyncSocket
{
public:
	CServerSocket();
	~CServerSocket();

	void SendCmd(FARDATA cmd,char FileData[]);
	void SendCmd(FARDATA cmd);
public:
	BOOL				m_bConnected;
	char				m_Buff[1024*1024*5];
	char				m_Buff1[1024*1024];
	UINT				readcount;
	CRightView*			m_pView;
	int m_nNum;

protected:
	virtual void OnReceive(int nErrorCode);
public:
	void SetLink(CRightView* pView,int num)
	{
		m_pView=pView;
		m_nNum=num;
	};
};

class CListenSocket : public CAsyncSocket
{
public:
	CListenSocket(CRightView* pView);
	~CListenSocket();

public:
	sockaddr_in			m_ClientAddr;
	CRightView*			m_pView;
protected:
	virtual void OnAccept(int nErrorCode);

public:
	void    SendCmd(FARDATA cmd,char FileData[]);
	void    SendCmd(FARDATA cmd);
};