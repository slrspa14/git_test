
// mfc_test_server1Doc.cpp: Cmfctestserver1Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "mfc_test_server1.h"
#endif

#include "mfc_test_server1Doc.h"
#include "CListenSocket.h"//헤더파일추가
#include "CDataSocket.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "mfc_test_server1View.h"//얘가 없었네
// Cmfctestserver1Doc

IMPLEMENT_DYNCREATE(Cmfctestserver1Doc, CDocument)

BEGIN_MESSAGE_MAP(Cmfctestserver1Doc, CDocument)
END_MESSAGE_MAP()


// Cmfctestserver1Doc 생성/소멸

Cmfctestserver1Doc::Cmfctestserver1Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	m_pListenSocket = NULL;//소켓 초기화
	m_pDataSocket = NULL; //초기화
}

Cmfctestserver1Doc::~Cmfctestserver1Doc()
{
	if (m_pListenSocket != NULL)
		delete m_pListenSocket;
	if (m_pDataSocket != NULL)
		delete m_pDataSocket;
}

BOOL Cmfctestserver1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	if (!m_viewList.IsEmpty())
	{
		reinterpret_cast<CEditView*>(m_viewList.GetHead())->SetWindowText(nullptr);
	}
	
	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.
	ASSERT(m_pListenSocket == NULL);//조건식 if랑 비슷 m_pListenSocket == NULL이 확실하다면 다음꺼실행
	m_pListenSocket = new CListenSocket(this);
	if (m_pListenSocket->Create(10000))//10000번 포트로 클라 접속 기다리고
	{
		if (m_pListenSocket->Listen())//접속됐으면
		{
			AfxMessageBox(_T("서버를 시작"), MB_ICONINFORMATION);
			return TRUE;
		}
	}
	AfxMessageBox(_T("이미 실행중인 서버가 있음")
		_T("\n프로그램 종료"), MB_ICONERROR);

	return TRUE;
}




// Cmfctestserver1Doc serialization

void Cmfctestserver1Doc::Serialize(CArchive& ar)
{
	// CEditView에는 모든 serialization을 처리하는 edit 컨트롤이 들어 있습니다.
	if (!m_viewList.IsEmpty())
	{
		reinterpret_cast<CEditView*>(m_viewList.GetHead())->SerializeRaw(ar);
	}
#ifdef SHARED_HANDLERS

	if (m_viewList.IsEmpty() && ar.IsLoading())
	{
		CFile* pFile = ar.GetFile();
		pFile->Seek(0, FILE_BEGIN);
		ULONGLONG nFileSizeBytes = pFile->GetLength();
		ULONGLONG nFileSizeChars = nFileSizeBytes/sizeof(TCHAR);
		LPTSTR lpszText = (LPTSTR)malloc(((size_t)nFileSizeChars + 1) * sizeof(TCHAR));
		if (lpszText != nullptr)
		{
			ar.Read(lpszText, (UINT)nFileSizeBytes);
			lpszText[nFileSizeChars] = '\0';
			m_strThumbnailContent = lpszText;
			m_strSearchContent = lpszText;
		}
	}
#endif
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void Cmfctestserver1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(m_strThumbnailContent, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void Cmfctestserver1Doc::InitializeSearchContent()
{
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 전체 텍스트 파일 콘텐츠를 검색 콘텐츠로 사용합니다.
	SetSearchContent(m_strSearchContent);
}

void Cmfctestserver1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Cmfctestserver1Doc 진단

#ifdef _DEBUG
void Cmfctestserver1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cmfctestserver1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cmfctestserver1Doc 명령

//객체 종료시 글씨 삭제용
void Cmfctestserver1Doc::DeleteContents()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//객체 종료가 아니라는거니깐
	if (m_pListenSocket != NULL)
	{
		delete m_pListenSocket;
		m_pListenSocket = NULL;
	}
	if (m_pDataSocket != NULL)
	{
		delete m_pDataSocket;
		m_pDataSocket = NULL;
	}
	CDocument::DeleteContents();
}

void Cmfctestserver1Doc::PrintMessage(LPCTSTR message)
{
	// TODO: 여기에 구현 코드 추가.
	CFrameWnd* pMainWnd = (CFrameWnd*)AfxGetMainWnd();//메인윈도우 객체 주소를 알아냄
	Cmfctestserver1View* pView = (Cmfctestserver1View*)pMainWnd->GetActiveView();
	//getactiveview 함수로 뷰 객체 주소를 알아낸다
	pView->AddMessage(message);//메시지함수호출
}


void Cmfctestserver1Doc::ProcessAccept(int nErrorCode)
{
	// TODO: 여기에 구현 코드 추가.
	CString PeerAddr;
	UINT PeerPort;
	CString str;

	ASSERT(nErrorCode == 0);
	if (m_pDataSocket == NULL)
	{
		m_pDataSocket = new CDataSocket(this);
		if (m_pListenSocket->Accept(*m_pDataSocket))
		{
			m_pDataSocket->GetPeerName(PeerAddr, PeerPort);
			str.Format(_T("###IP주소: %s, 포트번호: %d 127.0.0.1\r\n"), PeerAddr, PeerPort);
			PrintMessage(str);
		}
		else
		{
			delete m_pDataSocket;
			m_pDataSocket = NULL;
		}
	}
}

void Cmfctestserver1Doc::ProcessReceive(CDataSocket* pSocket, int nErrorCode)
{
	// TODO: 여기에 구현 코드 추가.
	TCHAR buf[256 + 1];//Type + char
	int nbytes = pSocket->Receive(buf, 256);
	buf[nbytes] = _T('\0');//널값설정해주고마지막
	PrintMessage(buf);
}


void Cmfctestserver1Doc::ProcessClose(CDataSocket* pSocket, int nErrorCode)
{
	// TODO: 여기에 구현 코드 추가.
	//소켓종료
	pSocket->Close();//소켓닫고
	delete m_pDataSocket; //할당된 메모리 해제
	m_pDataSocket = NULL;
	PrintMessage(_T("접속종료\r\n\r\n"));
}
