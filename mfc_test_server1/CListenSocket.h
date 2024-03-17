#pragma once

// CListenSocket 명령 대상
//접근하려고
class Cmfctestserver1Doc;//클래스 생성

class CListenSocket : public CSocket
{
public:
	CListenSocket(Cmfctestserver1Doc* pDoc);//생성자 형태 변경;
	virtual ~CListenSocket();

	//도큐멘트 클래스에 접근가능한 *m_pDoc 멤버변수 선언
	Cmfctestserver1Doc* m_pDoc;
	virtual void OnAccept(int nErrorCode);
};


