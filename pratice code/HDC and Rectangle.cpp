// Win_First_step_.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Win_First_step_.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {

	if (uMsg == WM_DESTROY) PostQuitMessage(0);
	else if (uMsg == WM_LBUTTONDOWN) {
		HDC h_dc = GetDC(hWnd);

		//Rectangle(h_dc,10,10,200,200); // 고정 위치 사각형 생성
		//LPARAM에 마우스 클릭 등의 정보 x,y좌표 값이 저장되어있음. 
		//Lparam에 상위 비트 16비트에 Y좌표 하위 비트 16비트에 X좌표가 들어있음.
		int x = lParam & 0x0000FFFF; // == LOWORD(lParam)
		int y = (lParam >> 16) & 0x0000FFFF;// == HIWORD(lParam)
		Rectangle(h_dc, x -15, y - 15, x + 15, y + 15);

		ReleaseDC(hWnd,h_dc);
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