#include <iostream>
#include <windows.h>  
#include <tlhelp32.h>  
#include<algorithm>

/*
   typedef struct tagPROCESSENTRY32 { 
   DWORD dwSize;  ����ü ����Ʈ ũ�� �׽� �ʱ�ȭ���־����.
   DWORD cntUsage; 
   DWORD th32ProcessID; PID      ****
   ULONG_PTR th32DefaultHeapID; �����ϴ� �� 
   DWORD th32ModuleID; ��� ���ϴ� ��
   DWORD cntThreads; ���μ����� ���� ���۵� ������ �� ****
   DWORD th32ParentProcessID; �θ����μ��� PID ****
   LONG pcPriClassBase; 
   DWORD dwFlags; ��� ���ϴ� ��
   CHAR szExeFile[MAX_PATH]; ���� ���μ��� �̸�
   }PROCESSENTRY32

   #include <tlhelp32.h>
        CreateToolhelp32napshot(dwFlag, th32ProcessID); ���μ��� ������ ���ִ� �Լ�.

        dwFlag {
            TH32CS_SNAPPROCESS ��� ���μ��� ��������
            TH32CS_SNAPTHREAD ��� ������ ��������
        }
        Process32First(handle snapshot , &process32 struct); �������� ���� ù��° ������ �˻��ϴ� �Լ�.
        �������� ���Ͽ� ���� ���μ��� �����͸� process information�� ���  PROCESSENTRY32 ����ü�� �����͸� �ִ� �Լ�. 
        Process32Next(handle snapshot , &process32 struct) ���� ������ ���� �˻��ϴ� �Լ�.
        Library Kernel32.lib
        DLL Kernel32.dll
        
        ���α׷� ����
        1. ã�� ���� ���μ��� ������ �Է� -> ������ -> PROCESSENTRY32 ����ü�� process information ��� -> �ش� ���μ��� ���� �ִ� �� �̸����� Ȯ�� -> ����� handle �ݾ��ֱ�
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
        std::cout << "��� ���μ����� �߰����� ���߽��ϴ�." << std::endl;
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