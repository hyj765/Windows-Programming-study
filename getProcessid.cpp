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
    PROCESSENTRY32 ppe;     //������ �ڷᱸ���� �����ϱ� ���� ��Ʈ��.  
    std::string target_p;
    std::cin >> target_p;
    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//system ���μ���(pid=0)�� ���¸� �о� �´�   
    ppe.dwSize = sizeof(PROCESSENTRY32);                        //��Ʈ�� ����ü ����� �����ش�.  
    bGet = Process32First(hSnapshot, &ppe);                     //��Ʈ�� �� �ڷḦ �����´�.  

    while (bGet)
    {
        WideCharToMultiByte(CP_ACP, 0, ppe.szExeFile, 260, buf, 260, NULL, NULL);
        if (c_find(buf,target_p)) {
            fprintf(stdout, "processName:%-15s\t", buf);          //���μ��� �̸��� ���  
            fprintf(stdout, "processID:%5d\n", ppe.th32ProcessID);//���μ��� ���̵� ���  
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