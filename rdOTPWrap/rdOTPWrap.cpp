#include "pch.h"

#include "rdOTPWrap.h"

using namespace rdOTPWrap;
using namespace System::Runtime::InteropServices;

int RDOtpWrapper::Show() {
	rdOTP::AuthForm^ form = gcnew rdOTP::AuthForm();
	if (form->ShowAndValidateCode()) {
		return 0;
	}
	else {
		return 1;
	}
}

//dll load path
System::Reflection::Assembly^ currentDomain_AssemblyResolve(Object^ sender, ResolveEventArgs^ args)
{
	//// If this is an mscorlib, do a bare load
	//if (args->Name->Length >= 8 && args->Name->Substring(0, 8) == L"mscorlib")
	//{
	//	return System::Reflection::Assembly::Load(args->Name->Substring(0, args->Name->IndexOf(L",")) + L".dll");
	//}


	// Load the assembly from the specified path
	String^ finalPath = nullptr;
	try
	{
		String^ programFiles = Environment::GetFolderPath(Environment::SpecialFolder::ProgramFiles);
		programFiles += "\\rdOTP\\";
		finalPath = gcnew String(programFiles) + args->Name->Substring(0, args->Name->IndexOf(",")) + ".dll";

		if (System::IO::File::Exists(finalPath)) {
			System::Reflection::Assembly^ retval = System::Reflection::Assembly::LoadFrom(finalPath);
			return retval;
		}

		finalPath = gcnew String(programFiles) + args->Name->Substring(0, args->Name->IndexOf(",")) + ".exe";

		if (System::IO::File::Exists(finalPath)) {
			System::Reflection::Assembly^ retval = System::Reflection::Assembly::LoadFrom(finalPath);
			return retval;
		}
	}
	catch (Exception^ e)
	{
		System::Diagnostics::Trace::WriteLine(e);
	}

	return nullptr;
}

__declspec(dllexport) void* RDOTPWrapper_CreateInstance() {
	AppDomain^ currentDomain = AppDomain::CurrentDomain;
	currentDomain->AssemblyResolve += gcnew ResolveEventHandler(currentDomain_AssemblyResolve);


	RDOtpWrapper^ wrapper = gcnew RDOtpWrapper();

	return (void*)((IntPtr)GCHandle::Alloc(wrapper));
}

_declspec(dllexport) int RDOTPWrapper_Show(void* obj) {
	GCHandle hObj = GCHandle::FromIntPtr((IntPtr)obj);

	RDOtpWrapper^ wrapper = (RDOtpWrapper^)hObj.Target;
	return wrapper->Show();
}

__declspec(dllexport) void RDOTPWrapper_Cleanup(void* obj) {
	if (obj) {
		GCHandle hObj = GCHandle::FromIntPtr((IntPtr)obj);
		hObj.Free();
	}
}
