#include"PEBInternel.h"

void PEBParser::GetProcessHandle(long ProcessId) {
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);
}


void PEBParser::PrintProcessInfo() {
	if (hProcess == NULL) {
		printf("error target process is null");
		return;
	}
	HMODULE hNtdll = GetModuleHandle(TEXT("ntdll.dll"));
	NtQueryInformationProcessFunc NtQueryInformationProcess = reinterpret_cast<NtQueryInformationProcessFunc>(GetProcAddress(hNtdll, "NtQueryInformationProcess"));
	PROCESS_BASIC_INFORMATION pbi;
	ULONG RL;
	NTSTATUS status = NtQueryInformationProcess(hProcess, 0, &pbi, sizeof(pbi), &RL);

	if (status == 0) {
		std::cout << "PEB ADDRESS: " << pbi.PebBaseAddress << std::endl;
		std::cout << "AffinityMask: " << pbi.AffinityMask << std::endl;
		std::cout << "Base Property: " << pbi.BasePriority << std::endl;
		std::cout << "UniqueProcess: " << pbi.UniqueProcessId << std::endl;
	}
	else {
		std::cout << "Fail to Get Process Information" << std::endl;
	}


}

PEBParser::~PEBParser() {
	if (hProcess != NULL) CloseHandle(hProcess);
}

