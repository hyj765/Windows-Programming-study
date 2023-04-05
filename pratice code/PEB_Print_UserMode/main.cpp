#include<iostream>
#include<Windows.h>
#include"PEBInternel.h"

int main() {

	PEBParser pe;
	long pid;
	printf("원하는 process pid를 입력하세요. >>>> ");
	std::cin >> pid;

	pe.GetProcessHandle(pid);
	pe.PrintProcessInfo();
}