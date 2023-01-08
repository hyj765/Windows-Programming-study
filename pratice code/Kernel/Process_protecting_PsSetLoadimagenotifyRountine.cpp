#include<ntddk.h>

/*
typedef struct _IMAGE_INFO {
  union {
	ULONG Properties; // ��� ��Ʈ��
	struct {
	  ULONG ImageAddressingMode : 8;  �ԷµǴ� ���� �׻� ���� IMAGE_ADDRESSING_MODE_32BIT
	  ULONG SystemModeImage : 1;   Ŀ�θ���� ��������� ��� 1 �ƴ� ��� ����ڰ������� �̷����� 0���� ������.
	  ULONG ImageMappedToAllPids : 1;
	  ULONG ExtendedInfoPresent : 1;
	  ULONG MachineTypeMismatch : 1;
	  ULONG ImageSignatureLevel : 4; // �ڵ� ���Ἲ ���̺� ������ ���� ����
	  ULONG ImageSignatureType : 3;  ��������
	  ULONG ImagePartialMap : 1;
	  ULONG Reserved : 12;
	};
  };
  PVOID  ImageBase;      // �̹��� �����ּ�
  ULONG  ImageSelector; // 0���� �����ȴ���.
  SIZE_T ImageSize;       // imagesize
  ULONG  ImageSectionNumber;
} IMAGE_INFO, *PIMAGE_INFO;


*/


void FilterImageLoad(PUNICODE_STRING Imagename, HANDLE ProcessId, PIMAGE_INFO imageinfo) 
{
	

	if (imageinfo->SystemModeImage != 1) { // Dll Injection �Ǵ� Process injection�� ��� ������ ���� 
		//����� �������� PE injection ���� �̷����� ������ SystemModelimage�� ���� 0�� �Ǿ���Ѵ�.
		if (wcsstr(Imagename->Buffer, L"Terminate")) {
				//Process Protecting
			DbgPrintEx(DPFLTR_ACPI_ID, DPFLTR_INFO_LEVEL, "is it Driver");
		}

	}
	else {
		DbgPrintEx(DPFLTR_ACPI_ID, DPFLTR_INFO_LEVEL, "is it Driver");
	}
}



void unload(PDRIVER_OBJECT pDriver){
	/*
		DRIVER UNLOAD FUCNTION 
		
	*/
	PsRemoveLoadImageNotifyRoutine(FilterImageLoad);
	DbgPrintEx(DPFLTR_ACPI_ID,DPFLTR_INFO_LEVEL,"[Driver unload Complete]");
};


NTSTATUS DriverEntry(PDRIVER_OBJECT pDriver, PUNICODE_STRING pRegPath) 
{
	
	_Unreferenced_parameter_(pRegPath);
	pDriver->DriverUnload = unload;

	if (PsSetLoadImageNotifyRoutine(&FilterImageLoad) != STATUS_SUCCESS) {
		DbgPrintEx(DPFLTR_ACPI_ID, DPFLTR_INFO_LEVEL,"Filtering Fail");
	}

	return STATUS_SUCCESS;

}