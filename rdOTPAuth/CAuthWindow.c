#include "pch.h"
#include "CAuthWindow.h"
#include "resource.h"

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

HWND g_SubmitBtnHwnd = NULL;
DWORD g_SubmitBtnX = 260;
DWORD g_SubmitBtnY = 160;
DWORD g_SubmitBtnWidth = 60;
DWORD g_SubmitBtnHeight = 30;

HWND g_CancelBtnHwnd = NULL;
DWORD g_CancelBtnX = 330;
DWORD g_CancelBtnY = 160;
DWORD g_CancelBtnWidth = 60;
DWORD g_CancelBtnHeight = 30;

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
DWORD g_MachineTimeLabelWidth = 200;
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


// end controls

DWORD g_MainWindowX = 0;
DWORD g_MainWindowY = 0;
DWORD g_MainWindowWidth = 400;
DWORD g_MainWindowHeight = 200;
DWORD g_scale = 1;
DWORD g_Time = 0;

#define BTN_SUBMIT 100
#define BTN_CANCEL 101

#define MAX_INPUTCODE_LEN 16
#define MAX_AUTH_TIME 45

#define AUTH_TIMER 1


BOOL RDOTP_InitializeAuthWindow(HWND hwnd) {
	if (!hwnd) {
		hwnd = GetForegroundWindow();
	}

    g_ParentWindow = hwnd;

    WNDCLASSEX wc = { 0, };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = _RDOTP_AuthWindow_WndProc;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"RDOTP_AuthWindow";

    g_MainWindowClass = RegisterClassExW(&wc);
    if (g_MainWindowClass) {
        return TRUE;
    }

    g_TransParentBtnBk = GetSysColorBrush(COLOR_WINDOW);

	return FALSE;
}

HWND RDOTP_CreateAuthWindow() {
    g_AuthWindowHwnd = CreateWindowW(L"RDOTP_AuthWindow", L"MainWindow", WS_POPUPWINDOW, g_MainWindowX, g_MainWindowY,
        g_MainWindowWidth, g_MainWindowHeight, g_ParentWindow, NULL, NULL, NULL);
    if (!g_AuthWindowHwnd) {
        return NULL;
    }

    g_MainTitleLabelHwnd = CreateWindowW(L"static", L"Autherication Required", WS_CHILD, g_MainTitleLabelX, g_MainTitleLabelY, g_MainTitleLabelWidth,
        g_MainTitleLabelHeight, g_AuthWindowHwnd, NULL, NULL, NULL);
    if (!g_MainTitleLabelHwnd) {
        return NULL;
    }
    g_MainTitleLabelFont = _RDTP_SetLabelFont(g_MainTitleLabelHwnd, g_MainTItleLabelFontSize);
    ShowWindow(g_MainTitleLabelHwnd, SW_SHOW);

    g_SubTitleLabelHwnd = CreateWindowW(L"static", L"Enter OTP code from registered phone", WS_CHILD, g_SubTitleLabelX, g_SubTitleLabelY, g_SubTitleLabelWidth,
        g_SubTitleLabelHeight, g_AuthWindowHwnd, NULL, NULL, NULL);
    if (!g_SubTitleLabelHwnd) {
        return NULL;
    }
    g_SubTitleLabelFont = _RDTP_SetLabelFont(g_SubTitleLabelHwnd, g_SubTitleLabelFontSize);
    ShowWindow(g_SubTitleLabelHwnd, SW_SHOW);

    g_InputCodeTextboxHwnd = CreateWindowW(L"edit", L"", WS_CHILD | WS_BORDER | ES_CENTER, g_InputCodeTextboxX, g_InputCodeTextboxY, g_InputCodeTextboxWidth,
        g_InputCodeTextboxHeight, g_AuthWindowHwnd, NULL, NULL, NULL);
    if (!g_InputCodeTextboxHwnd) {
        return NULL;
    }
    g_InputCodeTextboxFont = _RDTP_SetLabelFont(g_InputCodeTextboxHwnd, g_InputCodeTextboxFontSize);
    ShowWindow(g_InputCodeTextboxHwnd, SW_SHOW);
    SendMessageW(g_InputCodeTextboxHwnd, EM_SETLIMITTEXT, MAX_INPUTCODE_LEN - 1, (LPARAM)NULL);

    g_SubmitBtnHwnd = CreateWindowW(L"button", L"Submit", WS_CHILD, g_SubmitBtnX, g_SubmitBtnY, g_SubmitBtnWidth,
        g_SubmitBtnHeight, g_AuthWindowHwnd, (HMENU)BTN_SUBMIT, NULL, NULL);
    if (!g_SubmitBtnHwnd) {
        return NULL;
    }
    ShowWindow(g_SubmitBtnHwnd, SW_SHOW);

    g_CancelBtnHwnd = CreateWindowW(L"button", L"Cancel", WS_CHILD, g_CancelBtnX, g_CancelBtnY, g_CancelBtnWidth,
        g_CancelBtnHeight, g_AuthWindowHwnd, (HMENU)BTN_CANCEL, NULL, NULL);
    if (!g_CancelBtnHwnd) {
        return NULL;
    }
    ShowWindow(g_CancelBtnHwnd, SW_SHOW);
        
    g_LockIcon = (HICON)LoadImageW(GetModuleHandleW(NULL), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, g_LockIconWidth, g_LockIconHeight, LR_DEFAULTCOLOR);
    g_LockIconHwnd = CreateWindowW(L"static", L"", WS_CHILD | SS_ICON, g_LockIconX, g_LockIconY, g_LockIconWidth,
        g_LockIconHeight, g_AuthWindowHwnd, NULL, NULL, NULL);
    if (!g_LockIconHwnd) {
        return NULL;
    }

    g_MachineTimeLabelHwnd = CreateWindowW(L"static", L"Machine Time : ", WS_CHILD, g_MachineTimeLabelX, g_MachineTimeLabelY, g_MachineTimeLabelWidth,
        g_MachineTimeLabelHeight, g_AuthWindowHwnd, NULL, NULL, NULL);
    if (!g_MachineTimeLabelHwnd) {
        return NULL;
    }
    g_MachineTimeLabelFont = _RDTP_SetLabelFont(g_MachineTimeLabelHwnd, g_MachineTimeLabelFontSize);
    ShowWindow(g_MachineTimeLabelHwnd, SW_SHOW);

    g_AuthTimeLeftLabelHwnd = CreateWindowW(L"static", L"", WS_CHILD, g_AuthTimeLeftLabelX, g_AuthTimeLeftLabelY, g_AuthTimeLeftLabelWidth,
        g_AuthTimeLeftLabelHeight, g_AuthWindowHwnd, NULL, NULL, NULL);
    if (!g_AuthTimeLeftLabelHwnd) {
        return NULL;
    }
    g_AuthTimeLeftLabelFont = _RDTP_SetLabelFont(g_AuthTimeLeftLabelHwnd, g_AuthTimeLeftLabelFontSize);
    ShowWindow(g_AuthTimeLeftLabelHwnd, SW_SHOW);

    g_AuthCodeNotValidLabelHwnd = CreateWindowW(L"static", L"Authentication code does not valid.", WS_CHILD, g_AuthCodeNotValidLabelX, g_AuthCodeNotValidLabelY, g_AuthCodeNotValidLabelWidth,
        g_AuthCodeNotValidLabelHeight, g_AuthWindowHwnd, NULL, NULL, NULL);
    if (!g_AuthCodeNotValidLabelHwnd) {
        return NULL;
    }
    g_AuthCodeNotValidLabelFont = _RDTP_SetLabelFont(g_AuthCodeNotValidLabelHwnd, g_AuthCodeNotValidLabelFontSize);
    ShowWindow(g_AuthCodeNotValidLabelHwnd, SW_HIDE);

    SendMessageW(g_LockIconHwnd, STM_SETIMAGE, IMAGE_ICON, (LPARAM)g_LockIcon);

    ShowWindow(g_LockIconHwnd, SW_SHOW);

    return g_AuthWindowHwnd;
}

BOOL RDOTP_ShowAuthWindow() {
    if (!g_AuthWindowHwnd) {
        return FALSE;
    }

    g_Time = MAX_AUTH_TIME;

    SetTimer(g_AuthWindowHwnd, AUTH_TIMER, 1000, NULL);

    return ShowWindow(g_AuthWindowHwnd, SW_SHOW);
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
                    SendMessageW(g_AuthWindowHwnd, WM_CLOSE, 0, 0);
                }
                else {
                    // auth failed
                    Sleep(1500);
                    SendMessageW(g_InputCodeTextboxHwnd, WM_SETTEXT, 0, 0);
                    ShowWindow(g_AuthCodeNotValidLabelHwnd, SW_SHOW);
                }
            }
        }; break;
        case WM_CTLCOLORBTN: {
            return (LRESULT)g_TransParentBtnBk;
        }; break;
        case WM_CTLCOLORSTATIC: {
            if (lParam == g_AuthCodeNotValidLabelHwnd) {
                SetTextColor((HDC)wParam, RGB(255, 0, 0));
            }
            return (LRESULT)g_TransParentBtnBk;
        }; break;
        case WM_TIMER: {
            if (wParam == AUTH_TIMER) {
                _RDOTP_HandleAuthTimer();
            }

        }; break;
        case WM_DESTROY:
            _RDOTP_CloseAndCleanupControls();
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProcW(hWnd, msg, wParam, lParam);
    }
    return 0;
}

HFONT _RDTP_SetLabelFont(HWND hLabel, DWORD dwFontSize) {
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

    CloseWindow(g_SubmitBtnHwnd);
    DestroyWindow(g_SubmitBtnHwnd);
    g_SubmitBtnHwnd = NULL;

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

    if (!wcscmp(pOtpCode, L"1234")) {
        return TRUE;
    }

    return FALSE;
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