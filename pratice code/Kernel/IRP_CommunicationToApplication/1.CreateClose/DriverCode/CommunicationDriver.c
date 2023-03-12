#include<ntddk.h>

NTSTATUS DispatchPassThru(PDEVICE_OBJECT DeviceObject, PIRP pIrp) 
{
	UNREFERENCED_PARAMETER(DeviceObject);
	NTSTATUS status = STATUS_SUCCESS;
	pIrp->IoStatus.Status = STATUS_SUCCESS;
	KdPrint(("irp create\n"));
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return status;
}


void unload(PDRIVER_OBJECT pdriveobj) {
	pdriveobj = pdriveobj;

	UNICODE_STRING SymbolicLinkName;
	RtlInitUnicodeString(&SymbolicLinkName, L"\\DosDevices\\MYSAMPLE");
	IoDeleteSymbolicLink(
		&SymbolicLinkName
	);

	IoDeleteDevice(pdriveobj->DeviceObject);
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObj, UNICODE_STRING RegistPath) {
	NTSTATUS status = STATUS_SUCCESS;
	PDEVICE_OBJECT DeviceObject = NULL;
	UNREFERENCED_PARAMETER(RegistPath);
	
	UNICODE_STRING uniDeviceName;
	UNICODE_STRING uniSymbolicName;
	RtlInitUnicodeString(&uniDeviceName, L"\\Device\\Sample");
	RtlInitUnicodeString(&uniSymbolicName, L"\\DosDevices\\MYSAMPLE");
	IoCreateSymbolicLink(&uniSymbolicName, &uniDeviceName);

	pDriverObj->DriverUnload = unload;
	pDriverObj->MajorFunction[IRP_MJ_CREATE] = DispatchPassThru;

	status = IoCreateDevice(
		pDriverObj,
		0,
		&uniDeviceName,
		FILE_DEVICE_UNKNOWN,
		0,
		FALSE,
		&DeviceObject
	);

	return status;
}