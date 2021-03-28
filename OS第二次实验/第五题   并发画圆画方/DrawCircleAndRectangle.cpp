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

DWORD WINAPI drawCircle(LPVOID lpParam) {
	for (int i = 0; i <= 720; i++) {
		putpixel(100 + 50 * sin(i * 2 * PI / 720), 100 + 50 * cos(i * 2 * PI / 720), RED);
		Sleep(1);
	}
	return 0;
}
DWORD WINAPI drawRectangle(LPVOID lpParam) {

	for (int i = 1; i <= 180; i++) {
		putpixel(250 + i / 2, 55, BLUE);
		Sleep(1);
	}
	for (int i = 1; i <= 180; i++) {
		putpixel(340, 55 + i / 2, BLUE);
		Sleep(1);
	}
	for (int i = 1; i <= 180; i++) {
		putpixel(340 - i / 2, 145, BLUE);
		Sleep(1);
	}
	for (int i = 1; i <= 180; i++) {
		putpixel(250, 145 - i / 2, BLUE);
		Sleep(1);
	}
	return 0;
}
void draw() {
	initgraph(500, 300);
	HANDLE thread[2];
	thread[0] = CreateThread(NULL, 0, drawCircle, (LPVOID)0, NULL, NULL);
	thread[1] = CreateThread(NULL, 0, drawRectangle, (LPVOID)0, NULL, NULL);
	WaitForMultipleObjects(2, thread, TRUE, INFINITE);
	_getch();
}

void main() {
	draw();
}