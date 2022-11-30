#pragma warning(disable: 4996)
#define _CRT_SECURE_NO_WARNINGS 1
#include<Windows.h>
#include<iostream>


int main(int argc, char* argv[]) {
	HANDLE processResourece = nullptr; // resource¸¦ °¡Á®¿Ã handle;
	PVOID remoteBuffer;
	if (argc < 3) {
		printf("Usage program.exe [dllpath] [pid]\n");
	}
	LPCSTR dllpath = "";
	dllpath = argv[1];
	FILE* file = fopen(dllpath,"r");
	if (file == nullptr) {
		printf("dll path error\n");
		return 0;
	}
	fclose(file);
	DWORD pid;
	pid = atoi(argv[2]);
	
	processResourece = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (processResourece == nullptr) {
		std::cout << "injection fail" << std::endl;
		return 0;
	}
	remoteBuffer = VirtualAllocEx(processResourece, NULL, sizeof (dllpath+1), MEM_COMMIT,PAGE_READWRITE);
	WriteProcessMemory(processResourece, remoteBuffer, (LPVOID)dllpath, sizeof(dllpath+1), NULL);
	PTHREAD_START_ROUTINE startroutineaddress = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "LoadLibraryW");

	HANDLE loadthread = CreateRemoteThread(processResourece, NULL, 0, startroutineaddress, remoteBuffer, 0, NULL);
	WaitForSingleObject(loadthread, INFINITE);

	std::cout << " dll path allocated at : " << remoteBuffer << std::endl;
	VirtualFreeEx(loadthread, remoteBuffer, sizeof(dllpath+1), MEM_RELEASE);
	CloseHandle(processResourece);
	std::cout << "done";
	return 0;
}
