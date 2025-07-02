#include "pch.h"

#include "Curtain.h"

static int g_MonitorCount = 0;
static RECT* g_pMonitorRects = NULL;
static int g_MonitorRectsIndex = 0;

// 컴퓨터의 모니터 정보를 조회
int _GetDisplayMonitorInfos(RECT** ppRects);
BOOL WINAPI _MonitorEnumProc(
	HMONITOR unnamedParam1,
	HDC unnamedParam2,
	LPRECT unnamedParam3,
	LPARAM unnamedParam4
);

// 커튼 윈도우 생성
int _ShowCurtainWindow(HWND** ppHwnds);

// 커튼 윈도우 닫기
void _CloseCurtainWindow(
	int nHwnds,
	HWND* pHwnds
);

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR pCmdLine,
	int nCmdShow
) 
{
	// 커튼 윈도우 초기화
	RDOTPInitializeCurtain();

	HWND* curtainWindows = NULL;
	// 모니터 별로 커튼 윈도우 생성 및 표시
	int curtainWindowsCnt = _ShowCurtainWindow(&curtainWindows);

	// 메인 메시지 루프
	MSG msg;
	while (GetMessageW(
		&msg,
		NULL,
		0,
		0
	))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	if (curtainWindows)
	{
		// 프로그램 종료 요청 시 커튼 윈도우 파괴
		_CloseCurtainWindow(curtainWindowsCnt, curtainWindows);

		free(curtainWindows);
	}

	// 커튼 윈도우 정리


	return 0;
}

int _ShowCurtainWindow(HWND** ppHwnds)
{
	if (!ppHwnds)
	{
		return -1;
	}

	// 모니터 정보들을 조회
	RECT* pMonitorRects = NULL;
	int monitorRectsCount = _GetDisplayMonitorInfos(&pMonitorRects);
	if (monitorRectsCount <= 0 || pMonitorRects == NULL)
	{
		return -1;
	}

	*ppHwnds = (HWND*)malloc(sizeof(HWND) * monitorRectsCount);
	if (!*ppHwnds)
	{
		return -1;
	}

	int hwndCnt = 0;
	for (int i = 0; i < monitorRectsCount; i++)
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

		(*ppHwnds)[hwndCnt++] = hwnd;
	}

	return hwndCnt;
}

void _CloseCurtainWindow(
	int nHwnds,
	HWND* pHwnds
)
{
	if (!pHwnds)
	{
		return;
	}

	for (int i = 0; i < nHwnds; i++)
	{
		RDOTPCloseCurtainWindow(pHwnds[i]);
	}

	free(pHwnds);
}


int _GetDisplayMonitorInfos(
	RECT** ppRects
) 
{
	if (!ppRects) 
	{
		return -1;
	}

	*ppRects = NULL;
	
	// 전역 변수 초기화
	g_MonitorCount	= 0;
	g_pMonitorRects = NULL;

	// 컴퓨터에 연결된 모든 모니터의 갯수를 조회
	if (EnumDisplayMonitors(
		NULL,
		NULL,
		_MonitorEnumProc, 
		0
	) == FALSE) 
	{
		return -1;
	}

	// 정보를 조회하지 못한 경우 (혹은 진짜 모니터가 한개도 없는 경우)
	if (g_MonitorCount == 0) 
	{
		return 0;
	}

	g_MonitorRectsIndex = 0;
	g_pMonitorRects = (LPRECT)malloc(g_MonitorCount * sizeof(RECT));

	// 컴퓨터에 연결된 모든 모니터의 정보를 조회
	if (EnumDisplayMonitors(
		NULL,
		NULL,
		_MonitorEnumProc,
		0
	) == FALSE) 
	{
		free(g_pMonitorRects);
		g_pMonitorRects = NULL;

		return -1;
	}

	*ppRects = g_pMonitorRects;
	g_pMonitorRects = NULL;

	return g_MonitorRectsIndex;
}

BOOL WINAPI _MonitorEnumProc(
	HMONITOR unnamedParam1,
	HDC unnamedParam2,
	LPRECT unnamedParam3,
	LPARAM unnamedParam4
) 
{
	if (!g_pMonitorRects)
	{
		g_MonitorCount++;
	}
	else 
	{
		if (g_MonitorRectsIndex >= g_MonitorCount)
		{
			return TRUE;
		}

		g_pMonitorRects[g_MonitorRectsIndex] = *unnamedParam3;

		g_MonitorRectsIndex++;
	}

	return TRUE;
}