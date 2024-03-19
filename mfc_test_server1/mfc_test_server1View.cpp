
// mfc_test_server1View.cpp: Cmfctestserver1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "mfc_test_server1.h"
#endif

#include "mfc_test_server1Doc.h"
#include "mfc_test_server1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cmfctestserver1View

IMPLEMENT_DYNCREATE(Cmfctestserver1View, CEditView)

BEGIN_MESSAGE_MAP(Cmfctestserver1View, CEditView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

// Cmfctestserver1View 생성/소멸

Cmfctestserver1View::Cmfctestserver1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

Cmfctestserver1View::~Cmfctestserver1View()
{
}

BOOL Cmfctestserver1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// 자동 래핑을 사용합니다.

	return bPreCreated;
}


// Cmfctestserver1View 인쇄

BOOL Cmfctestserver1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 CEditView 준비
	return CEditView::OnPreparePrinting(pInfo);
}

void Cmfctestserver1View::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// 기본 CEditView 시작 인쇄
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void Cmfctestserver1View::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// 기본 CEditView 종료 인쇄
	CEditView::OnEndPrinting(pDC, pInfo);
}


// Cmfctestserver1View 진단

#ifdef _DEBUG
void Cmfctestserver1View::AssertValid() const
{
	CEditView::AssertValid();
}

void Cmfctestserver1View::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

Cmfctestserver1Doc* Cmfctestserver1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cmfctestserver1Doc)));
	return (Cmfctestserver1Doc*)m_pDocument;
}
#endif //_DEBUG
a

// Cmfctestserver1View 메시지 처리기

//만든 메소드
void Cmfctestserver1View::AddMessage(LPCTSTR message)
{
	// TODO: 여기에 구현 코드 추가.
	int len = GetWindowTextLength();
	//문자범위 시작, 끝 선택
	GetEditCtrl().SetSel(len, len);//문자 범위 선택
	GetEditCtrl().ReplaceSel(message);
}
