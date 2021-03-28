#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <time.h>

#define MAX_LINE 1024
int food = 0;
CRITICAL_SECTION cs;
#define PI 3.1415926
HANDLE Chopsticks[5];
LPCSTR chopsticksSemaphore[5] = { "0","1","2","3","4" };


void PipCount() {
	CHAR buf[25] = { 0 };
	HANDLE writeHandle, readHandle;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	DWORD len;
	SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ANONYMOUS),NULL,TRUE };

	ZeroMemory(&si, sizeof(si));
	CreatePipe(&readHandle, &writeHandle, &sa, 0);

	GetStartupInfo(&si);
	si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	si.hStdInput = readHandle;
	si.dwFlags = STARTF_USESTDHANDLES;
	SetHandleInformation(writeHandle, HANDLE_FLAG_INHERIT, 0);
	//StartInfo.wShowWindow = SW_HIDE;

	if (CreateProcess(NULL, "C:\\Users\\life\\source\\repos\\ConsoleApplication3\\Debug\\son.exe", NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
		printf("Make process successfully\n");
	CloseHandle(readHandle);
	for (int i = 0; i <= 100; i++) {
		buf[0] = (char)i;
		WriteFile(writeHandle, buf, 25, &len, NULL);
	}
	CloseHandle(writeHandle);
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

void main() {
	PipCount();
}