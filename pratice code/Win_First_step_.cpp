#include "framework.h"
#include "Win_First_step_.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {

	if (uMsg == WM_DESTROY) PostQuitMessage(0);

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