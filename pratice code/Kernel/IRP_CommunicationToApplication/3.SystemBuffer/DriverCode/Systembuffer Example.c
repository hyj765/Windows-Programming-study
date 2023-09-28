#include<ntddk.h>



typedef struct {

	unsigned char buffer[100];
	int size;
} DEVICE_EXTENSION, * PDEVICE_EXTENSION;





void UNLOAD(PDRIVER_OBJECT pDrvObj) {

	UNICODE_STRING symName = RTL_CONSTANT_STRING(L"\\DosDevice\\MYDriver");
	IoDeleteSymbolicLink(&symName);
	IoDeleteDevice(pDrvObj->DeviceObject);

	KdPrint(("Driver Successfully Unloaded \r\n"));
}


NTSTATUS DispatchRoutine(PDEVICE_OBJECT pDeviceObj, PIRP irp) {

	PIO_STACK_LOCATION pStack=IoGetCurrentIrpStackLocation(irp);
	PDEVICE_EXTENSION pDe;
	int len;

	switch (pStack->MajorFunction)
	{
		case IRP_MJ_CREATE: {
			KdPrint(("create IRP request \r\n"));
			break;
		}
		case IRP_MJ_CLOSE: {
			KdPrint(("close IRP request \r\n"));
			break;
		}
		case IRP_MJ_READ: {
			len = pStack->Parameters.Read.Length;
			pDe = (PDEVICE_EXTENSION)pDeviceObj->DeviceExtension;
			if (len > pDe->size) len = pDe->size;
			unsigned char* userBuffer = irp->AssociatedIrp.SystemBuffer;
			memcpy(userBuffer, pDe->buffer, len);
			KdPrint(("kernel send data: %s \r\n", userBuffer));
			irp->IoStatus.Information = len;
			break;
		}
		case IRP_MJ_WRITE: {

			len = pStack->Parameters.Write.Length;
			if (len > 100) len = 100;
			pDe = (PDEVICE_EXTENSION)pDeviceObj->DeviceExtension;
			unsigned char* userBuffer = irp->AssociatedIrp.SystemBuffer;
			memcpy(pDe->buffer, userBuffer, len);
			pDe->size = len;
			KdPrint(("kernel receive data: %s \r\n", pDe->buffer));
			irp->IoStatus.Information = len;
			break;
		}


	}

	irp->IoStatus.Status = STATUS_SUCCESS;
	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDrvObj, PUNICODE_STRING pRegPath) {

	UNICODE_STRING symName;
	UNICODE_STRING deviceName;
	NTSTATUS status;
	PDEVICE_OBJECT deviceObj = NULL;
	DEVICE_EXTENSION* pDe;
	RtlInitUnicodeString(&deviceName,L"\\Device\\MYDriver123");
	RtlInitUnicodeString(&symName, L"\\??\\MYDriver123");

	pDrvObj->DriverUnload = UNLOAD;

	status = IoCreateDevice(pDrvObj,
		sizeof(DEVICE_EXTENSION),
		&deviceName,
		FILE_DEVICE_UNKNOWN,
		0,
		FALSE,
		&deviceObj);
	
	deviceObj->Flags |= DO_BUFFERED_IO;

	if (!NT_SUCCESS(status)) {
		KdPrint(("fail to createing IODEVICE \r\n"));

		return status;
	}


	pDe = (DEVICE_OBJECT*)deviceObj->DeviceExtension;
	pDe->size = 0;

	status = IoCreateSymbolicLink(&symName, &deviceName);
	
	if (!NT_SUCCESS(status)) {
		KdPrint(("fail to creating symbolic link \r\n"));
		IoDeleteDevice(deviceObj);
		return status;
	}

	for (int i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; ++i) {
		pDrvObj->MajorFunction[i] = DispatchRoutine;
	}
	
	KdPrint(("Driver Load \r\n"));

	return status;

}