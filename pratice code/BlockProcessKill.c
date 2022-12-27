#include<ntifs.h>

ULONG ProcessId = 1552;
NTSTATUS DriverEntry(PDRIVER_OBJECT pDrvObj, PUNICODE_STRING pRegistryPath) {
	PEPROCESS pEprocess = NULL;
	pDrvObj = pDrvObj;
	pRegistryPath = pRegistryPath;
	
	if (ProcessId == 0) goto exit;
	PsLookupProcessByProcessId((HANDLE)ProcessId, &pEprocess);
	if (pEprocess) {
		*(unsigned char*)(((unsigned char*)pEprocess) - 0x15) = 0x14;
	}
	exit:
		return STATUS_UNSUCCESSFUL;
}