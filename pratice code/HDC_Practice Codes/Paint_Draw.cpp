// Win_First_step_.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Win_First_step_.h"

#define MAX_CNT 1000

int g_is_clicked = 0;
int g_x[MAX_CNT], g_y[MAX_CNT];
int g_cnt = 0;
int g_move[MAX_CNT];
int g_mcnt = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {

	if (uMsg == WM_DESTROY) PostQuitMessage(0);
	else if (uMsg == WM_PAINT) {// WM_PAINT GETDC 사용 시 무한 루프를 돌면서 cpu 사용율이 증가함.
		PAINTSTRUCT ps;
		HDC h_dc = BeginPaint(hWnd,&ps);

		if (g_cnt > 0) {
			MoveToEx(h_dc, g_x[0], g_y[0], NULL);
			int offcnt = g_mcnt;
			int cur = 0;
			bool ef = true;
			for (int i = 1; i < g_cnt - 1; i++) {
				if (g_move[cur] == i && ef == true) {
					MoveToEx(h_dc, g_x[i], g_y[i], NULL);
					cur++;
					if (cur % g_mcnt == 0) ef == false;
				}else LineTo(h_dc, g_x[i], g_y[i]);
			}
		}
		EndPaint(hWnd, &ps);

		return 0; // DefWindowProc하면 BeginPaint_ endPaint 가 재호출되기 때문에 Return으로 끝내줘야함.
	}
	else if (uMsg == WM_LBUTTONDOWN ) {
		g_is_clicked = 1;
		if (g_cnt < MAX_CNT) {
			g_x[g_cnt] = LOWORD(lParam);
			g_y[g_cnt] = HIWORD(lParam);
			g_cnt++;
		}
	}
	else if (uMsg==WM_MOUSEMOVE) {
		if (g_is_clicked == 1 && g_cnt < MAX_CNT) {
			HDC h_dc = GetDC(hWnd);
			MoveToEx(h_dc, g_x[g_cnt - 1], g_y[g_cnt - 1], NULL);
			g_x[g_cnt] = LOWORD(lParam);
			g_y[g_cnt] = HIWORD(lParam);
			LineTo(h_dc, g_x[g_cnt], g_y[g_cnt]);
			g_cnt++;

			ReleaseDC(hWnd,h_dc);
		}
	}
	else if (uMsg == WM_LBUTTONUP) {
		g_is_clicked = 0;
		g_move[g_mcnt] = g_cnt;
		g_mcnt++;
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