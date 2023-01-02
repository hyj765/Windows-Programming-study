#include<ntddk.h>
#include<wdm.h>
/*
	
	PS_CREATE_NOTIFY_INFO{
	_in PCUNICODE_STRING ImageFileName; // File name
	_inout STSTATUS CreateStatus;  // Create Status true,false
	}

	eprocess  =kernel process struct
	
*/


void NotifyRoutine(PEPROCESS process, HANDLE ProcessId, PPS_CREATE_NOTIFY_INFO Createinfo)
{
	
	process = process;
	ProcessId = ProcessId;

	if (Createinfo == NULL) return;


	WCHAR* bufferString = ExAllocatePool(NonPagedPool,Createinfo->ImageFileName->Length);

	memset(bufferString, 0, Createinfo->ImageFileName->Length);
	memcpy(bufferString, Createinfo->ImageFileName->Buffer,Createinfo->ImageFileName->Length);
	_wcsupr(bufferString);
	if (wcswcs(bufferString, L"NOTEPAD.EXE")) {
		Createinfo->CreationStatus = STATUS_UNSUCCESSFUL;
	}
	return;
}


void SampleDriverUnload(PDRIVER_OBJECT pDrvObj) {
	pDrvObj = pDrvObj;
	PsSetCreateProcessNotifyRoutineEx(NotifyRoutine,TRUE);

}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObj, PUNICODE_STRING pRegistryPath) {
	pRegistryPath = pRegistryPath;

	pDriverObj->DriverUnload = SampleDriverUnload;
	PsSetCreateProcessNotifyRoutineEx(NotifyRoutine,FALSE);

	return STATUS_SUCCESS;
}