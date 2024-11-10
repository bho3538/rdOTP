#pragma once

BOOL RDOTP_InitializeAuthWindow(HWND hwnd);
HWND RDOTP_CreateAuthWindow();
BOOL RDOTP_ShowAuthWindow();

LRESULT CALLBACK _RDOTP_AuthWindow_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
HFONT _RDTP_SetLabelFont(HWND hLabel, DWORD dwFontSize);
void _RDOTP_CloseAndCleanupControls();

BOOL _RDOTP_ProcessAuth(LPCWSTR pOtpCode);

void _RDOTP_HandleAuthTimer();

INT _GetSystemDPI();
DWORD _CalcPos(DWORD originalPos);