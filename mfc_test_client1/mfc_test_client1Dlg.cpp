
// mfc_test_client1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "mfc_test_client1.h"
#include "mfc_test_client1Dlg.h"
#include "afxdialogex.h"

#include "CDataSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cmfctestclient1Dlg 대화 상자



Cmfctestclient1Dlg::Cmfctestclient1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_TEST_CLIENT1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cmfctestclient1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipaddr);
	//DDX_Control(pDX, IDC_CONNECT);
	DDX_Control(pDX, IDC_LIST1, list_box);
	DDX_Control(pDX, AFX_IDC_PICTURE, m_picture);
}

BEGIN_MESSAGE_MAP(Cmfctestclient1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, &Cmfctestclient1Dlg::OnClickedConnect)
	ON_BN_CLICKED(IDC_DISCONNECT, &Cmfctestclient1Dlg::OnClickedDisconnect)
	ON_BN_CLICKED(IDC_SEND, &Cmfctestclient1Dlg::OnClickedSend)
	ON_BN_CLICKED(IDC_SEND2, &Cmfctestclient1Dlg::OnBnClickedSend2)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SEND3, &Cmfctestclient1Dlg::OnBnClickedSend3)
END_MESSAGE_MAP()


// Cmfctestclient1Dlg 메시지 처리기

BOOL Cmfctestclient1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//초기화 무조건
	m_pDataSocket = NULL;
	m_ipaddr.SetWindowText(_T("127.0.0.1"));
	capture = new VideoCapture(0);

	if (!capture->isOpened())
	{
		MessageBox(_T("웹캠을 열수 없습니다. \n"));
	}
	//웹캠 크기를  320x240으로 지정    

	capture->set(CAP_PROP_FRAME_WIDTH, 320);
	capture->set(CAP_PROP_FRAME_HEIGHT, 240);
	SetTimer(1000, 30, NULL);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Cmfctestclient1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void Cmfctestclient1Dlg::OnPaint()
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
HCURSOR Cmfctestclient1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cmfctestclient1Dlg::OnClickedConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pDataSocket == NULL) 
	{
		m_pDataSocket = new CDataSocket(this);
		m_pDataSocket->Create();//소켓생성
		CString addr;
		m_ipaddr.GetWindowText(addr);//edit에 있는값 넣어주고
		if (m_pDataSocket->Connect(addr, 10000))//주소랑 포트가지고 접속
		{
			MessageBox(_T("서버 접속성공"), _T("알림"), MB_ICONINFORMATION);
			m_edit.SetFocus();
		}
		else
		{
			MessageBox(_T("서버 접속실패"), _T("알림"), MB_ICONERROR);
			delete m_pDataSocket; //메모리 해제해주고
			m_pDataSocket = NULL; //다시 NULL값으로
		}
	}
	else
	{
		MessageBox(_T("서버에 이미 접속중"), _T("알림"), MB_ICONINFORMATION);
		delete m_pDataSocket;
		m_pDataSocket = NULL;
	}
		
}


void Cmfctestclient1Dlg::OnClickedDisconnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pDataSocket == NULL)
	{
		MessageBox(_T("서버에 접속중인 상태가 아님"), _T("알림"), MB_ICONINFORMATION);
	}
	else
	{
		m_pDataSocket->Close();
		delete m_pDataSocket;//메모리 해제
		m_pDataSocket = NULL;
	}
}


void Cmfctestclient1Dlg::OnClickedSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pDataSocket == NULL)
	{
		MessageBox(_T("서버에 접송중인 상태가 아님"), _T("알림"), MB_ICONINFORMATION);
	}
	else
	{
		CString message;
		m_edit.GetWindowText(message);//edit 박스에 있는거 넣어주고
		message += _T("\r\n");
		m_pDataSocket->Send((LPCTSTR)message,
			(message.GetLength() + 1) * sizeof(TCHAR));
		m_edit.SetWindowText(_T(""));//박스 지워주고
		m_edit.SetFocus();//키보드 마우스 입력 포커스?
	}
}



void Cmfctestclient1Dlg::OnBnClickedSend2()//파일전송
{
	CFileDialog dlg(TRUE); // TRUE = 파일을 열기 위한 대화 상자 생성
	if (dlg.DoModal() == IDOK) //사용자가 OK 버튼 눌렀을 때 조건문 실행
	{
		CString filePath = dlg.GetPathName(); //파일 경로

		CString fileName = dlg.GetFileName(); //파일 이름

		// 서버에 파일 이름 전송
		CString request = _T("[File] ") + fileName;

		// request.GetLength() * sizeof(TCHAR) < 전송할 데이터(request) 크기 (문자열 길이 * 데이터 타입 크기)
		m_pDataSocket->Send(request, request.GetLength() * sizeof(TCHAR));

		// 파일 오픈
		CFile file;
		if (file.Open(filePath, CFile::modeRead | CFile::typeBinary)) // 파일 읽기 모드로 오픈/ 바이너리 모드로 오픈
		{
			// 파일 크기 가져오기
			// (UINT) < 형변환 명시
			UINT fileSize = (UINT)file.GetLength(); //GetLength() < CFile 클래스의 멤버함수로 열린 파일의 크기 반환
			int nNameLen = fileName.GetLength(); // 파일 이름 길이 저장

			// 파일 이름 길이와 파일 이름을 서버로 전송
			m_pDataSocket->Send(&nNameLen, sizeof(int)); // 파일 이름 길이 전달
			m_pDataSocket->Send((LPCTSTR)fileName, nNameLen * sizeof(TCHAR)); // 파일 이름 전달, LPCTSTR < 문자열 가리키는 포인터

			// 파일 크기를 서버로 전송 (파일 크기를 알아야 서버에서 파일을 수신할 수 있기 때문)
			m_pDataSocket->Send(&fileSize, sizeof(UINT));

			// 파일 데이터를 읽어와 소켓을 통해 전송
			CByteArray fileData;
			fileData.SetSize(fileSize); // 객체 크기를 fileSize(파일크기)로 설정
			file.Read(fileData.GetData(), fileSize); //filesize만큼 파일을 읽어옴
			file.Close();

			// 소켓을 통해 파일 데이터를 서버에 전송
			m_pDataSocket->Send(fileData.GetData(), fileSize); // fileData.GetData() < 파일데이터의 시작위치, fileSize < 전송할 데이터 크기
			m_pDataSocket->Send(file, 256);

			// 전송한 데이터 리스트 박스에 보여줌
			CString strTmp;
			strTmp.Format(_T("나 : [File] %s"), fileName);
			int i = list_box.GetCount();
			list_box.InsertString(i, strTmp);
			UpdateData(FALSE);

			// 파일 전송 완료 메시지 표시
			MessageBox(_T("파일 전송이 완료되었습니다."));

		}
		else
		{
			LPCTSTR pAppNameTemp = AfxGetApp()->m_pszAppName;
			AfxGetApp()->m_pszAppName = _T("ERROR");
			MessageBox(_T("파일을 열 수 없습니다."));
			AfxGetApp()->m_pszAppName = pAppNameTemp;

		}
	}
}


void Cmfctestclient1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void Cmfctestclient1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	  //mat_frame가 입력 이미지입니다.
	capture->read(mat_frame);


	//이곳에 OpenCV 함수들을 적용합니다.
	//여기에서는 그레이스케일 이미지로 변환합니다.
	//cvtColor(mat_frame, mat_frame, COLOR_BGR2GRAY);//회색

	//화면에 보여주기 위한 처리입니다.
	int bpp = 8 * mat_frame.elemSize();
	assert((bpp == 8 || bpp == 24 || bpp == 32));

	int padding = 0;
	//32 bit image is always DWORD aligned because each pixel requires 4 bytes
	if (bpp < 32)
		padding = 4 - (mat_frame.cols % 4);

	if (padding == 4)
		padding = 0;

	int border = 0;
	//32 bit image is always DWORD aligned because each pixel requires 4 bytes
	if (bpp < 32)
	{
		border = 4 - (mat_frame.cols % 4);
	}



	Mat mat_temp;
	if (border > 0 || mat_frame.isContinuous() == false)
	{
		// Adding needed columns on the right (max 3 px)
		cv::copyMakeBorder(mat_frame, mat_temp, 0, 0, 0, border, cv::BORDER_CONSTANT, 0);
	}
	else
	{
		mat_temp = mat_frame;
	}


	RECT r;
	m_picture.GetClientRect(&r);
	cv::Size winSize(r.right, r.bottom);

	cimage_mfc.Create(winSize.width, winSize.height, 24);


	BITMAPINFO* bitInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));
	bitInfo->bmiHeader.biBitCount = bpp;
	bitInfo->bmiHeader.biWidth = mat_temp.cols;
	bitInfo->bmiHeader.biHeight = -mat_temp.rows;
	bitInfo->bmiHeader.biPlanes = 1;
	bitInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitInfo->bmiHeader.biCompression = BI_RGB;
	bitInfo->bmiHeader.biClrImportant = 0;
	bitInfo->bmiHeader.biClrUsed = 0;
	bitInfo->bmiHeader.biSizeImage = 0;
	bitInfo->bmiHeader.biXPelsPerMeter = 0;
	bitInfo->bmiHeader.biYPelsPerMeter = 0;


	//그레이스케일 인경우 팔레트가 필요
	if (bpp == 8)
	{
		RGBQUAD* palette = bitInfo->bmiColors;
		for (int i = 0; i < 256; i++)
		{
			palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
			palette[i].rgbReserved = 0;
		}
	}


	// Image is bigger or smaller than into destination rectangle
	// we use stretch in full rect

	if (mat_temp.cols == winSize.width && mat_temp.rows == winSize.height)
	{
		// source and destination have same size
		// transfer memory block
		// NOTE: the padding border will be shown here. Anyway it will be max 3px width

		SetDIBitsToDevice(cimage_mfc.GetDC(),
			//destination rectangle
			0, 0, winSize.width, winSize.height,
			0, 0, 0, mat_temp.rows,
			mat_temp.data, bitInfo, DIB_RGB_COLORS);
	}
	else
	{
		// destination rectangle
		int destx = 0, desty = 0;
		int destw = winSize.width;
		int desth = winSize.height;

		// rectangle defined on source bitmap
		// using imgWidth instead of mat_temp.cols will ignore the padding border
		int imgx = 0, imgy = 0;
		int imgWidth = mat_temp.cols - border;
		int imgHeight = mat_temp.rows;

		StretchDIBits(cimage_mfc.GetDC(),
			destx, desty, destw, desth,
			imgx, imgy, imgWidth, imgHeight,
			mat_temp.data, bitInfo, DIB_RGB_COLORS, SRCCOPY);
	}


	HDC dc = ::GetDC(m_picture.m_hWnd);
	cimage_mfc.BitBlt(dc, 0, 0);


	::ReleaseDC(m_picture.m_hWnd, dc);

	cimage_mfc.ReleaseDC();
	cimage_mfc.Destroy();

	CDialogEx::OnTimer(nIDEvent);
}
void Cmfctestclient1Dlg::OnBnClickedSend3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	imshow("", mat_frame);
}
