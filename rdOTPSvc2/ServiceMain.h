#pragma once
class ServiceMain
{
public:
	static void WINAPI RunService();
private:

	static void WINAPI SvcMain(
		DWORD dwArgc,
		LPWSTR* lpszArgv
	);

	static DWORD WINAPI SvcCtrlHandler(
		DWORD dwCtrl,
		DWORD dwEventType,
		LPVOID lpEventData,
		LPVOID lpContext
	);

	ServiceMain();
	~ServiceMain();

	bool Initialize();
	void Release();

	void Run();

	void SvcReportStatus(
		DWORD state,
		DWORD exitCode,
		DWORD waitTime
	);

	SERVICE_STATUS_HANDLE _svcHandle;
	SERVICE_STATUS _svcStatus;

	HANDLE _svcStopEvent;

	DWORD _reportStatusCnt;
};

