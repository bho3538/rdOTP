//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// CSampleProvider implements ICredentialProvider, which is the main
// interface that logonUI uses to decide which tiles to display.
// In this sample, we will display one tile that uses each of the nine
// available UI controls.

#include <initguid.h>
#include "CRdotpProvider.h"
#include "CRdotpCredential.h"
#include "guid.h"

LPWSTR g_DomainName = NULL;
LPWSTR g_UserName = NULL;
LPWSTR g_EncPassword = NULL;

DWORD g_DomainNameLen = 0;
DWORD g_UserNameLen = 0;
DWORD g_EncPasswordLen = 0;

CRdotpProvider::CRdotpProvider():
    _cRef(1),
    _pCredProviderUserArray(nullptr),
    _cpus(CPUS_INVALID)
{
    DllAddRef();
}

CRdotpProvider::~CRdotpProvider()
{
    _ReleaseEnumeratedCredentials();
    if (_pCredProviderUserArray != nullptr)
    {
        _pCredProviderUserArray->Release();
        _pCredProviderUserArray = nullptr;
    }

    DllRelease();
}

// SetUsageScenario is the provider's cue that it's going to be asked for tiles
// in a subsequent call.
HRESULT CRdotpProvider::SetUsageScenario(
    CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus,
    DWORD /*dwFlags*/)
{
    HRESULT hr;

    // Decide which scenarios to support here. Returning E_NOTIMPL simply tells the caller
    // that we're not designed for that scenario.
    switch (cpus)
    {
    case CPUS_LOGON:
    case CPUS_UNLOCK_WORKSTATION:
        // The reason why we need _fRecreateEnumeratedCredentials is because ICredentialProviderSetUserArray::SetUserArray() is called after ICredentialProvider::SetUsageScenario(),
        // while we need the ICredentialProviderUserArray during enumeration in ICredentialProvider::GetCredentialCount()
        _cpus = cpus;
        _fRecreateEnumeratedCredentials = true;
        hr = S_OK;
        break;

    case CPUS_CHANGE_PASSWORD:
    case CPUS_CREDUI:
        hr = E_NOTIMPL;
        break;

    default:
        hr = E_INVALIDARG;
        break;
    }

    return hr;
}

 //SetSerialization takes the kind of buffer that you would normally return to LogonUI for
 //an authentication attempt.  It's the opposite of ICredentialProviderCredential::GetSerialization.
 //GetSerialization is implement by a credential and serializes that credential.  Instead,
 //SetSerialization takes the serialization and uses it to create a tile.

 //SetSerialization is called for two main scenarios.  The first scenario is in the credui case
 //where it is prepopulating a tile with credentials that the user chose to store in the OS.
 //The second situation is in a remote logon case where the remote client may wish to
 //prepopulate a tile with a username, or in some cases, completely populate the tile and
 //use it to logon without showing any UI.

 //If you wish to see an example of SetSerialization, please see either the SampleCredentialProvider
 //sample or the SampleCredUICredentialProvider sample.  [The logonUI team says, "The original sample that
 //this was built on top of didn't have SetSerialization.  And when we decided SetSerialization was
 //important enough to have in the sample, it ended up being a non-trivial amount of work to integrate
 //it into the main sample.  We felt it was more important to get these samples out to you quickly than to
 //hold them in order to do the work to integrate the SetSerialization changes from SampleCredentialProvider
 //into this sample.]
HRESULT CRdotpProvider::SetSerialization(
    _In_ CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION const * pcpcs)
{

    if (!pcpcs) {
        return E_NOTIMPL;
    }

    //not RDOTP Credential
    if (pcpcs->clsidCredentialProvider != CLSID_RDOTPProvider) {
        return E_NOTIMPL;
    }

    ULONG package = 0;
    RetrieveNegotiateAuthPackage(&package);

    if (pcpcs->cbSerialization) {
        KERB_INTERACTIVE_UNLOCK_LOGON* pkiul = (KERB_INTERACTIVE_UNLOCK_LOGON*)pcpcs->rgbSerialization;
        if (pkiul && pkiul->Logon.MessageType == KerbInteractiveLogon) {

            BYTE* unpacked = (BYTE*)CoTaskMemAlloc(pcpcs->cbSerialization);
            if (unpacked) {
                CopyMemory(unpacked, pcpcs->rgbSerialization, pcpcs->cbSerialization);
                KerbInteractiveUnlockLogonUnpackInPlace((KERB_INTERACTIVE_UNLOCK_LOGON*)unpacked, pcpcs->cbSerialization);

                KERB_INTERACTIVE_UNLOCK_LOGON* aaa = (KERB_INTERACTIVE_UNLOCK_LOGON*)unpacked;

                g_DomainName = (LPWSTR)CoTaskMemAlloc(pkiul->Logon.LogonDomainName.Length + sizeof(WCHAR));
                if (!g_DomainName) {
                    return E_FAIL;
                }
                ZeroMemory(g_DomainName, pkiul->Logon.LogonDomainName.Length + sizeof(WCHAR));
                CopyMemory(g_DomainName, aaa->Logon.LogonDomainName.Buffer, aaa->Logon.LogonDomainName.Length);
                g_DomainNameLen = pkiul->Logon.LogonDomainName.Length;

                g_UserName = (LPWSTR)CoTaskMemAlloc(pkiul->Logon.UserName.Length + sizeof(WCHAR));
                if (!g_UserName) {
                    return E_FAIL;
                }
                ZeroMemory(g_UserName, pkiul->Logon.UserName.Length + sizeof(WCHAR));
                CopyMemory(g_UserName, aaa->Logon.UserName.Buffer, aaa->Logon.UserName.Length);
                g_UserNameLen = pkiul->Logon.UserName.Length;

                #pragma warning(suppress : 4996)
                _wcsupr(g_UserName);

                g_EncPassword = (LPWSTR)CoTaskMemAlloc(pkiul->Logon.Password.Length + sizeof(WCHAR));
                if (!g_EncPassword) {
                    return E_FAIL;
                }
                ZeroMemory(g_EncPassword, pkiul->Logon.Password.Length + sizeof(WCHAR));
                CopyMemory(g_EncPassword, aaa->Logon.Password.Buffer, aaa->Logon.Password.Length);
                g_EncPasswordLen = pkiul->Logon.Password.Length;

                SecureZeroMemory(unpacked, pcpcs->cbSerialization);
                CoTaskMemFree(unpacked);

                return S_OK;
            }
        }
    }

    

    return E_NOTIMPL;
}

// Called by LogonUI to give you a callback.  Providers often use the callback if they
// some event would cause them to need to change the set of tiles that they enumerated.
HRESULT CRdotpProvider::Advise(
    _In_ ICredentialProviderEvents * /*pcpe*/,
    _In_ UINT_PTR /*upAdviseContext*/)
{
    return E_NOTIMPL;
}

// Called by LogonUI when the ICredentialProviderEvents callback is no longer valid.
HRESULT CRdotpProvider::UnAdvise()
{
    return E_NOTIMPL;
}

// Called by LogonUI to determine the number of fields in your tiles.  This
// does mean that all your tiles must have the same number of fields.
// This number must include both visible and invisible fields. If you want a tile
// to have different fields from the other tiles you enumerate for a given usage
// scenario you must include them all in this count and then hide/show them as desired
// using the field descriptors.
HRESULT CRdotpProvider::GetFieldDescriptorCount(
    _Out_ DWORD *pdwCount)
{
    *pdwCount = SFI_NUM_FIELDS;
    return S_OK;
}

// Gets the field descriptor for a particular field.
HRESULT CRdotpProvider::GetFieldDescriptorAt(
    DWORD dwIndex,
    _Outptr_result_nullonfailure_ CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR **ppcpfd)
{
    HRESULT hr;
    *ppcpfd = nullptr;

    // Verify dwIndex is a valid field.
    if ((dwIndex < SFI_NUM_FIELDS) && ppcpfd)
    {
        hr = FieldDescriptorCoAllocCopy(s_rgCredProvFieldDescriptors[dwIndex], ppcpfd);
    }
    else
    {
        hr = E_INVALIDARG;
    }

    return hr;
}

 //Sets pdwCount to the number of tiles that we wish to show at this time.
 //Sets pdwDefault to the index of the tile which should be used as the default.
 //The default tile is the tile which will be shown in the zoomed view by default. If
 //more than one provider specifies a default the last used cred prov gets to pick
 //the default. If *pbAutoLogonWithDefault is TRUE, LogonUI will immediately call
 //GetSerialization on the credential you've specified as the default and will submit
 //that credential for authentication without showing any further UI.
HRESULT CRdotpProvider::GetCredentialCount(
    _Out_ DWORD *pdwCount,
    _Out_ DWORD *pdwDefault,
    _Out_ BOOL *pbAutoLogonWithDefault)
{
    *pdwDefault = CREDENTIAL_PROVIDER_NO_DEFAULT;

    if (_fRecreateEnumeratedCredentials)
    {
        _fRecreateEnumeratedCredentials = false;
        _ReleaseEnumeratedCredentials();
        _CreateEnumeratedCredentials();
    }

    if (g_UserName) {
        *pbAutoLogonWithDefault = TRUE;

        for (size_t i = 0; i < this->_pCredentials.size(); i++) {
            if (!wcscmp(this->_pCredentials[i]->GetCredUserName(), g_UserName)) {
                *pdwDefault = (DWORD)i;
                break;
            }
        }
    }
    else {
        *pbAutoLogonWithDefault = FALSE;
    }


    *pdwCount = (DWORD)this->_pCredentials.size();

    return S_OK;
}

// Returns the credential at the index specified by dwIndex. This function is called by logonUI to enumerate
// the tiles.
HRESULT CRdotpProvider::GetCredentialAt(
    DWORD dwIndex,
    _Outptr_result_nullonfailure_ ICredentialProviderCredential **ppcpc)
{
    HRESULT hr = E_INVALIDARG;

    if (dwIndex <= this->_pCredentials.size() && ppcpc)
    {
        hr = _pCredentials[dwIndex]->QueryInterface(IID_PPV_ARGS(ppcpc));
    }

    if (FAILED(hr)) {
        *ppcpc = nullptr;
    }

    return hr;
}

// This function will be called by LogonUI after SetUsageScenario succeeds.
// Sets the User Array with the list of users to be enumerated on the logon screen.
HRESULT CRdotpProvider::SetUserArray(_In_ ICredentialProviderUserArray *users)
{
    if (_pCredProviderUserArray)
    {
        _pCredProviderUserArray->Release();
    }
    _pCredProviderUserArray = users;
    _pCredProviderUserArray->AddRef();
    return S_OK;
}

void CRdotpProvider::_CreateEnumeratedCredentials()
{
    switch (_cpus)
    {
    case CPUS_LOGON:
    case CPUS_UNLOCK_WORKSTATION:
        {
            _EnumerateCredentials();
            break;
        }
    default:
        break;
    }
}

void CRdotpProvider::_ReleaseEnumeratedCredentials()
{
    if (!_pCredentials.empty())
    {
        for (size_t i = 0; i < _pCredentials.size(); i++) {
            _pCredentials[i]->Release();
        }
        _pCredentials.clear();
    }
}

HRESULT CRdotpProvider::_EnumerateCredentials()
{
    HRESULT hr = E_UNEXPECTED;
    if (_pCredProviderUserArray != nullptr)
    {
        DWORD dwUserCount;
        _pCredProviderUserArray->GetCount(&dwUserCount);
        if (dwUserCount > 0)
        {
            for (DWORD i = 0; i < dwUserCount; i++) {
                ICredentialProviderUser* pCredUser;
                hr = _pCredProviderUserArray->GetAt(i, &pCredUser);
                if (SUCCEEDED(hr))
                {
                    BOOL skip = FALSE;
                    //from RDP
                    if (g_UserName) {
                        LPWSTR userName = 0;
                        if (pCredUser->GetStringValue(PKEY_Identity_UserName, &userName) == S_OK) {
                            #pragma warning(suppress : 4996)
                            _wcsupr(userName);
                            if (wcscmp(g_UserName, userName)) {
                                skip = TRUE;
                            }
                            CoTaskMemFree(userName);
                        }
                    }

                    if (!skip) {
                        CRDotpCredential* pCred = new(std::nothrow) CRDotpCredential();
                        if (pCred != nullptr)
                        {
                            hr = pCred->Initialize(_cpus, s_rgCredProvFieldDescriptors, s_rgFieldStatePairs, pCredUser);
                            if (FAILED(hr))
                            {
                                pCred->Release();
                            }
                            else {
                                this->_pCredentials.push_back(pCred);
                            }
                        }
                        else
                        {
                            hr = E_OUTOFMEMORY;
                        }
                    }

                    pCredUser->Release();
                }
            }
        }
    }
    return hr;
}

// Boilerplate code to create our provider.
HRESULT CSample_CreateInstance(_In_ REFIID riid, _Outptr_ void **ppv)
{
    HRESULT hr;
    CRdotpProvider *pProvider = new(std::nothrow) CRdotpProvider();
    if (pProvider)
    {
        hr = pProvider->QueryInterface(riid, ppv);
        pProvider->Release();
    }
    else
    {
        hr = E_OUTOFMEMORY;
    }
    return hr;
}
