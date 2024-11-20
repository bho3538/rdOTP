#pragma once

__declspec(dllexport)  BOOL RDOTP_InitializeAuthWindow(HWND hwnd);
__declspec(dllexport) HWND RDOTP_CreateAuthWindow();
__declspec(dllexport) BOOL RDOTP_ShowAuthWindow();


LRESULT CALLBACK _RDOTP_AuthWindow_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK _RDOTP_InputCodeCtrl_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HFONT _RDTP_SetLabelFont(HWND hLabel, DWORD dwFontSize);
void _RDOTP_CloseAndCleanupControls();

BOOL _RDOTP_ProcessAuth(LPCWSTR pOtpCode);

void _RDOTP_HandleAuthTimer();

INT _GetSystemDPI();
DWORD _CalcPos(DWORD originalPos);