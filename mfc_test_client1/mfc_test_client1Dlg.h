﻿
// mfc_test_client1Dlg.h: 헤더 파일
//

#pragma once

#include "opencv2/opencv.hpp"

class CDataSocket;

using namespace cv;

// Cmfctestclient1Dlg 대화 상자
class Cmfctestclient1Dlg : public CDialogEx
{
// 생성입니다.
public:
	Cmfctestclient1Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	//포인터 멤버변수 선언
	CDataSocket* m_pDataSocket;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_TEST_CLIENT1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit;
	CIPAddressCtrl m_ipaddr;
	afx_msg void OnClickedConnect();
	afx_msg void OnClickedDisconnect();
	afx_msg void OnClickedSend();
private:
	CListBox list_box;
public:
	afx_msg void OnBnClickedSend2();
	CStatic m_picture;
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	VideoCapture* capture;
	Mat mat_frame;
	CImage cimage_mfc;
	afx_msg void OnBnClickedSend3();
};
