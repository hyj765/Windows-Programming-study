#include<iostream>
#include<Windows.h>
#include<winternl.h>


using funcMessageBox = int (WINAPI*)(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);
funcMessageBox originalMsgBox = MessageBoxA;
int hookedMessageBox(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
{
	printf("hook success\n");
	int result;
	__asm {
		push uType
		push lpCaption
		push lpText
		push hWnd
		call originalMsgBox
		mov result, eax
		add esp, 16
	}
	return result;
}


int main() {

	LPVOID imageBase = GetModuleHandleA(NULL);
	PIMAGE_DOS_HEADER dosHeaders = (PIMAGE_DOS_HEADER)imageBase;
	PIMAGE_NT_HEADERS ntheader = (PIMAGE_NT_HEADERS)((DWORD_PTR)imageBase + dosHeaders->e_lfanew);
	PIMAGE_IMPORT_DESCRIPTOR importDescriptor = NULL;
	IMAGE_DATA_DIRECTORY importDirectory = ntheader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
	importDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(importDirectory.VirtualAddress + (DWORD_PTR)imageBase);
	LPCSTR libraryName = NULL;
	HMODULE library = NULL;
	PIMAGE_IMPORT_BY_NAME functionName = NULL;
	PIMAGE_THUNK_DATA retThunk = NULL;
	while (importDescriptor->Name != NULL) {

		libraryName = (LPCSTR)importDescriptor->Name + (DWORD_PTR)imageBase;
		library = LoadLibraryA(libraryName);

		if (library) {
			PIMAGE_THUNK_DATA originalFirstThunk = NULL;
			PIMAGE_THUNK_DATA firstThunk = NULL;
			originalFirstThunk = (PIMAGE_THUNK_DATA)((DWORD_PTR)imageBase + importDescriptor->OriginalFirstThunk);
			firstThunk = (PIMAGE_THUNK_DATA)((DWORD_PTR)imageBase + importDescriptor->FirstThunk);
			while (originalFirstThunk->u1.AddressOfData != NULL)
			{

				functionName = (PIMAGE_IMPORT_BY_NAME)((DWORD_PTR)imageBase + originalFirstThunk->u1.AddressOfData);

				if (std::string(functionName->Name).compare("MessageBoxA") == 0)
				{
					DWORD oldProtect = 0;
					VirtualProtect((LPVOID)(&firstThunk->u1.Function), 8, PAGE_READWRITE, &oldProtect);
					firstThunk->u1.Function = (DWORD_PTR)hookedMessageBox;

					
				}
				++originalFirstThunk;
				++firstThunk;
			}
		}
		importDescriptor++;
	}
	MessageBoxA(NULL, "msg", "msg", 0);

}