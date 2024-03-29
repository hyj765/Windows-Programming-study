﻿// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include "pch.h"
#include<stdio.h>
#include<Windows.h>

#define DEF_PROCESS_NAME "notepad.exe"

HINSTANCE g_hInstance = NULL;
HHOOK g_hHook = NULL;
HWND g_hWnd = NULL;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	char szPath[MAX_PATH] = { 0 };
	char* p = NULL;

	if (nCode >= 0) {
		if (!(lParam & 0x80000000)) {
			GetModuleFileNameA(NULL, szPath, MAX_PATH);
			p = strrchr(szPath, '\\');
			if (!_stricmp(p + 1, DEF_PROCESS_NAME)) {
				return 1;
			}
		}

	}

	return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD dwReason, LPVOID lpvReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
		g_hInstance = hinstDll;
		break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


#ifdef __cplusplus
extern "C" {
#endif
	__declspec(dllexport) void HookStart() {
		g_hHook = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, g_hInstance, 0);
		if (g_hHook == NULL) {
			printf("hook error\n");
		}
	}
	__declspec(dllexport) void HookStop() {
		if (g_hHook) {
			UnhookWindowsHookEx(g_hHook);
			g_hHook = NULL;
		}
	}

#ifdef __cplusplus
}
#endif

