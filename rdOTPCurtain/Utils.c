#include "pch.h"
#include "Utils.h"

static int g_MonitorCount = 0;
static RECT* g_pMonitorRects = NULL;
static int g_MonitorRectsIndex = 0;

BOOL WINAPI _RDOTPMonitorEnumProc(
	HMONITOR unnamedParam1,
	HDC unnamedParam2,
	LPRECT unnamedParam3,
	LPARAM unnamedParam4
);

int RDOTPGetDisplayMonitorInfos(
	RECT** ppRects
)
{
	if (!ppRects)
	{
		return -1;
	}

	*ppRects = NULL;

	// 전역 변수 초기화
	g_MonitorCount = 0;
	g_pMonitorRects = NULL;

	// 컴퓨터에 연결된 모든 모니터의 갯수를 조회
	if (EnumDisplayMonitors(
		NULL,
		NULL,
		_RDOTPMonitorEnumProc,
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
		_RDOTPMonitorEnumProc,
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

BOOL WINAPI _RDOTPMonitorEnumProc(
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