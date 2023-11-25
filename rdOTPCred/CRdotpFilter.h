#pragma once

#include "helpers.h"
#include <windows.h>

class CRdotpFilter : public ICredentialProviderFilter
{
public:
    // IUnknown
    IFACEMETHODIMP_(ULONG) AddRef()
    {
        return ++_cRef;
    }

    IFACEMETHODIMP_(ULONG) Release()
    {
        long cRef = --_cRef;
        if (!cRef)
        {
            delete this;
        }
        return cRef;
    }

    IFACEMETHODIMP QueryInterface(_In_ REFIID riid, _COM_Outptr_ void** ppv)
    {
        static const QITAB qit[] =
        {
            QITABENT(CRdotpFilter, ICredentialProviderFilter), // ICredentialProviderFilter
            {0},
        };
        return QISearch(this, qit, riid, ppv);
    }

public:
    IFACEMETHODIMP Filter(
        /* [in] */ CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus,
        /* [in] */ DWORD dwFlags,
        /* [annotation][size_is][in] */
        _In_reads_(cProviders)  GUID* rgclsidProviders,
        /* [annotation][size_is][out][in] */
        _Inout_updates_(cProviders)  BOOL* rgbAllow,
        /* [in] */ DWORD cProviders);

    IFACEMETHODIMP UpdateRemoteCredential(
        /* [annotation][in] */
        _In_  const CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION* pcpcsIn,
        /* [annotation][out] */
        _Out_  CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION* pcpcsOut);


    friend HRESULT CProviderFilter_CreateInstance(_In_ REFIID riid, _Outptr_ void** ppv);


private:
    long                                    _cRef = 1;            // Used for reference counting.
};