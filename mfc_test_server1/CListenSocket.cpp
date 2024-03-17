// CListenSocket.cpp: 구현 파일
//

#include "pch.h"
#include "mfc_test_server1.h"
#include "CListenSocket.h"

#include "mfc_test_server1Doc.h"

// CListenSocket

CListenSocket::CListenSocket(Cmfctestserver1Doc* pDoc)
{
	//멤버변수에 매개변수 집어넣기
	m_pDoc = pDoc;
}

CListenSocket::~CListenSocket()
{
}


// CListenSocket 멤버 함수


void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CSocket::OnAccept(nErrorCode);
	m_pDoc->ProcessAccept(nErrorCode);
}
