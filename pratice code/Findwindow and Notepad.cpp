// Win_First_step_.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Win_First_step_.h"

#define MAX_CNT 1000

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {

	if (uMsg == WM_DESTROY) PostQuitMessage(0);
	else if (uMsg == WM_LBUTTONDOWN) {
		HWND h_find_wnd = FindWindow(L"Notepad", NULL);
		if (NULL != h_find_wnd) {
			HWND h_edit_wnd = FindWindowEx(h_find_wnd, NULL, L"Edit", NULL);
			if (NULL != h_edit_wnd) {
				//SendMessage(h_edit_wnd,WM_SETTEXT,0,(LPARAM)L"Hello world");
				wchar_t str[256];
				SendMessage(h_edit_wnd, WM_GETTEXT, 256, (LPARAM)str);
				MessageBox(hWnd, str, L"Recieve Text",MB_OK );
			}
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hIntance,HINSTANCE hPreintance,LPSTR ipCmdline,int nCmdShow) {

	WNDCLASS wndclass;
	wndclass.cbClsExtra = NULL;
	wndclass.cbWndExtra = NULL;
	wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hIntance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = L"my first_win_prog";
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndclass);

	HWND hWnd = CreateWindow(L"my first_win_prog", L"Step_one",
		WS_OVERLAPPEDWINDOW, 100, 90, 400, 350,NULL,NULL,hIntance,NULL);
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}