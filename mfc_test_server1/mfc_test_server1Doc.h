
// mfc_test_server1Doc.h: Cmfctestserver1Doc 클래스의 인터페이스
//


#pragma once
//소켓 클래스는 동적으로 생성하거나 파괴하기위한 포인터변수를 선언하기 위해
class CListenSocket;
class CDataSocket;


class Cmfctestserver1Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	Cmfctestserver1Doc() noexcept;
	DECLARE_DYNCREATE(Cmfctestserver1Doc)//클래스 동적선언

// 특성입니다.
public:

// 작업입니다.
	CListenSocket* m_pListenSocket;//소켓 포인터 멤버 변수 선언
	CDataSocket* m_pDataSocket;
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~Cmfctestserver1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

#ifdef SHARED_HANDLERS
private:
	CString m_strSearchContent;
	CString m_strThumbnailContent;
#endif // SHARED_HANDLERS
public:
	virtual void DeleteContents();
	void PrintMessage(LPCTSTR message);
	void ProcessAccept(int nErrorCode);
	void ProcessReceive(CDataSocket* pSocket, int nErrorCode);
	void ProcessClose(CDataSocket* pSocket, int nErrorCode);
};
