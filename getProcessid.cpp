#include <iostream>
#include <windows.h>  
#include <tlhelp32.h>  
#include<algorithm>

/*
   typedef struct tagPROCESSENTRY32 { 
   DWORD dwSize;  구조체 바이트 크기 항시 초기화해주어야함.
   DWORD cntUsage; 
   DWORD th32ProcessID; PID      ****
   ULONG_PTR th32DefaultHeapID; 사용안하는 값 
   DWORD th32ModuleID; 사용 안하는 값
   DWORD cntThreads; 프로세스에 의해 시작된 스레드 수 ****
   DWORD th32ParentProcessID; 부모프로세스 PID ****
   LONG pcPriClassBase; 
   DWORD dwFlags; 사용 안하는 값
   CHAR szExeFile[MAX_PATH]; 실행 프로세스 이름
   }PROCESSENTRY32

   #include <tlhelp32.h>
        CreateToolhelp32napshot(dwFlag, th32ProcessID); 프로세스 스냅샷 떠주는 함수.

        dwFlag {
            TH32CS_SNAPPROCESS 모든 프로세스 가져오기
            TH32CS_SNAPTHREAD 모든 쓰레드 가져오기
        }
        Process32First(handle snapshot , &process32 struct); 스냅샷에 대한 첫번째 정보를 검색하는 함수.
        스냅샷을 통하여 얻은 프로세스 데이터를 process information을 담는  PROCESSENTRY32 구조체에 데이터를 넣는 함수. 
        Process32Next(handle snapshot , &process32 struct) 다음 스냅샷 값을 검색하는 함수.
        Library Kernel32.lib
        DLL Kernel32.dll
        
        프로그램 순서
        1. 찾고 싶은 프로세스 데이터 입력 -> 스냅샷 -> PROCESSENTRY32 구조체에 process information 담기 -> 해당 프로세스 값이 있는 지 이름으로 확인 -> 사용한 handle 닫아주기
*/



bool c_find(const char* target, std::string dest);

int main(int argc, char* argv[])
{

    BOOL f_Flag = FALSE;
    BOOL bGet = FALSE;
    char buf[260] = "";
    HANDLE hSnapshot;
    PROCESSENTRY32 ppe;     //Windows process data struct
    std::string target_p;
    std::cin >> target_p;
    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    ppe.dwSize = sizeof(PROCESSENTRY32);                        
    bGet = Process32First(hSnapshot, &ppe);                      

    while (bGet)
    {
        WideCharToMultiByte(CP_ACP, 0, ppe.szExeFile, 260, buf, 260, NULL, NULL);
        if (c_find(buf,target_p)) {
            fprintf(stdout, "processName:%-15s\t", buf);          
            fprintf(stdout, "processID:%5d\n", ppe.th32ProcessID); 
            f_Flag = TRUE;
        }
        bGet = Process32Next(hSnapshot, &ppe);
    }
    if (f_Flag == FALSE) {
        std::cout << "대상 프로세스를 발견하지 못했습니다." << std::endl;
    }
    CloseHandle(hSnapshot);
    return 0;
}

bool c_find(const char* target, std::string dest) {
    std::string t = target;
    int g = t.find(dest);
    if (g == std::string::npos) {
        return false;
    }
    return true;
}