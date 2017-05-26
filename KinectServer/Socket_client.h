#include <afxsock.h>
#pragma once

struct FARDATA
{
	UINT cmd;
	UINT length;
	char sName[100];
};
class CRightView;
class CClientSocket : public CSocket
//class CClientSocket : public CAsyncSocket
{
public:
	CClientSocket(); 
	~CClientSocket();

protected:
	CRightView*	m_pView;
	char				m_Buff[1024*1024*10];
	char				m_Buff1[1024*1024];
	UINT				m_nReadCount;
	UINT				m_nLeftCount;

public:
	virtual void OnReceive(int nErrorCode);
	//virtual void OnConnect(int nErrorCode);
	virtual void SendCmd(FARDATA fardata,float *FileData);
	virtual void SendCmd(FARDATA fardata);
	
	void SetLink(CRightView* pView)
	{
		m_pView=pView;
	};
};