#pragma once

// CDataSocket 명령 대상

class Cmfctestserver1Doc;//클래스 생성

class CDataSocket : public CSocket
{
public:
	CDataSocket(Cmfctestserver1Doc* pDoc);
	virtual ~CDataSocket();

	Cmfctestserver1Doc* m_pDoc;
	void OnReceive(int nErrorCode);
	void OnClose(int nErrorCode);
};


