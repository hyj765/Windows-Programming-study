#include<iostream>
#include<Windows.h>
#include"HEADER/PEBInternel.h"

int main() {

	PEBParser pe;
	long pid;
	printf("¿øÇÏ´Â process pid¸¦ ÀÔ·ÂÇÏ¼¼¿ä. >>>> ");
	std::cin >> pid;

	pe.GetProcessHandle(pid);
	pe.PrintProcessInfo();
}
