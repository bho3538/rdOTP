#pragma once

#include <string>

class ProcessManager
{
public:
	ProcessManager();
	~ProcessManager();

	void CheckIsStartedRemoteProcess(DWORD pid);
	void CheckIsEndedRemoteProcess(DWORD pid);

private:
	// 원격 프로그램 (크롬 원격 데스크톱) 의 pid
	DWORD _remoteProgramPid;

	// 로컬 모니터의 화면을 가리는 프로세스의 핸들
	HANDLE _curtainProcess;

	BOOL _needStartCurtainWhenLogon;

	// 크롬 원격 데스크톱이 시작된 경우 수행하는 작업
	void OnChromeRemoteDesktopStarted(DWORD pid);

	// 크롬 원격 데스크톱이 종료된 경우 수행하는 작업
	void OnChromeRemoteDesktopEnded(DWORD pid);

	// 사용자 세션에서 rdOTP 프로세스 시작
	HANDLE StartProcessOnUserSession(LPCWSTR exeName);

	// 실행 파일의 내부 정보 (VersionString) 을 읽기
	LPWSTR GetImageProperty(LPCWSTR imagePath, LPCWSTR key);

	// rdOTP 내부 모듈의 경로를 조회
	std::wstring GetRDOTPExePath(LPCWSTR exeName);
};