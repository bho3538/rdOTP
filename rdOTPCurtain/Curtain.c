#include "pch.h"
#include "Curtain.h"

LRESULT CALLBACK _CurtainWindowWndProc(
	HWND hwnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
);

BOOL RDOTPInitializeCurtain()
{
	// 윈도우 등록
	WNDCLASS wc = { 0, };
	wc.lpfnWndProc = _CurtainWindowWndProc;
	wc.lpszClassName = _RDOTP_CURTAIN_WINDOW_CLASSNAME;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	ATOM windowClass = RegisterClassW(&wc);
	if (!windowClass)
	{
		return FALSE;
	}

	return TRUE;
}

HWND RDOTPShowCurtainWindow(
	int x,
	int y,
	int sizeX,
	int sizeY
)
{
	// 커튼 윈도우 생성
	HWND hwnd = CreateWindowExW(
		WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW, // 투과되는 topmost 창
		_RDOTP_CURTAIN_WINDOW_CLASSNAME,
		L"",
		WS_POPUP,
		x,
		y,
		sizeX,
		sizeY,
		NULL,
		NULL,
		NULL,
		NULL
	);

	if (!hwnd) 
	{
		return 0;
	}

	// 창을 불투명하게 설정
	SetLayeredWindowAttributes(
		hwnd,
		0,
		100,
		LWA_ALPHA
	);

	// 원격 프로그램이 아닌 로컬 모니터에만 해당 창이 보이도록 설정 (Win10 2004 부터 지원)
	SetWindowDisplayAffinity(hwnd, WDA_EXCLUDEFROMCAPTURE);

	ShowWindow(hwnd, SW_SHOW);

	return hwnd;
}

void RDOTPCloseCurtainWindow(
	HWND hwnd
)
{
	if (!hwnd)
	{
		return;
	}

	CloseWindow(hwnd);

	DestroyWindow(hwnd);
}

LRESULT CALLBACK _CurtainWindowWndProc(
	HWND hwnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
) 
{
	if (msg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}