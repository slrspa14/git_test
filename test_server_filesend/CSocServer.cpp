// CSocServer.cpp: 구현 파일
//

#include "pch.h"
#include "test_server_filesend.h"
#include "CSocServer.h"


// CSocServer

CSocServer::CSocServer()
{
}

CSocServer::~CSocServer()
{
}


// CSocServer 멤버 함수
void CSocServer::Init(HWND hWnd)
{
	m_hWnd = hWnd;
}

void CSocServer::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	Accept(m_socCom);//클라랑 서버 실제연결 소켓
	SendMessage(m_hWnd, UM_ACCEPT, 0, 0);
	CSocket::OnAccept(nErrorCode);
}
CSocCom* CSocServer::GetAcceptSocCom()
{
	//통신소켓 리턴, 반환되는 통신 소켓은 클라이언트와 연결됨
	return &m_socCom;
}
