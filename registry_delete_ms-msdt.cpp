#include<iostream>
#include<Windows.h>

class Register_Manager {
private:	
	HKEY hKey;
	DWORD dwBytes = 100;
public:

	void deleteRegister(HKEY hkeyRoot) {
		LONG Result;
		Result = RegDeleteKey(hkeyRoot,TEXT("ms-msdt"));

		if (Result == ERROR_SUCCESS) {
			printf("ms-msdt delete");
		}
		

		Result = RegOpenKeyEx(hkeyRoot, TEXT("ms-msdt"), 0, KEY_READ, &hKey);

		if (Result != ERROR_SUCCESS)
		{
			if (Result == ERROR_FILE_NOT_FOUND) {
				printf("Key not found.\n");
				
			}
			else {
				printf("Error opening key.\n");
				
			}
		}

		return;
	}

};

int main() {
	Register_Manager s;
	s.deleteRegister(HKEY_CLASSES_ROOT);
}