#pragma once
#include<Windows.h>

typedef struct _PROCESS_BASIC_INFORMATION {
	NTSTATUS ExitStatus; // ���� �ڵ�
	PVOID PebBaseAddress; // peb block�� �ּ�
	ULONG_PTR AffinityMask; // ��ȣ�� ����ũ
	LONG BasePriority; // ���μ��� �켱����
	ULONG_PTR UniqueProcessId;
	ULONG_PTR InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION;

/* ����
typedef struct _PROCESS_BASIC_INFORMATION {
	NTSTATUS ExitStatus;
	PPEB PebBaseAddress;
	ULONG_PTR AffinityMask;
	KPRIORITY BasePriority;
	ULONG_PTR UniqueProcessId;
	ULONG_PTR InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION;
*/