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

DWORD WINAPI thread1(LPVOID lpParam) {     //Ҫע���̺߳����Ĳ������Լ��ú���������
	for (int i = 1; i <= 1000; i++) {
		printf_s("This is Thread1 : %d\n", i);
		Sleep(0.5);
	}
	return 0;
}
DWORD WINAPI thread2(LPVOID lpParam) {
	for (int i = 1000; i >= 1; i--) {
		printf_s("This is Thread2 : %d \n", i);
		Sleep(0.5);
	}
	return 0;
}
void outputNaturalNumber() {                                                     //ʵ��3
	DWORD ThreadID;
	HANDLE thread[2];
	thread[0] = CreateThread(NULL, 0, thread1, (LPVOID)1, NULL, &ThreadID);     //CreateThread �����ĵ�������������Ҫһ���̺߳�����ַ
	thread[1] = CreateThread(NULL, 0, thread2, (LPVOID)1, NULL, &ThreadID);
	WaitForMultipleObjects(2, thread, TRUE, INFINITE);
}

void main() {
	outputNaturalNumber();
}