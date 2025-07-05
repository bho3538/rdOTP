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
		255,
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

	switch (msg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);

			return 0;
		}
		case WM_PAINT:
		{
			// 창의 크기 구하기
			RECT rc;
			GetClientRect(hwnd, &rc);

			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			if (!hdc)
			{
				break;
			}

			SetBkMode(hdc, TRANSPARENT);

			// 표시할 텍스트의 색
			SetTextColor(hdc, RGB(150, 150, 150));

			int windowHeight = rc.bottom - rc.top;

			// 타이틀 폰트 (큰거)
			HFONT titleFont = CreateFontW(
				windowHeight * 8 / 100,
				0,
				0,
				0,
				FW_NORMAL,
				FALSE,
				FALSE,
				FALSE,
				DEFAULT_CHARSET,
				OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,
				0,
				L"Arial"
			);

			// 설명 폰트 (작은거)
			HFONT subTitleFont = CreateFontW(
				windowHeight * 3 / 100,
				0,
				0,
				0,
				FW_NORMAL,
				FALSE,
				FALSE,
				FALSE,
				DEFAULT_CHARSET,
				OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,
				0,
				L"Arial"
			);

			HFONT oldFont = (HFONT)SelectObject(hdc, titleFont);
			RECT rcTitle =
			{
				rc.left,
				rc.top + 50,
				rc.right,
				rc.top + windowHeight / 2
			};

			DrawTextW(
				hdc,
				L"Under Remotely Controlled",
				-1,
				&rcTitle,
				DT_CENTER | DT_VCENTER
			);

			SelectObject(hdc, subTitleFont);
			RECT rcSubTitle =
			{
				rc.left,
				rc.top + windowHeight / 2,
				rc.right,
				rc.bottom
			};

			DrawTextW(
				hdc,
				L"To close this window, Press 'Win' key using keyboard, find 'rdOTP' at system tray and click 'Exit'",
				-1,
				&rcSubTitle,
				DT_CENTER | DT_VCENTER
			);

			// 정리
			SelectObject(hdc, oldFont);
			DeleteObject(titleFont);
			DeleteObject(subTitleFont);
			EndPaint(hwnd, &ps);

			return 0;
		}
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}