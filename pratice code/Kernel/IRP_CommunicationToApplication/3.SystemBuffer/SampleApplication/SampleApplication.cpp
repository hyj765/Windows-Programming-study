#include<iostream>
#include<Windows.h>

using namespace std;



int main() {

	HANDLE handle= CreateFile(L"\\\\.\\MYDriver123",GENERIC_READ | GENERIC_WRITE, 0,NULL,OPEN_EXISTING,0,NULL);
	
	if (handle == INVALID_HANDLE_VALUE) {
		
		printf("fail to get handle \r\n");
		return 0;
	}


	int flag;
	char buffer[100];
	DWORD dReq;
	while (1) {

		printf("input 0 then exit this routine \r\n");
		cin >> flag;
		
		cin.ignore();
		if (flag == 0) break;
	
		printf("you choose talking with device driver \n");
		printf("press any word here =======>");
		fgets(buffer,100,stdin);
		printf("send: %s \r\n", buffer);
		WriteFile(handle, buffer, 100, &dReq, NULL);
		
		ReadFile(handle, buffer, 100, &dReq, NULL);
		printf("receivce %s \r\n", buffer);
	}



}