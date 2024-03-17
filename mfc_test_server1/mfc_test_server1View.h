
// mfc_test_server1View.h: Cmfctestserver1View 클래스의 인터페이스
//

#pragma once


class Cmfctestserver1View : public CEditView
{
protected: // serialization에서만 만들어집니다.
	Cmfctestserver1View() noexcept;
	DECLARE_DYNCREATE(Cmfctestserver1View)

// 특성입니다.
public:
	Cmfctestserver1Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~Cmfctestserver1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	void AddMessage(LPCTSTR message);
};

#ifndef _DEBUG  // mfc_test_server1View.cpp의 디버그 버전
inline Cmfctestserver1Doc* Cmfctestserver1View::GetDocument() const
   { return reinterpret_cast<Cmfctestserver1Doc*>(m_pDocument); }
#endif

