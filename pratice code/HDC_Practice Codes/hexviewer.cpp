#include<Windows.h>
#include<iostream>
using namespace std;

char* ReadData(const std::wstring fpath, size_t* datasize) {

	FILE* de;
	char* data = NULL;
	const wchar_t* path = fpath.data();
	if (0 == _wfopen_s(&de, path, L"rb")) {
		fseek(de, 0, SEEK_END);
		*datasize = ftell(de);
		fseek(de, 0, SEEK_SET);
		if (*datasize > 0) {
			data = new char[*datasize];
			fread(data, *datasize, 1, de);
		}
		fclose(de);
		return data;
	}
	else {
		printf("파일 경로지정 실패....");
		exit(-1);
	}
}

int main(int argv,char* argc[]) {
	/*
		22.12.16 hex editor
		유사 헥사에디터
	*/
	size_t size;
	std::wstring temp = L"";
	printf("파싱 파일 경로 입력 ===>");
	wcin >> temp;
	if (temp == L"") {
		printf("경로지정 실패.");
		return -1;
	}
	char* data = ReadData(temp, &size);
	size_t offset = 0;
	int tsize = 0;
	int cur =0;

	printf("offset \t data \t \t\t\t\t\t   Decoded Text\n");
	printf("===========================================================================\n");
	while (tsize < size) {
		
		printf("%08x : ", offset);
		for (int i = 0; i < 16; ++i) {
			printf("%02X ", (unsigned char)data[offset+i]);	
		}
		for (int i = 0; i < 16; ++i) {
			if (data[offset + i] >= 0x20 && data[offset + i] <= 0x7E) printf("%c", data[offset + i]);
			else printf(".");
		}
		printf("\t");
		printf("\n");
		tsize += 16;
		offset += 16;
	}
	delete[] data;
}