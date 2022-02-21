# Windows-Programming-study
study repository 

Window Datatype
handle 같은 하나의 자료형으로 봐도됨.
HANDLE - 4바이트의 양의 정수값을 말함. = 운영체제가 응용 프로그램을 실행 또는 구분하는 방법임.


인스턴스는 응용프로그램의 ID임 같은 프로그램이기 떄문에 ID값이 같음 하나의 응용프로그램
HANDLE 각 참조되는 값이 달라서 다른 값을 가질 수 있음 운영체제에서 할당한 자원의 아이디
 

[
PVOID = void * 
HANDLE typedef PVOID HANDLE;
HDC typedef HANDLE HDC;
HINSTANCE typedef HANDLE HINSTANCE;
HWND typedef HANDLE HWND;
]


헝가리안 표기법
 1. 첫문자는 대문자 ex) Count; 
 2. 데이터형을 의미하는 접두사를 붙임 ex) fCount; nNumber;

ex)

  1. integer i,n
  2. long l
  3. float f
  4. double d
  5. DWORD dw
  6. string sz,s,str
  7. Pointer p
  8. HANDLE h
  9. global g_
  10. MSG msg
자료형 
  
    CHAR typedef char CHAR; 
    DWORD typedef unisigned long DWORD;
    COLORREF typedef DWORD COLORREF;
    LPSTR typedef CHAR * LPSTR;
    LPSTR typedef WCHAR * LPWSTR;  unicode str을 말함.
    LPTSTR #ifdef UNICODE
		      Typedef LPWSTR LPTSTR;
	       #else
		       Typedef LPSTR LPTSTR;
	      #endif
    TCHAR #ifdef UNICODE
		      Typedef WCHAR TCHAR;
	      #else
		      Typedef char TCHAR;
	      #endif


    UINT typedef unsigned int UINT;
    VOID #define VOID void
    WORD typedef unsigned short WORD;
    WPARAM typedef UINT_PTR WPARAM;
    UINT_PTR #if defined(_WIN64)

            typedef unsigned __int64 UINT_PTR;
            
         #else 
            typedef unsigned int UINT_PTR;
         #endif
         
    LPARAM typedef LONG_PTR LPARAM; 


    LONG_PTR #if defined(_WIN64)
          typedef __int64 LONG_PTR;
         #else 
          typedef long LONG_PTR;
         #endif



__stdcall and __cdecl 

__stdcall 호출당한 함수 내부에서 Stack pointer 연산을 해줌. 연산속도가 __cdecl에 비해 빠르고 용량도 적어짐
__cdecl 함수 호출용으로 스택에 쌓은 파라미터를 호출한 함수에서 제거해줌
[
WINAPI #define WINAPI __stdcall

]

윈도우 구조체

      WNDCLASSEX{
			UINT cbSize; 구조체 크기 WNDCLASSEX 구조체 크기
			UINT style 출력형태 
			WNDPROC lpfnWndProc 프로시저 함수 메모리 처리 에 사용될 함수이름 기재
			int cbClsExtra 클래스 여분 메모리
			int cbWndExtra 윈도우 여분 메모리
			HANDLE hInstace 윈도우 인스턴스
			HICON hIcon 아이콘
			HCURSOR hCursor 커서
			HBRUSH hbrBackground 배경색
			LPCTSTR lpszMenuName; 메뉴 이름
			LPCTSTR lpszClassName 클래스 이름 
			HICON hIconSm; 작은 아이콘
      } WNDCLASSEX
		
    MSG 구조체
		typedef struct tagMSG{
		 HWND hwnd;		메세지를 받을 윈도우 핸들
		 UINT message;	메시지 종류
		 WPARAM wParam;	메세지에 따른 부가정보
		 LPARAM lParam;	메세지에 따른 부가정보
		 DWORD time;	메세지 발생 시각
		 POINT pt;		발생했을 때 마우스 위치 
		}MSG, *PMSG , *LPMSG;
		

WinMain() 윈도우 구조체 등록 및 생성 역활 -> 메시지 루프 , 체크, 전달
  registerclass() 등록함수
  while(GetMessage(&msg,NULL,0,0)){
  TranslateMessage(&msg);  # 키보드 등의 외부장치 발생시켜주는 함수
  DispatchMessage(&msg);   # 메시지 전달 함수 WNDCLASSEX에 지정된 WINPROC 호출  
 }
WinProc() 메시지 처리
  ex)
  {
    switch(message){
    case WM_xxx:
        break;
    case CB_xxx:
        break;
        ...
    default : 
        DefWndProc();
  }
메시지들의 형태는 
  WM_xxx , CB_xxx , LM_xxx , PBM_xxx = unsigned_integer
  

DLL(Dynamic Link Library)란? 
실행 파일에서 특정 라이브러리 기능을 사용할 때만 참조하는 것으로 메모리적 이점을 볼 수 있다.
DLL을 사용할 수록 배포나 설치면에서 편리성을 가지며 협업 시에 분담 작업에 용이하다.

DllMain 
Dll에서 가지는 하나의 진입점을 말한다.
DllMain에서의 각 인자는 다음과 같은 값을 의미한다.

1. hintdll : dll 인스턴스 자체에 포인트를 처리하는 인자
2. fdwReason : DLL의 호출 이유 값을 가지고 있는 인자
3. plReserved 


BOOL WINAPI DllMain(HINSTANCE hintdll, DWORD fdwReason , LPVOID lpvReserved)
{
  switch(dwReason){
    case DLL_PROCESS_ATTACH: DLL이 프로세스 주소 영역에 매핑되었을 경우 - LoadLibrary();
      break;
    case DLL_THREAD_ATTACH: 쓰레드 생성시
      break;
    case DLL_THREAD_DETACH: 쓰레드 종료시
      break;
    case DLL_PROCESS_DETACH: 프로세스 주소 영역에서 매핑 해제시에
      break;
  
  }
}
