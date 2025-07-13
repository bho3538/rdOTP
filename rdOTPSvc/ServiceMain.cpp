#include "pch.h"
#include "ServiceMain.h"
#include "ETWTraceManager.h"

ServiceMain::ServiceMain() :
	_svcHandle(NULL),
	_svcStopEvent(NULL),
	_reportStatusCnt(0)
{
	::ZeroMemory(&_svcStatus, sizeof(SERVICE_STATUS));
}

ServiceMain::~ServiceMain()
{}

void WINAPI ServiceMain::RunService()
{
	const SERVICE_TABLE_ENTRYW DispatchTable[] =
	{
		{ (LPWSTR)_RDOTP_SVC_NAME, (LPSERVICE_MAIN_FUNCTIONW)SvcMain },
		{ NULL, NULL }
	};

	::StartServiceCtrlDispatcherW(DispatchTable);
}

void ServiceMain::InstallService()
{
	SC_HANDLE hScmManager = NULL;
	SC_HANDLE hSvc = NULL;

	WCHAR modulePath[MAX_PATH];

	if (!GetModuleFileNameW(NULL, modulePath, MAX_PATH))
	{
		return;
	}

	hScmManager = ::OpenSCManagerW(
		NULL,
		NULL,
		SC_MANAGER_ALL_ACCESS
	);

	if (!hScmManager)
	{
		return;
	}

	hSvc = ::CreateServiceW(
		hScmManager,
		_RDOTP_SVC_NAME,
		_RDOTP_SVC_NAME,
		SERVICE_ALL_ACCESS,
		SERVICE_WIN32_OWN_PROCESS,
		SERVICE_AUTO_START,
		SERVICE_ERROR_NORMAL,
		modulePath,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL
	);

	if (hSvc)
	{
		::CloseServiceHandle(hSvc);
	}

	::CloseServiceHandle(hScmManager);
}

void ServiceMain::RemoveService()
{
	SC_HANDLE hScmManager = NULL;
	SC_HANDLE hSvc = NULL;

	hScmManager = ::OpenSCManagerW(
		NULL,
		NULL,
		SC_MANAGER_ALL_ACCESS
	);

	if (!hScmManager)
	{
		return;
	}

	hSvc = ::OpenServiceW(
		hScmManager,
		_RDOTP_SVC_NAME,
		DELETE
	);

	if (hSvc)
	{
		::DeleteService(hSvc);

		::CloseServiceHandle(hSvc);
	}

	::CloseServiceHandle(hScmManager);
}

void WINAPI ServiceMain::SvcMain(
	DWORD dwArgc,
	LPWSTR* lpszArgv
)
{
	ServiceMain svcMain;

	if (svcMain.Initialize() == false)
	{
		return;
	}

	// 서비스 종료 요청이 발생할때 까지 실행
	svcMain.Run();

	// 서비스 종료 요청이 발생하면 종료
	svcMain.Release();
}

DWORD WINAPI ServiceMain::SvcCtrlHandler(
	DWORD dwCtrl,
	DWORD dwEventType,
	LPVOID lpEventData,
	LPVOID lpContext
)
{
	if (lpContext == NULL)
	{
		return ERROR_CALL_NOT_IMPLEMENTED;
	}

	ServiceMain* _this = (ServiceMain*)lpContext;

	switch (dwCtrl)
	{
		case SERVICE_CONTROL_STOP:
		{
			_this->SvcReportStatus(
				SERVICE_STOP_PENDING,
				NO_ERROR,
				5000
			);

			// 서비스 종료를 위해 이벤트를 실행
			SetEvent(_this->_svcStopEvent);

			return NO_ERROR;
		}
		case SERVICE_CONTROL_SESSIONCHANGE:
		{
			if (dwEventType == WTS_SESSION_LOGON)
			{
				_this->_processManager.OnUserLogon();
			}

			return NO_ERROR;
		}
	}

	return ERROR_CALL_NOT_IMPLEMENTED;
}

bool ServiceMain::Initialize()
{
	// 서비스 컨트롤 핸들러 등록
	_svcHandle = ::RegisterServiceCtrlHandlerExW(
		_RDOTP_SVC_NAME,
		ServiceMain::SvcCtrlHandler,
		this
	);

	if (_svcHandle == NULL)
	{
		return false;
	}

	_svcStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	_svcStatus.dwServiceSpecificExitCode = NO_ERROR;

	SvcReportStatus(
		SERVICE_START_PENDING,
		NO_ERROR,
		5000
	);

	_svcStopEvent = ::CreateEventW(
		NULL,
		TRUE,
		FALSE,
		NULL
	);

	if (_svcStopEvent == NULL)
	{
		return false;
	}

	SvcReportStatus(
		SERVICE_RUNNING,
		NO_ERROR,
		5000
	);

	return true;
}

void ServiceMain::Release()
{
	SvcReportStatus(
		SERVICE_STOPPED,
		NO_ERROR,
		5000
	);

	if (_svcHandle != NULL)
	{
		_svcHandle = NULL;
	}

	if (_svcStopEvent != NULL)
	{
		::CloseHandle(_svcStopEvent);
		_svcStopEvent = NULL;
	}

	::ZeroMemory(&_svcStatus, sizeof(SERVICE_STATUS));
}

void ServiceMain::Run()
{
	if (_svcHandle == NULL)
	{
		return;
	}

	// 실행할 것들
	ETWTraceManager traceManager(&_processManager);
	if (traceManager.Initialize() == false)
	{
		return;
	}

	traceManager.Start();

	// 서비스 종료 요청이 올때까지 대기
	::WaitForSingleObject(
		_svcStopEvent,
		INFINITE
	);

	traceManager.Stop();

	traceManager.Release();
}

void ServiceMain::SvcReportStatus(
	DWORD state,
	DWORD exitCode,
	DWORD waitTime
)
{
	if (_svcHandle == NULL)
	{
		return;
	}

	_svcStatus.dwCurrentState = state;
	_svcStatus.dwWin32ExitCode = exitCode;
	_svcStatus.dwWaitHint = waitTime;

	if (state == SERVICE_START_PENDING)
	{
		_svcStatus.dwControlsAccepted = 0;
	}
	else
	{
		// 시작 중이 아닐때는 서비스 정지가 가능하도록
		_svcStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
	}

	if (state == SERVICE_RUNNING || state == SERVICE_STOPPED)
	{
		// 서비스가 완전히 실행되었거나, 정지된 경우 재시도 횟수를 초기화
		_reportStatusCnt = 0;
	}
	else
	{
		_reportStatusCnt++;
	}

	_svcStatus.dwCheckPoint = _reportStatusCnt;
	_svcStatus.dwControlsAccepted |= SERVICE_ACCEPT_SESSIONCHANGE;

	::SetServiceStatus(
		_svcHandle,
		&_svcStatus
	);
}