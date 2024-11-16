#pragma once

BOOL RDOTP_ValidateCode(LPCWSTR userInputCode);

BOOL _RDOTP_DecodeBase32(LPCSTR encodedKey, DWORD keyLen, BYTE* decodedKey, DWORD);


DWORD _RDOTP_GenerateAuthCode(time_t baseTime, BYTE* decodedSecretKey, DWORD decodedSecretKeyLen, DWORD authCodeLen, LPWSTR generatedAuthCodeBuffer);