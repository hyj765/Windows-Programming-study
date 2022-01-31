#include <iostream>
#include <windows.h>  
#include <tlhelp32.h>  
#include<algorithm>

bool c_find(const char* target, std::string dest);

int main(int argc, char* argv[])
{
    BOOL f_Flag = FALSE;
    BOOL bGet = FALSE;
    char buf[260] = "";
    HANDLE hSnapshot;
    PROCESSENTRY32 ppe;     //구성된 자료구조를 저장하기 위한 엔트리.  
    std::string target_p;
    std::cin >> target_p;
    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//system 프로세서(pid=0)의 상태를 읽어 온다   
    ppe.dwSize = sizeof(PROCESSENTRY32);                        //엔트리 구조체 사이즈를 정해준다.  
    bGet = Process32First(hSnapshot, &ppe);                     //엔트리 중 자료를 가져온다.  

    while (bGet)
    {
        WideCharToMultiByte(CP_ACP, 0, ppe.szExeFile, 260, buf, 260, NULL, NULL);
        if (c_find(buf,target_p)) {
            fprintf(stdout, "processName:%-15s\t", buf);          //프로세스 이름을 출력  
            fprintf(stdout, "processID:%5d\n", ppe.th32ProcessID);//프로세스 아이디를 출력  
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