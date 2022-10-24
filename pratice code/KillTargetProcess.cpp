#include<Windows.h>
#include<TlHelp32.h>
#include<iostream>
using namespace std;



void GetProcessInfoAll(PROCESSENTRY32 process) {
	printf("=======================process ==================\n");
	printf("PID: %d \n", process.th32ProcessID);
	printf("PPID: %d \n", process.th32ParentProcessID);
	printf("FileExeName: %s \n", process.szExeFile);
	printf("\n");
}

void KillProcess(DWORD PID) {

	HANDLE hProcess = NULL;
	if (hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, PID)) {
		TerminateProcess(hProcess, 0);
	}
	CloseHandle(hProcess);
}

int main() {


	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if (snapshot != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 pe32 = {sizeof(PROCESSENTRY32
			)};
		if (Process32First(snapshot, &pe32)) {
			do {
				GetProcessInfoAll(pe32);
			} while (Process32Next(snapshot, &pe32));
		}
		CloseHandle(snapshot);
	}
	DWORD pid = NULL;
	cin >> pid;
	KillProcess(pid);
	printf("\nProcess Kill Success");
}