#pragma once

#include "CSocCom.h"
#define UM_ACCEPT WM_USER +1

// CSocServer 명령 대상

class CSocServer : public CSocket
{
public:
	CSocServer();
	virtual ~CSocServer();
	
	CSocCom m_socCom;//클라랑 연결되는 소켓
	CSocCom* GetAcceptSocCom();//통신소켓 리턴
	HWND m_hWnd;//메인 윈도우 핸들
	void CSocServer::Init(HWND hWnd);//소켓 클래스랑 메인 윈도우 연결

	virtual void OnAccept(int nErrorCode);
};


