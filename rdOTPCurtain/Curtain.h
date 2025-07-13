#pragma once


// 커튼 윈도우 초기화
BOOL RDOTPInitializeCurtain();

// 커튼 윈도우 정리
void RDOTPReleaseCurtain();

// 커튼 윈도우를 표시
HWND RDOTPShowCurtainWindow(int x, int y, int sizeX, int sizeY);

// 커튼 윈도우를 닫기
void RDOTPCloseCurtainWindow(HWND hwnd);