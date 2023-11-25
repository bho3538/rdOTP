//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Standard dll required functions and class factory implementation.

#include <windows.h>
#include <unknwn.h>
#include "dllmain.h"
#include "helpers.h"

static long g_cRef = 0;   // global dll reference count
HINSTANCE g_hinst = NULL; // global dll hinstance

extern HRESULT CSample_CreateInstance(__in REFIID riid, __deref_out void** ppv);
extern HRESULT CProviderFilter_CreateInstance(__in REFIID riid, __deref_out void** ppv);
EXTERN_C GUID CLSID_RDOTPProvider;
EXTERN_C GUID CLSID_RDOTPFilter;

class CClassFactory : public IClassFactory
{
public:
    CClassFactory(REFIID rclsid) : _cRef(1)
    {
        CopyMemory(&this->_clsid, (PVOID)&rclsid, sizeof(GUID));
    }

    // IUnknown
    IFACEMETHODIMP QueryInterface(__in REFIID riid, __deref_out void **ppv)
    {
        static const QITAB qit[] =
        {
            QITABENT(CClassFactory, IClassFactory),
            { 0 },
        };
        return QISearch(this, qit, riid, ppv);
    }

    IFACEMETHODIMP_(ULONG) AddRef()
    {
        return InterlockedIncrement(&_cRef);
    }

    IFACEMETHODIMP_(ULONG) Release()
    {
        long cRef = InterlockedDecrement(&_cRef);
        if (!cRef)
            delete this;
        return cRef;
    }

    // IClassFactory
    IFACEMETHODIMP CreateInstance(__in IUnknown* pUnkOuter, __in REFIID riid, __deref_out void **ppv)
    {
        HRESULT hr;
        if (!pUnkOuter)
        {
            if (this->_clsid == CLSID_RDOTPProvider) {
                hr = CSample_CreateInstance(riid, ppv);
            }
            else if (this->_clsid == CLSID_RDOTPFilter) {
                hr = CProviderFilter_CreateInstance(riid, ppv);
            }
        }
        else
        {
            *ppv = NULL;
            hr = CLASS_E_NOAGGREGATION;
        }
        return hr;
    }

    IFACEMETHODIMP LockServer(__in BOOL bLock)
    {
        if (bLock)
        {
            DllAddRef();
        }
        else
        {
            DllRelease();
        }
        return S_OK;
    }

private:
    ~CClassFactory()
    {
    }

    GUID _clsid = { 0, };

    long _cRef;
};

HRESULT CClassFactory_CreateInstance(__in REFCLSID rclsid, __in REFIID riid, __deref_out void **ppv)
{
    *ppv = NULL;

    HRESULT hr;

    CClassFactory* pcf = new CClassFactory(rclsid);
    if (pcf)
    {
        hr = pcf->QueryInterface(riid, ppv);
        pcf->Release();
    }
    else
    {
        hr = CLASS_E_CLASSNOTAVAILABLE;
    }
    return hr;
}

void DllAddRef()
{
    InterlockedIncrement(&g_cRef);
}

void DllRelease()
{
    InterlockedDecrement(&g_cRef);
}

STDAPI DllCanUnloadNow()
{
    return (g_cRef > 0) ? S_FALSE : S_OK;
}

STDAPI DllGetClassObject(__in REFCLSID rclsid, __in REFIID riid, __deref_out void** ppv)
{
    return CClassFactory_CreateInstance(rclsid, riid, ppv);
}

STDAPI DllRegisterServer() {
    CreateAndWriteRegistry(HKEY_CLASSES_ROOT, L"CLSID\\{0C34E73F-B241-48F3-8C7C-C5C7698BF718}", NULL, L"rdOTPCredFilter");
    CreateAndWriteRegistry(HKEY_CLASSES_ROOT, L"CLSID\\{0C34E73F-B241-48F3-8C7C-C5C7698BF718}\\InprocServer32", NULL, L"C:\\Program Files\\rdotp\\rdOTPCred.dll");
    CreateAndWriteRegistry(HKEY_CLASSES_ROOT, L"CLSID\\{0C34E73F-B241-48F3-8C7C-C5C7698BF718}\\InprocServer32", L"ThreadingModel", L"Apartment");

    CreateAndWriteRegistry(HKEY_CLASSES_ROOT, L"CLSID\\{0C34E73F-B241-48F3-8C7C-C5C7698BF717}", NULL, L"rdOTPCred");
    CreateAndWriteRegistry(HKEY_CLASSES_ROOT, L"CLSID\\{0C34E73F-B241-48F3-8C7C-C5C7698BF717}\\InprocServer32", NULL, L"C:\\Program Files\\rdotp\\rdOTPCred.dll");
    CreateAndWriteRegistry(HKEY_CLASSES_ROOT, L"CLSID\\{0C34E73F-B241-48F3-8C7C-C5C7698BF717}\\InprocServer32", L"ThreadingModel", L"Apartment");

    CreateAndWriteRegistry(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Authentication\\Credential Providers\\{0C34E73F-B241-48F3-8C7C-C5C7698BF717}",
        NULL, L"rdOTPCred");
    CreateAndWriteRegistry(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Authentication\\Credential Provider Filters\\{0C34E73F-B241-48F3-8C7C-C5C7698BF718}",
        NULL, L"rdOTPCredFilter");
    return 0;
}
STDAPI DllUnregisterServer() {
    DeleteRegistry(HKEY_CLASSES_ROOT, L"CLSID\\{0C34E73F-B241-48F3-8C7C-C5C7698BF718}\\InprocServer32");
    DeleteRegistry(HKEY_CLASSES_ROOT, L"CLSID\\{0C34E73F-B241-48F3-8C7C-C5C7698BF718}");

    DeleteRegistry(HKEY_CLASSES_ROOT, L"CLSID\\{0C34E73F-B241-48F3-8C7C-C5C7698BF717}\\InprocServer32");
    DeleteRegistry(HKEY_CLASSES_ROOT, L"CLSID\\{0C34E73F-B241-48F3-8C7C-C5C7698BF717}");

    DeleteRegistry(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Authentication\\Credential Providers\\{0C34E73F-B241-48F3-8C7C-C5C7698BF717}");
    DeleteRegistry(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Authentication\\Credential Provider Filters\\{0C34E73F-B241-48F3-8C7C-C5C7698BF718}");

    return 0;
}

BOOL CreateAndWriteRegistry(HKEY hiveKey, LPCWSTR key, LPCWSTR valueName, LPCWSTR strValue) {
    HKEY regKey = 0;
    DWORD op = 0;
    LRESULT re = RegCreateKeyExW(hiveKey, key, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &regKey, &op);
    if (re == NO_ERROR && strValue) {
        re = RegSetValueExW(regKey, valueName, 0, REG_SZ, (BYTE*)strValue, (wcslen(strValue) + 1) * 2);
        RegCloseKey(regKey);
    }

    return re == 0 ? TRUE : FALSE;
}
BOOL DeleteRegistry(HKEY hiveKey, LPCWSTR key) {

    RegDeleteKeyExW(hiveKey, key, NULL, NULL);

    return FALSE;
}

STDAPI_(BOOL) DllMain(__in HINSTANCE hinstDll, __in DWORD dwReason, __in void *)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hinstDll);
        break;
    case DLL_PROCESS_DETACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    }

    g_hinst = hinstDll;
    return TRUE;
}

