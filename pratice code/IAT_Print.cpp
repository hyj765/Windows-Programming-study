#include<Windows.h>
#include<iostream>

using namespace std;

void print_fileheader(PIMAGE_NT_HEADERS header) {
	cout <<std::hex<< "magic: " << header->OptionalHeader.Magic << endl; // optional
	cout << header->FileHeader.Characteristics << endl;
	cout << header->FileHeader.Machine << endl;
	cout << header->FileHeader.NumberOfSections << endl;
	cout << header->FileHeader.NumberOfSymbols << endl;
	cout << header->FileHeader.PointerToSymbolTable << endl;
	cout << header->FileHeader.SizeOfOptionalHeader << endl;
	cout << header->FileHeader.TimeDateStamp << endl;
}



int main() {

	LPVOID imagebase = GetModuleHandleA(NULL);
	PIMAGE_DOS_HEADER dosheader = (PIMAGE_DOS_HEADER)imagebase;
	PIMAGE_NT_HEADERS ntheader = (PIMAGE_NT_HEADERS)((DWORD_PTR)imagebase + dosheader->e_lfanew);
	IMAGE_DATA_DIRECTORY importdir = ntheader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
	PIMAGE_IMPORT_DESCRIPTOR iid = (PIMAGE_IMPORT_DESCRIPTOR)(importdir.VirtualAddress + (DWORD_PTR)imagebase);
	
	while (iid->Name != NULL) {

		LPCSTR libname = (LPCSTR)iid->Name + (DWORD_PTR)imagebase;
		cout << libname << endl;
		HMODULE lib = LoadLibraryA(libname);
		if (lib) {
			PIMAGE_THUNK_DATA originalfirstthunk, firstthunk;
			originalfirstthunk = (PIMAGE_THUNK_DATA)((DWORD_PTR)imagebase + iid->OriginalFirstThunk);
			cout << "fucntions \n";
			while (originalfirstthunk->u1.AddressOfData != NULL) {
				PIMAGE_IMPORT_BY_NAME functionName = (PIMAGE_IMPORT_BY_NAME)((DWORD_PTR)imagebase + originalfirstthunk->u1.AddressOfData);
				cout << std::string(functionName->Name) << endl;
				originalfirstthunk++;
			}
		}
		cout << "\n";
		iid++;
	}
}