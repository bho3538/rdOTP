#pragma once

using namespace System;

namespace rdOTPWrap {
	public ref class RDOtpWrapper
	{
		// TODO: 여기에 이 클래스에 대한 메서드를 추가합니다.
	public:
		int Show();
	};
}

extern "C" {
	__declspec(dllexport) void* RDOTPWrapper_CreateInstance();
	_declspec(dllexport) int RDOTPWrapper_Show(void* obj);
	__declspec(dllexport) void RDOTPWrapper_Cleanup(void* obj);

}