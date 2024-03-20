
// test_server_filesendDlg.h: 헤더 파일
//

#pragma once

#include "stdAfx.h"

// CtestserverfilesendDlg 대화 상자
class CtestserverfilesendDlg : public CDialogEx
{
// 생성입니다.
public:
	CtestserverfilesendDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CSocServer m_socServer;//서버용 소켓
	CSocCom* m_socCom;//통신용 소켓
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_SERVER_FILESEND_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//클라 접속 요청이 왔을 때 실행되는 메시지 함수
	afx_msg LPARAM OnAccept(UINT wParam, LPARAM lParam);
	//클라에서 오는 데이터 수신시 실행되는 함수
	afx_msg LPARAM OnReceive(UINT wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedIdcPicture();
	CListBox list_box;
	CEdit m_edit;
	CStatic m_strStatus;
};
