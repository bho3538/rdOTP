#include "pch.h"

#include "CurtainManager.h"

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR pCmdLine,
	int nCmdShow
) 
{
	// 커튼 매니저 초기화
	RDOTPInitializeCurtainMgr();

	// 커튼 매니저 시작
	RDOTPStartCurtainMgr();

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

	return 0;
}

