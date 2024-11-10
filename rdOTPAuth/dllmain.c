// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "CAuthWindow.h"
#include <CommCtrl.h>
#include <shellscalingapi.h>

#pragma comment(lib, "Shcore.lib")

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

int main() {

    SetProcessDpiAwareness(PROCESS_SYSTEM_DPI_AWARE);

    InitCommonControls();

    if (!RDOTP_InitializeAuthWindow(0)) {
        return -1;
    }

    HWND hwnd = RDOTP_CreateAuthWindow();
    if (!hwnd) {
        return -1;
    }

    RDOTP_ShowAuthWindow();

    MSG msg;
    while (GetMessage(&msg, 0, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}