#pragma once
#include<Windows.h>

typedef struct _PROCESS_BASIC_INFORMATION {
	NTSTATUS ExitStatus; // 종료 코드
	PVOID PebBaseAddress; // peb block의 주소
	ULONG_PTR AffinityMask; // 선호도 마스크
	LONG BasePriority; // 프로세스 우선순위
	ULONG_PTR UniqueProcessId; // 프로세스 PID
	ULONG_PTR InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION;

/* 원본
typedef struct _PROCESS_BASIC_INFORMATION {
	NTSTATUS ExitStatus;
	PPEB PebBaseAddress;
	ULONG_PTR AffinityMask;
	KPRIORITY BasePriority;
	ULONG_PTR UniqueProcessId;
	ULONG_PTR InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION;
*/
