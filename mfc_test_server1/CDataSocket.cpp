// CDataSocket.cpp: 구현 파일
//

#include "pch.h"
#include "mfc_test_server1.h"
#include "CDataSocket.h"

#include "mfc_test_server1Doc.h"

// CDataSocket

CDataSocket::CDataSocket(Cmfctestserver1Doc* pDoc)
{
	m_pDoc = pDoc;
}

CDataSocket::~CDataSocket()
{
}


// CDataSocket 멤버 함수


void CDataSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 구현 코드 추가.
	CSocket::OnReceive(nErrorCode);
	m_pDoc->ProcessReceive(this, nErrorCode);
}


void CDataSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 구현 코드 추가.
	CSocket::OnClose(nErrorCode);
	m_pDoc->ProcessClose(this, nErrorCode);
}
