#include<iostream>
#include<Windows.h>
#include"PEBInternel.h"

int main() {

	PEBParser pe;
	long pid;
	printf("���ϴ� process pid�� �Է��ϼ���. >>>> ");
	std::cin >> pid;

	pe.GetProcessHandle(pid);
	pe.PrintProcessInfo();
}