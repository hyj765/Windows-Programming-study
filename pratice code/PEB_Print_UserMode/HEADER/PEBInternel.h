#pragma once
#include<Windows.h>
#include<iostream>
#include"HEADER/InternelStruct.h"

typedef NTSTATUS(WINAPI* NtQueryInformationProcessFunc)(
	HANDLE ProcessHandle,
	DWORD ProcessInformationClass,
	PVOID ProcessInformation,
	ULONG ProcessInformationLength,
	PULONG ReturnLength
	);

class PEBParser {
private:
	HANDLE hProcess = NULL;
public:
	void GetProcessHandle(long ProcessId);

	void PrintProcessInfo();
	~PEBParser();
};
