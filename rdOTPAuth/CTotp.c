#include "pch.h"
#include "CTotp.h"

#include <stdio.h>
#include <bcrypt.h>
#include <time.h>
#include <math.h>

#define _TIME_STEP 30
#define _AUTH_CODE_LEN 6
#define _BASE32_CODE "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"


BOOL RDOTP_ValidateCode(LPCWSTR userInputCode) {
    if (!userInputCode || wcslen(userInputCode) != _AUTH_CODE_LEN) {
        return FALSE;
    }

    BOOL isValid = FALSE;
	// load secret key from registry
	char secretKeyStr[] = "";

	// scrent key (decode BASE32)
    BYTE secretKey[20];
    if (!_RDOTP_DecodeBase32(secretKeyStr, sizeof(secretKeyStr), secretKey, sizeof(secretKey))) {
        // invalid secret key (decode failed)
        return isValid;
    }

    // before 30 seconds, now, after 30 seconds (To compensate for time errors between devices)
    LPWSTR validCodes[3] = { 0, };
    LONGLONG times[3];
    
    times[0] = time(0);
    times[1] = times[0] - 30; // before 30 seconds
    times[2] = times[0] + 30; // after 30 seconds

    for (int i = 0; i < ARRAYSIZE(validCodes); i++) {
        LONGLONG baseTime = times[i] / _TIME_STEP;
        validCodes[i] = (LPWSTR)malloc((_AUTH_CODE_LEN + 1) * sizeof(WCHAR));
        if (!validCodes[i]) {
            break;
        }

        if (_RDOTP_GenerateAuthCode(baseTime, secretKey, sizeof(secretKey), _AUTH_CODE_LEN, validCodes[i]) != 0) {
            break;
        }

        if (!wcscmp(validCodes[i], userInputCode)) {
            isValid = TRUE;
            break;
        }
    }

    for (int i = 0; i < ARRAYSIZE(validCodes); i++) {
        if (validCodes[i]) {
            memset(validCodes[i], 0, (_AUTH_CODE_LEN + 1) * sizeof(WCHAR));
            free(validCodes[i]);
        }
    }

	return isValid;
}

BOOL _RDOTP_DecodeBase32(LPCSTR encodedKey, DWORD keyLen, BYTE* decodedKey, DWORD decodedKeyLen) {
    int buffer = 0, bits_left = 0;
    size_t count = 0;
    size_t i, index;

    for (i = 0; encodedKey[i] != '\0' && count < decodedKeyLen; i++) {
        char* ptr = strchr(_BASE32_CODE, encodedKey[i]);
        if (!ptr) {
            return FALSE;
        }

        index = ptr - _BASE32_CODE;
        buffer <<= 5;
        buffer |= index;
        bits_left += 5;

        if (bits_left >= 8) {
            decodedKey[count++] = (DWORD)(buffer >> (bits_left - 8));
            bits_left -= 8;
        }
    }

    return TRUE;
}

DWORD _RDOTP_GenerateAuthCode(time_t baseTime, BYTE* decodedSecretKey, DWORD decodedSecretKeyLen, DWORD authCodeLen, LPWSTR generatedAuthCodeBuffer) {
    BCRYPT_ALG_HANDLE hAlg = NULL;
    BCRYPT_HASH_HANDLE hHash = NULL;
    BYTE hash[20];
    DWORD offset = 0;
    DWORD numCode = 0;

    NTSTATUS status;

    if (!decodedSecretKey || !generatedAuthCodeBuffer || authCodeLen == 0) {
        return 1;
    }

    status = BCryptOpenAlgorithmProvider(&hAlg, BCRYPT_SHA1_ALGORITHM, NULL, BCRYPT_ALG_HANDLE_HMAC_FLAG);
    if (status != 0) {
        goto escapeArea;
    }

    status = BCryptCreateHash(hAlg, &hHash, NULL, 0, decodedSecretKey, decodedSecretKeyLen, 0);
    if (status != 0) {
        goto escapeArea;
    }

    BYTE bigEndianTime[8];
    for (INT i = 7; i >= 0; i--) {
        bigEndianTime[i] = (BYTE)(baseTime & 0xff);
        baseTime >>= 8;
    }

    status = BCryptHashData(hHash, bigEndianTime, sizeof(bigEndianTime), 0);
    if (status != 0) {
        goto escapeArea;
    }

    status = BCryptFinishHash(hHash, hash, sizeof(hash), 0);
    if (status != 0) {
        goto escapeArea;
    }

    offset = hash[19] & 0x0F;
    numCode = ((hash[offset] & 0x7F) << 24) | ((hash[offset + 1] & 0xFF) << 16) | ((hash[offset + 2] & 0xFF) << 8) | (hash[offset + 3] & 0xFF);
    numCode %= (DWORD)pow(10, authCodeLen);


    WCHAR format[12];
    _snwprintf_s(format, ARRAYSIZE(format), _TRUNCATE, L"%%0%dd", authCodeLen);
    _snwprintf_s(generatedAuthCodeBuffer, (size_t)authCodeLen + 1, _TRUNCATE, format, numCode);

escapeArea:
    if (hHash) {
        BCryptDestroyHash(hHash);
    }

    if (hAlg) {
        BCryptCloseAlgorithmProvider(hAlg, 0);
    }


    return status;
}