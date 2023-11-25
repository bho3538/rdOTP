#include "CRdotpFilter.h"
#include <new>

EXTERN_C GUID CLSID_RDOTPProvider;

HRESULT CRdotpFilter::Filter(
    /* [in] */ CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus,
    /* [in] */ DWORD dwFlags,
    /* [annotation][size_is][in] */
    _In_reads_(cProviders)  GUID* rgclsidProviders,
    /* [annotation][size_is][out][in] */
    _Inout_updates_(cProviders)  BOOL* rgbAllow,
    /* [in] */ DWORD cProviders) {

    BOOL isRemoteSession = IsRemoteSession();

    for (DWORD i = 0; i < cProviders; i++) {
        if (rgclsidProviders[i] == CLSID_RDOTPProvider) {
            rgbAllow[i] = isRemoteSession;
        }
        else {
            rgbAllow[i] = !isRemoteSession;
        }
    }

    return S_OK;
}

HRESULT CRdotpFilter::UpdateRemoteCredential(
    /* [annotation][in] */
    _In_  const CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION* pcpcsIn,
    /* [annotation][out] */
    _Out_  CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION* pcpcsOut) {
    if (!pcpcsIn) {
        return E_INVALIDARG;
    }

    pcpcsOut->ulAuthenticationPackage = pcpcsIn->ulAuthenticationPackage;
    pcpcsOut->cbSerialization = pcpcsIn->cbSerialization;
    pcpcsOut->rgbSerialization = pcpcsIn->rgbSerialization;
    pcpcsOut->clsidCredentialProvider = CLSID_RDOTPProvider;

    if (pcpcsIn->cbSerialization > 0) {
        pcpcsOut->rgbSerialization = (BYTE*)CoTaskMemAlloc(pcpcsIn->cbSerialization);

        if (pcpcsOut->rgbSerialization) {
            CopyMemory(pcpcsOut->rgbSerialization, pcpcsIn->rgbSerialization, pcpcsIn->cbSerialization);
            return S_OK;
        }
    }
    else
    {
        return E_NOTIMPL;
    }

    return E_NOTIMPL;
}

HRESULT CProviderFilter_CreateInstance(_In_ REFIID riid, _Outptr_ void** ppv)
{
    HRESULT hr;
    CRdotpFilter* pFilter = new(std::nothrow) CRdotpFilter();
    if (pFilter)
    {
        hr = pFilter->QueryInterface(riid, ppv);
        pFilter->Release();
    }
    else
    {
        hr = E_OUTOFMEMORY;
    }
    return hr;
}