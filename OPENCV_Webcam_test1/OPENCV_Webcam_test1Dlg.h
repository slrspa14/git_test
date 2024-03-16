
// OPENCV_Webcam_test1Dlg.h: 헤더 파일
//
#include "opencv2/opencv.hpp"
using namespace cv;
#pragma once


// COPENCVWebcamtest1Dlg 대화 상자
class COPENCVWebcamtest1Dlg : public CDialogEx
{
// 생성입니다.
public:
	COPENCVWebcamtest1Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENCV_WEBCAM_TEST1_DIALOG };
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
	CStatic m_picture;
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//멤버변수 추가
	VideoCapture* capture;
	Mat mat_frame;
	CImage cimage_mfc;
	afx_msg void OnBnClickedButton1();
};
