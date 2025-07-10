#pragma once

#include <tdh.h>
#include <evntrace.h>
#include <evntcons.h>

#include "ProcessManager.h"

class ETWTraceManager
{
public:
	ETWTraceManager();
	~ETWTraceManager();

	bool Initialize();
	void Release();

	void Start();
	void Stop();

private:
	bool _requestStop;
	HANDLE _eventTraceThread;

	TRACEHANDLE _traceSession;
	EVENT_TRACE_PROPERTIES* _traceProperties;

	ProcessManager _processManager;

	bool InitializeSession();

	static DWORD WINAPI TraceThread(
		PVOID args
	);

	static void WINAPI TraceEventCallback(
		EVENT_RECORD* record
	);

};

