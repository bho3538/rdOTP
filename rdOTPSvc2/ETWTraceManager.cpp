#include "pch.h"
#include "ETWTraceManager.h"

const WCHAR RDOTP_LOGGER_NAME[] = L"rdOTP_EventLogger";
const DWORD RDOTP_ETW_BUFFER_SIZE = 256;

const GUID RDOTP_LOGGER_GUID = { 0x81760642, 0x83d5, 0x44ab, { 0x9e, 0x38, 0xc7, 0x63, 0x2a, 0x92, 0x6e, 0x8b } };
const GUID RDOTP_TRACE_GUID_PROCESS_MANIFEST = { 0x22fb2cd6,0x0e7b,0x422b,{0xa0,0xc7,0x2f,0xad,0x1f,0xd0,0xe7,0x16} };

ETWTraceManager::ETWTraceManager() :
	_eventTraceThread(NULL),
	_traceSession(0),
	_traceProperties(NULL),
	_requestStop(false)
{}

ETWTraceManager::~ETWTraceManager()
{}

bool ETWTraceManager::Initialize()
{
	if (_traceProperties != NULL)
	{
		return true;
	}

	DWORD bufferSize = sizeof(EVENT_TRACE_PROPERTIES) + sizeof(RDOTP_LOGGER_NAME) + sizeof(WCHAR);

	_traceProperties = (EVENT_TRACE_PROPERTIES*)malloc(bufferSize);
	if (_traceProperties == NULL)
	{
		return false;
	}

	::ZeroMemory(_traceProperties, bufferSize);

	_traceProperties->Wnode.BufferSize = bufferSize;
	_traceProperties->Wnode.Guid = RDOTP_LOGGER_GUID;
	_traceProperties->Wnode.ClientContext = 1;
	_traceProperties->Wnode.Flags = WNODE_FLAG_TRACED_GUID;
	_traceProperties->LoggerNameOffset = sizeof(EVENT_TRACE_PROPERTIES);
	_traceProperties->BufferSize = RDOTP_ETW_BUFFER_SIZE;
	_traceProperties->LogFileMode = EVENT_TRACE_REAL_TIME_MODE | EVENT_TRACE_SYSTEM_LOGGER_MODE;

	return true;
}

void ETWTraceManager::Release()
{
	if (_traceSession != NULL)
	{
		// 추적 세션을 먼저 정지 후 Release 해야 함.
		return;
	}

	if (_traceProperties != NULL)
	{
		::free(_traceProperties);

		_traceProperties = NULL;
	}
}

void ETWTraceManager::Start()
{
	if (_eventTraceThread != NULL)
	{
		return;
	}

	if (_traceProperties == NULL)
	{
		// require initialize
		return;
	}

	_requestStop = false;

	// 이벤트 추적 스레드 시작
	_eventTraceThread = ::CreateThread(
		NULL,
		0,
		ETWTraceManager::TraceThread,
		this,
		0,
		NULL
	);
}

void ETWTraceManager::Stop()
{
	_requestStop = true;

	// 실행중인 추적 세션을 정지
	if (_traceSession != NULL)
	{
		::ControlTraceW(
			_traceSession,
			RDOTP_LOGGER_NAME,
			_traceProperties,
			EVENT_TRACE_CONTROL_STOP
		);

		_traceSession = NULL;
	}

	// 추적 이벤트를 실행하는 스레드가 완전히 정지될때까지 대기
	if (_eventTraceThread != NULL)
	{
		::WaitForSingleObject(
			_eventTraceThread,
			INFINITE
		);

		_eventTraceThread = NULL;
	}
}

bool ETWTraceManager::InitializeSession()
{
	if (_traceProperties == NULL)
	{
		return false;
	}

	DWORD status = ::StartTraceW(
		&_traceSession,
		RDOTP_LOGGER_NAME,
		_traceProperties
	);

	if (status == ERROR_ALREADY_EXISTS)
	{
		// 동작중인 세션 정지
		status = ::ControlTraceW(
			_traceSession,
			RDOTP_LOGGER_NAME,
			_traceProperties,
			EVENT_TRACE_CONTROL_STOP
		);

		// property 재설정
		_traceProperties->LogFileNameOffset = 0;
		_traceProperties->Wnode.Flags = WNODE_FLAG_TRACED_GUID;
		_traceProperties->EnableFlags = 0;

		// 다시 시작
		status = ::StartTraceW(
			&_traceSession,
			RDOTP_LOGGER_NAME,
			_traceProperties
		);
	}

	if (status == ERROR_SUCCESS)
	{
		ENABLE_TRACE_PARAMETERS prm =
		{
			ENABLE_TRACE_PARAMETERS_VERSION_2,
			0,
		};

		// manifest 기반의 process 이벤트 활성화
		status = ::EnableTraceEx2(
			_traceSession,
			&RDOTP_TRACE_GUID_PROCESS_MANIFEST,
			EVENT_CONTROL_CODE_ENABLE_PROVIDER,
			TRACE_LEVEL_INFORMATION,
			0x10, // process start event keyword
			0,
			0,
			&prm
		);

		return true;
	}

	return false;
}

DWORD WINAPI ETWTraceManager::TraceThread(
	PVOID args
)
{
	ETWTraceManager* _this = (ETWTraceManager*)args;

	EVENT_TRACE_LOGFILEW logFile = { 0, };
	logFile.LoggerName = (LPWSTR)RDOTP_LOGGER_NAME;
	logFile.ProcessTraceMode = PROCESS_TRACE_MODE_REAL_TIME | PROCESS_TRACE_MODE_EVENT_RECORD | PROCESS_TRACE_MODE_RAW_TIMESTAMP;
	logFile.EventRecordCallback = ETWTraceManager::TraceEventCallback;
	logFile.Context = args;

	while (_this->_requestStop == false)
	{
		if (_this->InitializeSession() == false)
		{
			break;
		}

		TRACEHANDLE currentTraceHandle = ::OpenTraceW(&logFile);
		if (currentTraceHandle == INVALID_PROCESSTRACE_HANDLE)
		{
			break;
		}

		// blocking
		::ProcessTrace(&currentTraceHandle, 1, NULL, NULL);

		::CloseTrace(currentTraceHandle);

		if (_this->_requestStop == true)
		{
			break;
		}

		// property 재설정
		_this->_traceProperties->LogFileNameOffset = 0;
		_this->_traceProperties->Wnode.Flags = WNODE_FLAG_TRACED_GUID;
		_this->_traceProperties->EnableFlags = 0;
	}

	return 0;
}

void WINAPI ETWTraceManager::TraceEventCallback(
	EVENT_RECORD* record
)
{
	if (!record || !record->UserData)
	{
		return;
	}

	// process 관련 이벤트만 확인
	if (!IsEqualGUID(
		record->EventHeader.ProviderId,
		RDOTP_TRACE_GUID_PROCESS_MANIFEST
	))
	{
		return;
	}

	ETWTraceManager* _this = (ETWTraceManager*)record->UserContext;
	if (_this == NULL)
	{
		return;
	}

	UCHAR opCode = record->EventHeader.EventDescriptor.Opcode;

	switch (opCode)
	{
		case EVENT_TRACE_TYPE_START:
		{
			DWORD pid = *(DWORD*)record->UserData;

			_this->_processManager.CheckIsStartedRemoteProcess(pid);
			
			break;
		}
		case EVENT_TRACE_TYPE_END:
		{
			DWORD pid = *(DWORD*)record->UserData;

			_this->_processManager.CheckIsEndedRemoteProcess(pid);

			break;
		}
	}
}