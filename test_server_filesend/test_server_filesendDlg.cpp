
// test_server_filesendDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "test_server_filesend.h"
#include "test_server_filesendDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtestserverfilesendDlg 대화 상자



CtestserverfilesendDlg::CtestserverfilesendDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST_SERVER_FILESEND_DIALOG, pParent)
	, m_strSend(_T(""))
	, m_strStatus(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestserverfilesendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, list_box);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	  DDX_Control(pDX, AFX_IDC_PICTURE, m_strStatus);
	  DDX_Control(pDX, IDC_STATIC_STATUS, m_strStatus);
	DDX_Control(pDX, IDC_EDIT_SEND, m_strSend);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_strStatus);
}

BEGIN_MESSAGE_MAP(CtestserverfilesendDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_ACCEPT, OnAccept)
	ON_MESSAGE(UM_RECEIVE, OnReceive)
	ON_BN_CLICKED(AFX_IDC_PICTURE, &CtestserverfilesendDlg::OnBnClickedIdcPicture)
END_MESSAGE_MAP()


// CtestserverfilesendDlg 메시지 처리기

BOOL CtestserverfilesendDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_socCom = NULL;
	m_socServer.Create(9191);//서버소켓생성
	m_socServer.Listen();//연결요청대기
	m_socServer.Init(this->m_hWnd);//소켓과 메인윈도우 연결
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CtestserverfilesendDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CtestserverfilesendDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtestserverfilesendDlg::OnBnClickedIdcPicture()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	wchar_t pTmp[256];
	CString strTmp;

	memset(pTmp, '\0', 256);
	wcscpy_s(pTmp, m_strSend);
	m_strSend = "";

	m_socCom->Send(pTmp, 256);

	strTmp.Format(_T("%s"), 256);
	int i = list_box.GetCount();
	list_box.InsertString(i, strTmp);
	UpdateData(FALSE);

}

LPARAM CtestserverfilesendDlg::OnAccept(UINT wParam, LPARAM lParam)
{
	//접속요청시
	m_strStatus = "접속성공";

	m_socCom = new CSocCom;
	m_socCom = m_socServer.GetAcceptSocCom();
	m_socCom->Init(this->m_hWnd);
	m_socCom->Send("접속성공", 256);

	UpdateData(FALSE);//textbox 값 바꾸기
	return TRUE;
}
LPARAM CtestserverfilesendDlg::OnReceive(UINT wParam, LPARAM lParam)
{
	char pTmp[256];
	CString strTmp;
	memset(pTmp, '\0', 256);

	m_socCom->Receive(pTmp, 256);
	strTmp.Format(_T("%s", pTmp));

	int i = list_box.GetCount();
	list_box.InsertString(i, strTmp);
	return TRUE;
}