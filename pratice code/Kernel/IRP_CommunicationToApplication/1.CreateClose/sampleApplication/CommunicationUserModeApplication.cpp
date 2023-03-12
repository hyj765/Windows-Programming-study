#include<iostream>
#include<Windows.h>


int main() {
	HANDLE handle= NULL;
	
	handle = CreateFile(L"\\??\\MYSAMPLE", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if (handle == INVALID_HANDLE_VALUE) {
		printf("not connected");
	}
	else {
		printf("connected");
	}

	CloseHandle(handle);
}