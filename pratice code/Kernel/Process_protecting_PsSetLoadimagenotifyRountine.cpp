#include<ntddk.h>

/*
typedef struct _IMAGE_INFO {
  union {
	ULONG Properties; // 모든 비트값
	struct {
	  ULONG ImageAddressingMode : 8;  입력되는 값이 항상 같음 IMAGE_ADDRESSING_MODE_32BIT
	  ULONG SystemModeImage : 1;   커널모드의 구성요소의 경우 1 아닌 경우 사용자공간에서 이뤄지면 0으로 설정됨.
	  ULONG ImageMappedToAllPids : 1;
	  ULONG ExtendedInfoPresent : 1;
	  ULONG MachineTypeMismatch : 1;
	  ULONG ImageSignatureLevel : 4; // 코드 무결성 레이블 지정한 서명 수준
	  ULONG ImageSignatureType : 3;  서명형식
	  ULONG ImagePartialMap : 1;
	  ULONG Reserved : 12;
	};
  };
  PVOID  ImageBase;      // 이미지 가상주소
  ULONG  ImageSelector; // 0으로 설정된다함.
  SIZE_T ImageSize;       // imagesize
  ULONG  ImageSectionNumber;
} IMAGE_INFO, *PIMAGE_INFO;


*/


void FilterImageLoad(PUNICODE_STRING Imagename, HANDLE ProcessId, PIMAGE_INFO imageinfo) 
{
	

	if (imageinfo->SystemModeImage != 1) { // Dll Injection 또는 Process injection의 경우 다음과 같이 
		//사용자 공간에서 PE injection 등이 이뤄지기 때문에 SystemModelimage의 값이 0이 되어야한다.
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