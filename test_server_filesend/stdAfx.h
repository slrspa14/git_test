#pragma once

#include <afxsock.h> //����Ŭ���� ����
#include "CSocServer.h"//������ ����
#include "CSocCom.h"//��ſ� ����

#define UM_ACCEPT WM_USER+1/*���������쿡 �޽��� ������ ���� ������
����������(m_hwnd)�� sendMessage�� �̿��� UM_ACCEPT��� ����� ���� �޽����� �ش�*/
#define UM_RECEIVE WM_USER+2
