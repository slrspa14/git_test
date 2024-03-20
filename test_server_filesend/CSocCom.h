#pragma once

// CSocCom 명령 대상

#define UM_RECEIVE WM_USER+2//통신용 소켓

class CSocCom : public CSocket
{
public:
	CSocCom();
	virtual ~CSocCom();
	HWND m_hWnd;//메인 윈도우 핸들
	void CSocCom::Init(HWND hwnd);//소켓 클래스와 메인 윈도우를 연결시켜줌

	virtual void OnReceive(int nErrorCode);//데이터 도착 알려줌
};


