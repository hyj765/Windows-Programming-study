#include<ntddk.h>

typedef struct
{
	unsigned char buffer[4];
	int size;
}DEVICE_EXTENSION;

void DriverUnload(PDRIVER_OBJECT pDriverObj) {
	UNICODE_STRING symbol;

	pDriverObj = pDriverObj;

	RtlInitUnicodeString(&symbol, L"\\DosDevices\\SAMPLEDRIVER");
	IoDeleteSymbolicLink(&symbol);
	IoDeleteDevice(pDriverObj->DeviceObject);
}

NTSTATUS CreateDispatch(PDEVICE_OBJECT pDeviceObj, PIRP irp) {

	pDeviceObj = pDeviceObj;
	irp = irp;
	irp->IoStatus.Status = STATUS_SUCCESS;
	IoCompleteRequest(irp, 0);
	return STATUS_SUCCESS;
}
NTSTATUS CloseDispatch(PDEVICE_OBJECT pDeviceObj, PIRP irp) {

	pDeviceObj = pDeviceObj;
	irp = irp;
	irp->IoStatus.Status = STATUS_SUCCESS;
	IoCompleteRequest(irp, 0);
	return STATUS_SUCCESS;
}

NTSTATUS WriteDispatch(PDEVICE_OBJECT pDeviceObj, PIRP irp) {
	PIO_STACK_LOCATION pStack;
	int len;
	unsigned char* pUserBuffer;
	DEVICE_EXTENSION* pDE;

	pStack = IoGetCurrentIrpStackLocation(irp);
	len = pStack->Parameters.Write.Length;
	if (len > 4) len = 4;
	pUserBuffer = irp->AssociatedIrp.SystemBuffer;
	pDE = (DEVICE_EXTENSION *)pDeviceObj->DeviceExtension;
	memcpy(pDE->buffer, pUserBuffer, len);
	pDE->size = len;

	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = len;
	IoCompleteRequest(irp, 0);

	return STATUS_SUCCESS;
}

NTSTATUS ReadDispatch(PDEVICE_OBJECT pDeviceObj, PIRP irp) {
	PIO_STACK_LOCATION pStack;
	int len;
	unsigned char* pUserBuffer;
	DEVICE_EXTENSION* pDE;

	pStack = IoGetCurrentIrpStackLocation(irp);
	len = pStack->Parameters.Write.Length;
	if (len > 4) len = 4;
	pUserBuffer = irp->AssociatedIrp.SystemBuffer;
	pDE = (DEVICE_EXTENSION*)pDeviceObj->DeviceExtension;
	memcpy(pUserBuffer,pDE->buffer, len);
	pDE->size = len;

	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = len;
	IoCompleteRequest(irp, 0);

	return STATUS_SUCCESS;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObj, PUNICODE_STRING regstPath) 
{
	UNREFERENCED_PARAMETER(regstPath);
	PDEVICE_OBJECT DeviceObj = NULL;
	NTSTATUS status;
	UNICODE_STRING DeviceName;
	UNICODE_STRING symbolicName;
	DEVICE_EXTENSION* pDE;

	pDriverObj->MajorFunction[IRP_MJ_CREATE] = CreateDispatch;
	pDriverObj->MajorFunction[IRP_MJ_CLOSE] = CloseDispatch;
	pDriverObj->MajorFunction[IRP_MJ_READ] = ReadDispatch;
	pDriverObj->MajorFunction[IRP_MJ_WRITE] = WriteDispatch;

	pDriverObj->DriverUnload = DriverUnload;
	RtlInitUnicodeString(&DeviceName,L"\\Device\\SAMPLEDRIVER");
	RtlInitUnicodeString(&symbolicName, L"\\DosDevices\\SAMPLEDRIVER");
	status = IoCreateDevice(
		pDriverObj,
		sizeof(DEVICE_EXTENSION),
		&DeviceName,
		FILE_DEVICE_UNKNOWN,
		0,
		FALSE,
		&DeviceObj
	);
	DeviceObj->Flags |= DO_BUFFERED_IO;
	
	pDE = (DEVICE_EXTENSION*)DeviceObj->DeviceExtension;
	pDE->size = 0;
	IoCreateSymbolicLink(&symbolicName, &DeviceName);
	return STATUS_SUCCESS;
}


