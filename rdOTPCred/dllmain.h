//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
//

#pragma once

// global dll hinstance
extern HINSTANCE g_hinst;
#define HINST_THISDLL g_hinst

void DllAddRef();
void DllRelease();

STDAPI DllCanUnloadNow();
STDAPI DllGetClassObject(__in REFCLSID rclsid, __in REFIID riid, __deref_out void** ppv);
STDAPI DllRegisterServer();
STDAPI DllUnregisterServer();

BOOL CreateAndWriteRegistry(HKEY hiveKey, LPCWSTR key, LPCWSTR valueName, LPCWSTR strValue);
BOOL DeleteRegistry(HKEY hiveKey, LPCWSTR key);

#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib , "Credui.lib")
#pragma comment(lib, "Secur32.lib")
