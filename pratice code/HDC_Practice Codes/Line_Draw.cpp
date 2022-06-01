// Win_First_step_.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Win_First_step_.h"

int g_is_clicked = 0;
int g_x, g_y;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {

	if (uMsg == WM_DESTROY) PostQuitMessage(0);
	else if(uMsg == WM_LBUTTONDOWN){
		g_is_clicked = 1;
		
		//MoveToEx(h_dc, 10, 10, NULL); // 시작점을 그리는 함수  ReleaseDC가 되면 MoveTO가 리셋 됨.
		//LineTo(h_dc, 100, 100); // 끝점을 그리는 함수

		g_x = lParam & 0x0000FFFF; // == LOWORD(lParam)
		g_y = (lParam >> 16) & 0x0000FFFF;// == HIWORD(lParam)
		
		
	}
	else if (uMsg == WM_LBUTTONUP) {
		g_is_clicked = 0;
	}
	else if(uMsg == WM_MOUSEMOVE){
		if (g_is_clicked == 1) {
			HDC h_dc = GetDC(hWnd);

			//MoveToEx(h_dc, 10, 10, NULL); // 시작점을 그리는 함수  ReleaseDC가 되면 MoveTO가 리셋 됨.
			//LineTo(h_dc, 100, 100); // 끝점을 그리는 함수
			MoveToEx(h_dc, g_x, g_y, NULL);
			int x = lParam & 0x0000FFFF; // == LOWORD(lParam)
			int y = (lParam >> 16) & 0x0000FFFF;// == HIWORD(lParam)
			LineTo(h_dc, x, y);
			g_x = x;
			g_y = y;
			ReleaseDC(hWnd, h_dc);
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

	HWND hWnd = CreateWindow(L"my first_win_prog", L"Step_two",
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