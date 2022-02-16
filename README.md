# Windows-Programming-study
study repository 

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
