#include<ntddk.h>

typedef struct {
	unsigned char buffer[4];
	int DataSize;
}DEVICE_EXTENSION;

void UNLOAD(PDRIVER_OBJECT pdriveobj) {

	UNICODE_STRING SymbolicLinkName;
	RtlInitUnicodeString(&SymbolicLinkName, L"\\DosDevices\\SAMPLEDRIVER");
	
	IoDeleteSymbolicLink(
		&SymbolicLinkName
	);

	IoDeleteDevice(pdriveobj->DeviceObject);
}

void DriverUnload(PDRIVER_OBJECT pDriverObj) {



	IoDeleteDevice(pDriverObj->DeviceObject);
}

NTSTATUS CreateDisPatch(PDEVICE_OBJECT DeviceObject, PIRP pIrp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	NTSTATUS status = STATUS_SUCCESS;
	pIrp->IoStatus.Status = STATUS_SUCCESS;
	KdPrint(("irp create\n"));
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return status;
}

NTSTATUS CloseDisPatch(PDEVICE_OBJECT DeviceObject, PIRP pirp) {

	UNREFERENCED_PARAMETER(DeviceObject);
	pirp->IoStatus.Status = STATUS_SUCCESS;
	IoCompleteRequest(pirp, 0);


	return STATUS_SUCCESS;
}

NTSTATUS ReadDisPatch(PDEVICE_OBJECT pDevice, PIRP irp) 
{
	PIO_STACK_LOCATION pStack;
	DEVICE_EXTENSION* pDE;
	pStack = IoGetCurrentIrpStackLocation(irp);
	int Length;
	unsigned char* UserBuffer;
	Length = pStack->Parameters.Write.Length;
	pDE = (DEVICE_EXTENSION*)pDevice->DeviceExtension;
	if (Length > pDE->DataSize) Length = pDE->DataSize;
	UserBuffer = (unsigned char*)irp->UserBuffer;
	memcpy(UserBuffer, pDE->buffer, Length);
	pDE->DataSize = Length;
	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = Length;
	IoCompleteRequest(irp, IO_NO_INCREMENT);

	


	return STATUS_SUCCESS;
}

NTSTATUS WriteDisPatch(PDEVICE_OBJECT pDevice, PIRP irp) 
{
	PIO_STACK_LOCATION pStack;
	DEVICE_EXTENSION* pDE;
	pStack = IoGetCurrentIrpStackLocation(irp);
	int Length;
	unsigned char* UserBuffer;
	Length=pStack->Parameters.Write.Length;
	if (Length > 4) Length = 4;

	UserBuffer = (unsigned char*)irp->UserBuffer;
	pDE = (DEVICE_EXTENSION*)pDevice->DeviceExtension;
	memcpy(pDE->buffer, UserBuffer, Length);
	pDE->DataSize = Length;
	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = Length;
	IoCompleteRequest(irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}
NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObj, PUNICODE_STRING RegPath) {
	UNREFERENCED_PARAMETER(RegPath);

	NTSTATUS status = STATUS_SUCCESS;
	PDEVICE_OBJECT gDevice = NULL;
	DEVICE_EXTENSION* pDE;
	UNICODE_STRING DeviceName;
	UNICODE_STRING SymbolicName;

	RtlInitUnicodeString(&DeviceName, L"\\Device\\SAMPLEDRIVER");
	RtlInitUnicodeString(&SymbolicName, L"\\DosDevice\\SAMPLEDRIVER");

	pDriverObj->MajorFunction[IRP_MJ_CREATE] = CreateDisPatch;
	pDriverObj->MajorFunction[IRP_MJ_CLOSE] = CloseDisPatch;
	pDriverObj->MajorFunction[IRP_MJ_READ] = ReadDisPatch;
	pDriverObj->MajorFunction[IRP_MJ_WRITE] = WriteDisPatch;
	
	pDriverObj->DriverUnload = UNLOAD;

	status = IoCreateDevice(
		pDriverObj,
		sizeof(DEVICE_EXTENSION),
		&DeviceName,
		FILE_DEVICE_UNKNOWN,
		0,
		FALSE,
		&gDevice
	);

	pDE = (DEVICE_EXTENSION*)gDevice->DeviceExtension;
	pDE->DataSize = 0;


	IoCreateSymbolicLink(&SymbolicName, &DeviceName);
	return STATUS_SUCCESS;
}
