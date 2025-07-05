#include "pch.h"
#include "CurtainManager.h"
#include "Curtain.h"
#include "Utils.h"
#include "resource.h"

#define _RDOTP_TRAY_MESSAGE (WM_APP + 2)
#define _RDOTP_TRAY_EXIT_COMMAND 0x1001

static HWND g_CurtainManagerHwnd = NULL;
static NOTIFYICONDATAW g_TrayMenu = { 0, };

static HWND* g_CurtainWindows = NULL;
static int g_CurtainWindowsCnt = 0;

LRESULT CALLBACK _CurtainMgrWindowWndProc(
	HWND hwnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
);

// Tray Menu 옵션을 표시 (커튼 종료 옵션)
void _ShowTrayMenuOptions(
	HWND hwnd
);

void _ShowCurtainWindow();
void _CloseCurtainWindow();

BOOL RDOTPInitializeCurtainMgr()
{
	// 커튼 창을 제어하기 위한 윈도우 생성 (숨겨진 창)
	WNDCLASS wc = { 0, };
	wc.lpfnWndProc = _CurtainMgrWindowWndProc;
	wc.lpszClassName = _RDOTP_CURTAIN_WINDOW_MANAGER_CLASSNAME;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	ATOM windowClass = RegisterClassW(&wc);
	if (!windowClass)
	{
		return FALSE;
	}

	return RDOTPInitializeCurtain();
}

BOOL RDOTPStartCurtainMgr()
{
	if (g_CurtainManagerHwnd)
	{
		// already running
		return TRUE;
	}

	g_CurtainManagerHwnd = CreateWindowExW(
		WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW,
		_RDOTP_CURTAIN_WINDOW_MANAGER_CLASSNAME,
		L"",
		WS_POPUP,
		0,
		0,
		0,
		0,
		NULL,
		NULL,
		NULL,
		NULL
	);

	if (!g_CurtainManagerHwnd)
	{
		return FALSE;
	}

	// Tray Menu
	g_TrayMenu.cbSize = sizeof(g_TrayMenu);
	g_TrayMenu.hWnd = g_CurtainManagerHwnd;
	g_TrayMenu.uID = 1001;
	g_TrayMenu.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	g_TrayMenu.uCallbackMessage = _RDOTP_TRAY_MESSAGE;
	g_TrayMenu.hIcon = LoadIconW(GetModuleHandleW(NULL), MAKEINTRESOURCE(IDI_ICON1));
	wcscpy_s(g_TrayMenu.szTip, ARRAYSIZE(g_TrayMenu.szTip), L"rdOTP");
	Shell_NotifyIconW(NIM_ADD, &g_TrayMenu);

	// 커튼 창 생성
	_ShowCurtainWindow();

	return TRUE;
}

void RDOTPStopCurtainMgr()
{
	_CloseCurtainWindow();

	// release tray menu
	Shell_NotifyIconW(NIM_DELETE, &g_TrayMenu);
	ZeroMemory(&g_TrayMenu, sizeof(g_TrayMenu));

	DestroyWindow(g_CurtainManagerHwnd);
	g_CurtainManagerHwnd = NULL;
}

void RDOTPReleaseCurtainMgr()
{

}

LRESULT CALLBACK _CurtainMgrWindowWndProc(
	HWND hwnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
)
{
	switch (msg)
	{
		case _RDOTP_TRAY_MESSAGE:
		{
			if (lParam == WM_LBUTTONUP || lParam == WM_RBUTTONUP)
			{
				_ShowTrayMenuOptions(hwnd);
				return 0;
			}
			break;
		}
		case WM_COMMAND:
		{
			if (LOWORD(wParam) == _RDOTP_TRAY_EXIT_COMMAND)
			{
				// 사용자가 커튼 모드 종료 메뉴를 클릭한 경우
				RDOTPStopCurtainMgr();
			}
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void _ShowTrayMenuOptions(
	HWND hwnd
)
{
	HMENU menu = CreatePopupMenu();
	if (!menu)
	{
		return;
	}

	AppendMenuW(menu, MF_STRING, _RDOTP_TRAY_EXIT_COMMAND, L"Exit");

	SetForegroundWindow(hwnd);

	// 메뉴를 띄울 위치를 찾기
	POINT pt;
	GetCursorPos(&pt);

	// 해당 위치에 메뉴를 띄우기
	TrackPopupMenuEx(
		menu,
		TPM_RIGHTBUTTON | TPM_LEFTALIGN,
		pt.x,
		pt.y,
		hwnd,
		NULL
	);

	DestroyMenu(menu);
}


void _ShowCurtainWindow()
{
	// 모니터 정보들을 조회
	RECT* pMonitorRects = NULL;
	int monitorRectsCount = RDOTPGetDisplayMonitorInfos(&pMonitorRects);
	if (monitorRectsCount <= 0 || pMonitorRects == NULL)
	{
		return;
	}

	// 모니터 갯수에 맞는 창(hwnd) 를 저장하기 위한 공간 할당
	g_CurtainWindows = (HWND*)malloc(sizeof(HWND) * monitorRectsCount);
	if (!g_CurtainWindows)
	{
		free(pMonitorRects);

		return;
	}

	// 생성한 창의 수
	int hwndCnt = 0;
	for (int i = 0; i < monitorRectsCount - 1; i++)
	{
		// 각 모니터별로 창을 생성
		HWND hwnd = RDOTPShowCurtainWindow(
			pMonitorRects[i].left,
			pMonitorRects[i].top,
			pMonitorRects[i].right - pMonitorRects[i].left,
			pMonitorRects[i].bottom - pMonitorRects[i].top
		);

		// 창 생성을 실패한 경우
		if (!hwnd)
		{
			continue;
		}

		g_CurtainWindows[hwndCnt++] = hwnd;
	}

	g_CurtainWindowsCnt = hwndCnt;

	free(pMonitorRects);
}

void _CloseCurtainWindow()
{
	for (int i = 0; i < g_CurtainWindowsCnt; i++)
	{
		RDOTPCloseCurtainWindow(g_CurtainWindows[i]);
	}

	free(g_CurtainWindows);
	g_CurtainWindows = NULL;
	g_CurtainWindowsCnt = 0;
}
