#include<iostream>
#include<Windows.h>


using namespace std;

int main() {

	HANDLE handle;
	BOOL bRet;
	UCHAR buffer[5] ={ 1, };
	DWORD dwRet;
	handle = CreateFile(L"\\??\\SAMPLEDRIVER",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
	bRet = WriteFile(handle, "Hola", 5, &dwRet, NULL);
	if (!bRet) {
		printf("Write Fail");
	}
	printf("Write: dwRet =%d \n", dwRet);

	bRet = ReadFile(handle, buffer, 5, &dwRet,NULL);
	if (!bRet) {
		printf("Driver Buffer Read Fail");
	}
	printf("Read: dwRet =%d \n", dwRet);
	printf("%s\n",&buffer);

	CloseHandle(handle);
	
}