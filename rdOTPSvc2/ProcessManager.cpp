#include "pch.h"
#include "ProcessManager.h"

#include <Shlwapi.h>
#include <pathcch.h>
#include <wtsapi32.h>
#include <TlHelp32.h>

ProcessManager::ProcessManager() :
	_remoteProgramPid(0),
	_curtainProcess(NULL),
	_needStartCurtainWhenLogon(FALSE)
{}

ProcessManager::~ProcessManager()
{}

void ProcessManager::CheckIsStartedRemoteProcess(DWORD pid)
{
	// 이미 원격 프로그램이 실행중이면 이후 작업은 진행하지 않음
	if (_remoteProgramPid != 0)
	{
		return;
	}

	// 프로세를 open 시도
	HANDLE hProcess = ::OpenProcess(
		PROCESS_QUERY_LIMITED_INFORMATION,
		FALSE,
		pid
	);

	if (hProcess == NULL)
	{
		// 권한이 없거나, 즉시 종료된 프로세스.
		return;
	}

	WCHAR processImagePath[MAX_PATH];
	DWORD processImagePathLen = MAX_PATH - 1;

	// 프로세스 실행 파일 경로를 조회
	if (::QueryFullProcessImageNameW(
		hProcess,
		0,
		processImagePath,
		&processImagePathLen
	) != FALSE)
	{

		// 풀 경로에서 실행 파일 이름을 조회
		LPCWSTR filename = ::PathFindFileNameW(
			processImagePath
		);

		// chrome remote desktop 일 경우
		if (::_wcsicmp(
			filename,
			L"remoting_desktop.exe"
		) == 0)
		{
			// 실행 파일의 내부 VersionString 을 비교하여 Google chrome remote desktop 인지 검사
			LPWSTR companyName = GetImageProperty(
				processImagePath,
				L"CompanyName"
			);

			// company name 이 없는 경우 skip
			if (companyName != NULL)
			{
				if (::wcscmp(
					companyName,
					L"Google LLC"
				) == 0)
				{
					// Google chrome remote desktop 인 경우
					OnChromeRemoteDesktopStarted(pid);
				}

				::free(companyName);
			}
		}
	}

	::CloseHandle(hProcess);
}

void ProcessManager::CheckIsEndedRemoteProcess(DWORD pid)
{
	OnChromeRemoteDesktopEnded(pid);
}

void ProcessManager::OnChromeRemoteDesktopStarted(DWORD pid)
{
	// already running
	if (_remoteProgramPid != 0)
	{
		return;
	}

	_remoteProgramPid = pid;

	// logonui 종료
	// 만약 잠금이 이미 시작되어있는 경우 기본 cred provider 가 표시되어 otp 인증을 수행할 수 없기 때문
	PROCESSENTRY32W pe32 = 
	{ 
		sizeof(PROCESSENTRY32W),
		0,
	};

	// 실행중인 프로세스 enum
	HANDLE hSnap = ::CreateToolhelp32Snapshot(
		TH32CS_SNAPPROCESS,
		0
	);

	if (hSnap != INVALID_HANDLE_VALUE) 
	{
		WCHAR processImagePath[MAX_PATH];
		DWORD processImagePathLen = MAX_PATH - 1;

		WCHAR logonuiPath[MAX_PATH];

		// logonui 의 실행 경로 구하기
		if (::GetSystemDirectoryW(
			logonuiPath,
			MAX_PATH
		) == 0)
		{
			// fallback
			::wcscpy_s(
				logonuiPath,
				MAX_PATH,
				L"C:\\Windows\\System32"
			);
		}

		::wcscat_s(
			logonuiPath,
			MAX_PATH,
			L"\\LogonUI.exe"
		);

		do 
		{
			// 프로세스 이름이 logonui 인 경우

			if (!::_wcsicmp(
				L"LogonUI.exe",
				pe32.szExeFile)
				) 
			{
				HANDLE hProcess = ::OpenProcess(
					PROCESS_QUERY_INFORMATION | THREAD_TERMINATE,
					FALSE,
					pe32.th32ProcessID
				);

				if (hProcess != NULL)
				{
					// 프로세스 실행 파일 경로를 조회
					if (::QueryFullProcessImageNameW(
						hProcess,
						0,
						processImagePath,
						&processImagePathLen
					) != FALSE)
					{
						// logonui 인 경우 강제종료
						if (::_wcsicmp(
							processImagePath,
							logonuiPath
						) == 0)
						{
							::TerminateProcess(
								hProcess,
								0
							);
						}
					}

					::CloseHandle(hProcess);
				}
			}
		} 
		while (::Process32NextW(hSnap, &pe32));

		::CloseHandle(hSnap);
	}

	// 화면 잠금 실행
	HANDLE hLockerProcess = StartProcessOnUserSession(L"rdOTPHelper.exe");
	if (hLockerProcess != NULL)
	{
		::CloseHandle(hLockerProcess);
	}

	// 커튼 실행
	_curtainProcess = StartProcessOnUserSession(L"rdOTPCurtain.exe");
	if (_curtainProcess == NULL)
	{
		_needStartCurtainWhenLogon = TRUE;
	}
}

void ProcessManager::OnChromeRemoteDesktopEnded(DWORD pid)
{
	if (_remoteProgramPid != pid)
	{
		return;
	}

	_remoteProgramPid = 0;
	_needStartCurtainWhenLogon = FALSE;

	// 커튼 종료
	// 서비스 세션에서 유저 세션으로 메시지를 보낼 수 없으므로 강제 종료 수행.
	// TODO : 적절한 ipc 통신을 사용하여 grace 하게 종료하도록 수정 필요
	if (_curtainProcess != NULL)
	{
		::TerminateProcess(_curtainProcess, 0);
		_curtainProcess = NULL;
	}

	// 화면 잠금 실행
	HANDLE hProcess = StartProcessOnUserSession(L"rdOTPHelper.exe");
	if (hProcess != NULL)
	{
		::CloseHandle(hProcess);
	}
}

LPWSTR ProcessManager::GetImageProperty(LPCWSTR imagePath, LPCWSTR key)
{
	LPWSTR propertyData = NULL;

	DWORD dummy = 0;
	DWORD versionSize = ::GetFileVersionInfoSizeW(
		imagePath,
		&dummy
	);

	if (versionSize == 0)
	{
		return NULL;
	}

	BYTE* versionData = (BYTE*)::malloc(versionSize);
	if (versionData == NULL)
	{
		return NULL;
	}

	if (::GetFileVersionInfoW(
		imagePath,
		0,
		versionSize,
		versionData
	) != FALSE)
	{
		struct LANGANDCODEPAGE 
		{
			WORD wLanguage;
			WORD wCodePage;
		} *lpTranslate = NULL;
		UINT cbTranslate = 0;

		if (::VerQueryValueW(
			versionData,
			L"\\VarFileInfo\\Translation",
			(LPVOID*)&lpTranslate,
			&cbTranslate
		) != FALSE)
		{

			WCHAR subBlock[64] = { 0, };
			::wsprintfW(
				subBlock,
				L"\\StringFileInfo\\%04x%04x\\%s",
				lpTranslate[0].wLanguage,
				lpTranslate[0].wCodePage,
				key
			);

			LPWSTR lpDataStr = NULL;
			UINT cbDataStr = 0;

			if (::VerQueryValueW(
				versionData,
				subBlock,
				(LPVOID*)&lpDataStr,
				&cbDataStr
			) != FALSE)
			{
				// copy
				cbDataStr *= sizeof(WCHAR);

				propertyData = (LPWSTR)::malloc(cbDataStr);
				if (propertyData != NULL)
				{
					::memcpy_s(propertyData, cbDataStr, lpDataStr, cbDataStr);
				}
			}
		}
	}

	free(versionData);
	return propertyData;
}

std::wstring ProcessManager::GetRDOTPExePath(LPCWSTR exeName)
{
	WCHAR currentDir[MAX_PATH] = { 0, };

	if (::GetModuleFileNameW(
		NULL,
		currentDir,
		MAX_PATH
	) == 0)
	{
		return L"";
	}

	HRESULT hr = ::PathCchRemoveFileSpec(
		currentDir,
		MAX_PATH
	);

	if (hr != S_OK)
	{
		return L"";
	}

	std::wstring path = currentDir;
	path += L"\\";
	path += exeName;

	return path;
}

HANDLE ProcessManager::StartProcessOnUserSession(LPCWSTR exeName)
{
	DWORD userSessionId = ::WTSGetActiveConsoleSessionId();
	if (userSessionId == MAXDWORD)
	{
		return NULL;
	}

	// 세션id 에서 사용자 토큰을 구하기
	HANDLE hTempToken = NULL;
	if (::WTSQueryUserToken(
		userSessionId,
		&hTempToken
	) == FALSE)
	{
		return NULL;
	}

	// 토큰 복제
	HANDLE hUserToken = NULL;
	if (::DuplicateTokenEx(
		hTempToken,
		0,
		NULL,
		SecurityImpersonation,
		TokenPrimary,
		&hUserToken) == FALSE)
	{
		::CloseHandle(hTempToken);

		return NULL;
	}

	::CloseHandle(hTempToken);

	// 프로세스 경로 구하기
	std::wstring processPath = GetRDOTPExePath(exeName);
	if (processPath.empty() == true)
	{
		::CloseHandle(hUserToken);

		return NULL;
	}

	PROCESS_INFORMATION processInfo = { 0, };
	STARTUPINFO processStartupInfo = { 0, };

	if (::CreateProcessAsUserW(
		hUserToken,
		processPath.c_str(),
		NULL,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&processStartupInfo,
		&processInfo
	) != FALSE)
	{
		CloseHandle(processInfo.hThread);

		return processInfo.hProcess;
	}

	return NULL;
}