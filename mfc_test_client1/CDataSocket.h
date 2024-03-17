#pragma once

// CDataSocket 명령 대상

class Cmfctestclient1Dlg;//클래스만들고

class CDataSocket : public CSocket
{
public:
	//생성자 바꿔주고
	CDataSocket(Cmfctestclient1Dlg* pDlg);
	virtual ~CDataSocket();
	//대화상자 클래스에 접근할 수 있는 변수선언
	Cmfctestclient1Dlg* m_pDlg;
};


