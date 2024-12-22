﻿#include "pch.h"
#include "CAuthWindow.h"
#include "resource.h"

#include <math.h>
#include "CTotp.h"

HWND g_ParentWindow = NULL;
HWND g_AuthWindowHwnd = NULL;
ATOM g_MainWindowClass = (ATOM)NULL;
HBRUSH g_TransParentBtnBk = NULL;

// controls
HWND g_MainTitleLabelHwnd = NULL;
DWORD g_MainTitleLabelX = 15;
DWORD g_MainTitleLabelY = 15;
DWORD g_MainTitleLabelWidth = 205;
DWORD g_MainTitleLabelHeight = 25;
HFONT g_MainTitleLabelFont = NULL;
DWORD g_MainTItleLabelFontSize = 23;

HWND g_SubTitleLabelHwnd = NULL;
DWORD g_SubTitleLabelX = 15;
DWORD g_SubTitleLabelY = 45;
DWORD g_SubTitleLabelWidth = 280;
DWORD g_SubTitleLabelHeight = 20;
HFONT g_SubTitleLabelFont = NULL;
DWORD g_SubTitleLabelFontSize = 16;

HWND g_InputCodeTextboxHwnd = NULL;
DWORD g_InputCodeTextboxX = 10;
DWORD g_InputCodeTextboxY = 70;
DWORD g_InputCodeTextboxWidth = 380;
DWORD g_InputCodeTextboxHeight = 23;
HFONT g_InputCodeTextboxFont = NULL;
DWORD g_InputCodeTextboxFontSize = 18;
LONG_PTR g_InputCodeTextboxOrigProc = 0;

HWND g_SubmitBtnHwnd = NULL;
DWORD g_SubmitBtnX = 260;
DWORD g_SubmitBtnY = 160;
DWORD g_SubmitBtnWidth = 60;
DWORD g_SubmitBtnHeight = 30;
HFONT g_SubmitBtnFont = NULL;
DWORD g_SubmitBtnFontSize = 16;

HWND g_CancelBtnHwnd = NULL;
DWORD g_CancelBtnX = 330;
DWORD g_CancelBtnY = 160;
DWORD g_CancelBtnWidth = 60;
DWORD g_CancelBtnHeight = 30;
HFONT g_CancelBtnFont = NULL;
DWORD g_CancelBtnFontSize = 16;

HWND g_LockIconHwnd = NULL;
DWORD g_LockIconX = 340;
DWORD g_LockIconY = 10;
DWORD g_LockIconWidth = 48;
DWORD g_LockIconHeight = 48;
HICON g_LockIcon = NULL;

HWND g_AuthTimeLeftLabelHwnd = NULL;
DWORD g_AuthTimeLeftLabelX = 15;
DWORD g_AuthTimeLeftLabelY = 145;
DWORD g_AuthTimeLeftLabelWidth = 230;
DWORD g_AuthTimeLeftLabelHeight = 23;
HFONT g_AuthTimeLeftLabelFont = NULL;
DWORD g_AuthTimeLeftLabelFontSize = 15;

HWND g_MachineTimeLabelHwnd = NULL;
DWORD g_MachineTimeLabelX = 15;
DWORD g_MachineTimeLabelY = 175;
DWORD g_MachineTimeLabelWidth = 210;
DWORD g_MachineTimeLabelHeight = 23;
HFONT g_MachineTimeLabelFont = NULL;
DWORD g_MachineTimeLabelFontSize = 15;

HWND g_AuthCodeNotValidLabelHwnd = NULL;
DWORD g_AuthCodeNotValidLabelX = 15;
DWORD g_AuthCodeNotValidLabelY = 100;
DWORD g_AuthCodeNotValidLabelWidth = 200;
DWORD g_AuthCodeNotValidLabelHeight = 23;
HFONT g_AuthCodeNotValidLabelFont = NULL;
DWORD g_AuthCodeNotValidLabelFontSize = 15;
BOOL g_AuthCodeNotValidDisplayed = FALSE;

DWORD g_FailedAuthCnt = 0;


// end controls

DWORD g_MainWindowX = 0;
DWORD g_MainWindowY = 0;
DWORD g_MainWindowWidth = 400;
DWORD g_MainWindowHeight = 200;
FLOAT g_scale = 1;
DWORD g_Time = 0;

BOOL g_AuthValid = FALSE;

#define BTN_SUBMIT 100
#define BTN_CANCEL 101

#define MAX_INPUTCODE_LEN 16
#define MAX_AUTH_TIME 40

#define AUTH_TIMER 1


_declspec(dllexport) BOOL RDOTP_InitializeAuthWindow(HWND hwnd) {
	if (!hwnd) {
		hwnd = GetForegroundWindow();
	}

    INT dpi = _GetSystemDPI();
    if (dpi > 96) {
        g_scale = dpi / 96.0f;
    }

    g_ParentWindow = hwnd;

    WNDCLASSEX wc = { 0, };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = _RDOTP_AuthWindow_WndProc;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"RDOTP_AuthWindow";

    g_MainWindowClass = RegisterClassExW(&wc);
    if (!g_MainWindowClass) {
        return FALSE;
    }

    g_TransParentBtnBk = GetSysColorBrush(COLOR_WINDOW);
    g_FailedAuthCnt = 0;

	return TRUE;
}

_declspec(dllexport) HWND RDOTP_CreateAuthWindow() {
    // Show auth window at screen center
    DWORD screenX = GetSystemMetrics(SM_CXSCREEN);
    DWORD screenY = GetSystemMetrics(SM_CYSCREEN);

    // hack
    if (g_scale == 1 && screenX > 3000) {
        g_scale = 2;
    }

    DWORD windowWidth = _CalcPos(g_MainWindowWidth);
    DWORD windowHeight = _CalcPos(g_MainWindowHeight);

    g_MainWindowX = (screenX - windowWidth) / 2;
    g_MainWindowY = (screenY - windowHeight) / 2;

    if (g_MainWindowX < 0) {
        g_MainWindowX = 20;
    }

    if (g_MainWindowY < 0) {
        g_MainWindowY = 20;
    }

    g_AuthWindowHwnd = CreateWindowExW(WS_EX_TOPMOST, L"RDOTP_AuthWindow", L"MainWindow", WS_POPUPWINDOW, (g_MainWindowX), (g_MainWindowY),
        windowWidth, windowHeight, g_ParentWindow, NULL, NULL, NULL);
    if (!g_AuthWindowHwnd) {
        return NULL;
    }

    // main title label
    g_MainTitleLabelHwnd = CreateWindowW(L"static", L"Autherication Required", WS_CHILD, _CalcPos(g_MainTitleLabelX), _CalcPos(g_MainTitleLabelY), _CalcPos(g_MainTitleLabelWidth),
        _CalcPos(g_MainTitleLabelHeight), g_AuthWindowHwnd, NULL, NULL, NULL);
    if (!g_MainTitleLabelHwnd) {
        return NULL;
    }
    g_MainTitleLabelFont = _RDTP_SetLabelFont(g_MainTitleLabelHwnd, g_MainTItleLabelFontSize);
    ShowWindow(g_MainTitleLabelHwnd, SW_SHOW);

    g_SubTitleLabelHwnd = CreateWindowW(L"static", L"Enter OTP code from registered phone", WS_CHILD, _CalcPos(g_SubTitleLabelX), _CalcPos(g_SubTitleLabelY), _CalcPos(g_SubTitleLabelWidth),
        _CalcPos(g_SubTitleLabelHeight), g_AuthWindowHwnd, NULL, NULL, NULL);
    if (!g_SubTitleLabelHwnd) {
        return NULL;
    }
    g_SubTitleLabelFont = _RDTP_SetLabelFont(g_SubTitleLabelHwnd, g_SubTitleLabelFontSize);
    ShowWindow(g_SubTitleLabelHwnd, SW_SHOW);

    // validate code edit control
    g_InputCodeTextboxHwnd = CreateWindowW(L"edit", L"", WS_CHILD | WS_BORDER | ES_CENTER, _CalcPos(g_InputCodeTextboxX), _CalcPos(g_InputCodeTextboxY), _CalcPos(g_InputCodeTextboxWidth),
        _CalcPos(g_InputCodeTextboxHeight), g_AuthWindowHwnd, NULL, NULL, NULL);
    if (!g_InputCodeTextboxHwnd) {
        return NULL;
    }
    g_InputCodeTextboxFont = _RDTP_SetLabelFont(g_InputCodeTextboxHwnd, g_InputCodeTextboxFontSize);
    g_InputCodeTextboxOrigProc = GetWindowLongPtrW(g_InputCodeTextboxHwnd, GWLP_WNDPROC);

    // handle 'Enter' key at edit control
    SetWindowLongPtrW(g_InputCodeTextboxHwnd, GWLP_WNDPROC, (LONG_PTR)_RDOTP_InputCodeCtrl_WndProc);
    ShowWindow(g_InputCodeTextboxHwnd, SW_SHOW);
    SendMessageW(g_InputCodeTextboxHwnd, EM_SETLIMITTEXT, MAX_INPUTCODE_LEN - 1, (LPARAM)NULL);

    // submit auth code
    g_SubmitBtnHwnd = CreateWindowW(L"button", L"Submit", WS_CHILD, _CalcPos(g_SubmitBtnX), _CalcPos(g_SubmitBtnY), _CalcPos(g_SubmitBtnWidth),
        _CalcPos(g_SubmitBtnHeight), g_AuthWindowHwnd, (HMENU)BTN_SUBMIT, NULL, NULL);
    if (!g_SubmitBtnHwnd) {
        return NULL;
    }
    g_SubmitBtnFont = _RDTP_SetLabelFont(g_SubmitBtnHwnd, g_SubmitBtnFontSize);
    ShowWindow(g_SubmitBtnHwnd, SW_SHOW);

    // close auth dialog button
    g_CancelBtnHwnd = CreateWindowW(L"button", L"Cancel", WS_CHILD, _CalcPos(g_CancelBtnX), _CalcPos(g_CancelBtnY), _CalcPos(g_CancelBtnWidth),
        _CalcPos(g_CancelBtnHeight), g_AuthWindowHwnd, (HMENU)BTN_CANCEL, NULL, NULL);
    if (!g_CancelBtnHwnd) {
        return NULL;
    }
    g_CancelBtnFont = _RDTP_SetLabelFont(g_CancelBtnHwnd, g_CancelBtnFontSize);
    ShowWindow(g_CancelBtnHwnd, SW_SHOW);
     
    // LOCK image icon
    LPCWSTR iconType = MAKEINTRESOURCE(IDI_ICON1);
    if (g_scale >= 2) {
        iconType = MAKEINTRESOURCE(IDI_ICON2);
    }
    g_LockIcon = (HICON)LoadImageW(GetModuleHandleW(L"rdOTPAuth.dll"), iconType, IMAGE_ICON, _CalcPos(g_LockIconWidth), _CalcPos(g_LockIconHeight), LR_DEFAULTCOLOR);
    g_LockIconHwnd = CreateWindowW(L"static", L"", WS_CHILD | SS_ICON, _CalcPos(g_LockIconX), _CalcPos(g_LockIconY), _CalcPos(g_LockIconWidth),
        _CalcPos(g_LockIconHeight), g_AuthWindowHwnd, NULL, NULL, NULL);
    if (!g_LockIconHwnd) {
        return NULL;
    }

    SendMessageW(g_LockIconHwnd, STM_SETIMAGE, IMAGE_ICON, (LPARAM)g_LockIcon);
    ShowWindow(g_LockIconHwnd, SW_SHOW);

    // current machine time label
    g_MachineTimeLabelHwnd = CreateWindowW(L"static", L"Machine Time : ", WS_CHILD, _CalcPos(g_MachineTimeLabelX), _CalcPos(g_MachineTimeLabelY), _CalcPos(g_MachineTimeLabelWidth),
        _CalcPos(g_MachineTimeLabelHeight), g_AuthWindowHwnd, NULL, NULL, NULL);
    if (!g_MachineTimeLabelHwnd) {
        return NULL;
    }
    g_MachineTimeLabelFont = _RDTP_SetLabelFont(g_MachineTimeLabelHwnd, g_MachineTimeLabelFontSize);
    ShowWindow(g_MachineTimeLabelHwnd, SW_SHOW);

    // auth left time label
    g_AuthTimeLeftLabelHwnd = CreateWindowW(L"static", L"", WS_CHILD, _CalcPos(g_AuthTimeLeftLabelX), _CalcPos(g_AuthTimeLeftLabelY), _CalcPos(g_AuthTimeLeftLabelWidth),
        _CalcPos(g_AuthTimeLeftLabelHeight), g_AuthWindowHwnd, NULL, NULL, NULL);
    if (!g_AuthTimeLeftLabelHwnd) {
        return NULL;
    }
    g_AuthTimeLeftLabelFont = _RDTP_SetLabelFont(g_AuthTimeLeftLabelHwnd, g_AuthTimeLeftLabelFontSize);
    ShowWindow(g_AuthTimeLeftLabelHwnd, SW_SHOW);

    // message label showed when auth code does not valid.
    g_AuthCodeNotValidLabelHwnd = CreateWindowW(L"static", L"Authentication code does not valid.", WS_CHILD, _CalcPos(g_AuthCodeNotValidLabelX), _CalcPos(g_AuthCodeNotValidLabelY), 
        _CalcPos(g_AuthCodeNotValidLabelWidth), _CalcPos(g_AuthCodeNotValidLabelHeight), g_AuthWindowHwnd, NULL, NULL, NULL);
    if (!g_AuthCodeNotValidLabelHwnd) {
        return NULL;
    }
    g_AuthCodeNotValidLabelFont = _RDTP_SetLabelFont(g_AuthCodeNotValidLabelHwnd, g_AuthCodeNotValidLabelFontSize);
    ShowWindow(g_AuthCodeNotValidLabelHwnd, SW_HIDE);
    g_AuthCodeNotValidDisplayed = FALSE;

    SetFocus(g_InputCodeTextboxHwnd);

    return g_AuthWindowHwnd;
}

_declspec(dllexport) BOOL RDOTP_ShowAuthWindow() {
    g_AuthValid = FALSE;

    if (!g_AuthWindowHwnd) {
        return FALSE;
    }

    g_Time = MAX_AUTH_TIME;

    _RDOTP_HandleAuthTimer();

    SetTimer(g_AuthWindowHwnd, AUTH_TIMER, 1000, NULL);

    ShowWindow(g_AuthWindowHwnd, SW_SHOW);

    MSG msg;
    while (IsWindow(g_AuthWindowHwnd)) {
        if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }

        Sleep(1);
    }

    return g_AuthValid;
}


LRESULT CALLBACK _RDOTP_AuthWindow_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_COMMAND: {
            WORD cmd = LOWORD(wParam);
            if (cmd == BTN_CANCEL) {
                SendMessageW(g_AuthWindowHwnd, WM_CLOSE, 0, 0);
            }
            else if (cmd == BTN_SUBMIT) {
                WCHAR otpCode[MAX_INPUTCODE_LEN] = { 0, };
                SendMessageW(g_InputCodeTextboxHwnd, WM_GETTEXT, MAX_INPUTCODE_LEN, (LPARAM)&otpCode);

                if (_RDOTP_ProcessAuth(otpCode)) {
                    // auth success
                    g_AuthValid = TRUE;
                    SendMessageW(g_AuthWindowHwnd, WM_CLOSE, 0, 0);
                }
                else {
                    // auth failed
                    g_FailedAuthCnt++;
                    if (g_FailedAuthCnt >= 5) {
                        Sleep(3000);
                        SendMessageW(g_AuthWindowHwnd, WM_CLOSE, 0, 0);
                    }
                    else {
                        Sleep(500);
                        SendMessageW(g_InputCodeTextboxHwnd, WM_SETTEXT, 0, 0);
                        ShowWindow(g_AuthCodeNotValidLabelHwnd, SW_SHOW);
                        g_AuthCodeNotValidDisplayed = TRUE;
                    }
                }
            }
        }; break;
        case WM_CTLCOLORBTN: {
            return (LRESULT)g_TransParentBtnBk;
        }; break;
        case WM_CTLCOLORSTATIC: {
            if ((HWND)lParam == g_AuthCodeNotValidLabelHwnd) {
                SetTextColor((HDC)wParam, RGB(255, 0, 0));
            }
            return (LRESULT)g_TransParentBtnBk;
        }; break;
        case WM_TIMER: {
            // handle auth left time
            if (wParam == AUTH_TIMER) {
                _RDOTP_HandleAuthTimer();
            }

        }; break;
        case WM_CLOSE:
            _RDOTP_CloseAndCleanupControls();
            DestroyWindow(hWnd);
            break;

        default:
            return DefWindowProcW(hWnd, msg, wParam, lParam);
    }
    return 0;
}

HFONT _RDTP_SetLabelFont(HWND hLabel, DWORD dwFontSize) {
    dwFontSize = _CalcPos(dwFontSize);

    HFONT hFont = CreateFontW(
        dwFontSize,
        0,
        0,
        0,
        FW_NORMAL,
        FALSE,
        FALSE,
        FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        0,
        L"Arial"
    );

    SendMessageW(hLabel, WM_SETFONT, (WPARAM)hFont, TRUE);

    return hFont;
}

void _RDOTP_CloseAndCleanupControls() {
    CloseWindow(g_AuthWindowHwnd);

    CloseWindow(g_MainTitleLabelHwnd);
    DestroyWindow(g_MainTitleLabelHwnd);
    g_MainTitleLabelHwnd = NULL;
    DeleteObject(g_MainTitleLabelFont);
    g_MainTitleLabelFont = NULL;

    CloseWindow(g_SubTitleLabelHwnd);
    DestroyWindow(g_SubTitleLabelHwnd);
    g_SubTitleLabelHwnd = NULL;
    DeleteObject(g_SubTitleLabelFont);
    g_SubTitleLabelFont = NULL;

    SetWindowLongPtrW(g_InputCodeTextboxHwnd, GWLP_WNDPROC, g_InputCodeTextboxOrigProc);
    CloseWindow(g_InputCodeTextboxHwnd);
    DestroyWindow(g_InputCodeTextboxHwnd);
    g_InputCodeTextboxHwnd = NULL;
    DeleteObject(g_InputCodeTextboxFont);
    g_InputCodeTextboxFont = NULL;

    CloseWindow(g_AuthTimeLeftLabelHwnd);
    DestroyWindow(g_AuthTimeLeftLabelHwnd);
    g_AuthTimeLeftLabelHwnd = NULL;
    DeleteObject(g_AuthTimeLeftLabelFont);
    g_AuthTimeLeftLabelFont = NULL;

    CloseWindow(g_MachineTimeLabelHwnd);
    DestroyWindow(g_MachineTimeLabelHwnd);
    g_MachineTimeLabelHwnd = NULL;
    DeleteObject(g_MachineTimeLabelFont);
    g_MachineTimeLabelFont = NULL;

    CloseWindow(g_AuthCodeNotValidLabelHwnd);
    DestroyWindow(g_AuthCodeNotValidLabelHwnd);
    g_AuthCodeNotValidLabelHwnd = NULL;
    DeleteObject(g_AuthCodeNotValidLabelFont);
    g_AuthCodeNotValidLabelFont = NULL;

    DeleteObject(g_SubmitBtnFont);
    g_SubmitBtnFont = NULL;
    CloseWindow(g_SubmitBtnHwnd);
    DestroyWindow(g_SubmitBtnHwnd);
    g_SubmitBtnHwnd = NULL;

    DeleteObject(g_CancelBtnFont);
    g_CancelBtnFont = NULL;
    CloseWindow(g_CancelBtnHwnd);
    DestroyWindow(g_CancelBtnHwnd);
    g_CancelBtnHwnd = NULL;

    KillTimer(g_AuthWindowHwnd, AUTH_TIMER);

    DestroyWindow(g_AuthWindowHwnd);
    g_AuthWindowHwnd = NULL;

    DeleteObject(g_TransParentBtnBk);
    g_TransParentBtnBk = NULL;

    DestroyIcon(g_LockIcon);
    g_LockIcon = NULL;

    UnregisterClassW(L"RDOTP_AuthWindow", NULL);
    g_MainWindowClass = (ATOM)NULL;
    g_ParentWindow = NULL;
}

BOOL _RDOTP_ProcessAuth(LPCWSTR pOtpCode) {
    if (!pOtpCode || !wcslen(pOtpCode)) {
        return FALSE;
    }

    return RDOTP_ValidateCode(pOtpCode);
}

void _RDOTP_HandleAuthTimer() {
    WCHAR machineTimeText[64] = { 0, };
    WCHAR leftAuthTimeText[64] = { 0, };
    SYSTEMTIME st = { 0, };

    if (g_Time <= 0) {
        SendMessageW(g_AuthWindowHwnd, WM_CLOSE, 0, 0);
        return;
    }

    GetLocalTime(&st);
    wsprintfW(machineTimeText, L"Machine Time : %04d-%02d-%02d %02d:%02d:%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
    SetWindowTextW(g_MachineTimeLabelHwnd, machineTimeText);

    wsprintfW(leftAuthTimeText, L"Dialog will be closed in %d seconds.", g_Time);
    SetWindowTextW(g_AuthTimeLeftLabelHwnd, leftAuthTimeText);

    g_Time--;
}

INT _GetSystemDPI() {
    // 'rdOTP" need to support windows 8 (server2012), so cannot use 'GetDpiForSystem()'
    HDC screen = GetDC(NULL);
    int dpi = GetDeviceCaps(screen, LOGPIXELSX);
    ReleaseDC(NULL, screen);

    return dpi;
}

DWORD _CalcPos(DWORD originalPos) {
    FLOAT position = originalPos * g_scale;

    position = roundf(position);
    
    return (DWORD)position;
}

LRESULT CALLBACK _RDOTP_InputCodeCtrl_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    // Handle 'Enter' Key
    switch (message) {
        case WM_KEYDOWN: {
            if (wParam == VK_RETURN) {
                SendMessageW(g_AuthWindowHwnd, WM_COMMAND, BTN_SUBMIT, 0);
            }
            else if (g_AuthCodeNotValidDisplayed) {
                g_AuthCodeNotValidDisplayed = FALSE;
                ShowWindow(g_AuthCodeNotValidLabelHwnd, SW_HIDE);
            }
        }; break;
    }

    return CallWindowProcW((WNDPROC)g_InputCodeTextboxOrigProc, hWnd, message, wParam, lParam);
}