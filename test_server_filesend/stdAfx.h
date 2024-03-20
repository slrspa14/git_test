#pragma once

#include <afxsock.h> //소켓클래스 사용용
#include "CSocServer.h"//서보용 소켓
#include "CSocCom.h"//통신용 소켓

#define UM_ACCEPT WM_USER+1/*메인윈도우에 메시지 보내기 위한 구별자
메인윈도우(m_hwnd)에 sendMessage를 이용해 UM_ACCEPT라는 사용자 정의 메시지를 준다*/
#define UM_RECEIVE WM_USER+2
