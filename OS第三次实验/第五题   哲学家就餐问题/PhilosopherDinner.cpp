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

//红色：思考    蓝色：吃饭    绿色：拿起左边筷子     黄色：拿起右边筷子     黑色：放下筷子
void think(int i) {
	//printf_s("This is philosopher%d,I'm thinking.\n", i);
	setfillcolor(RED);
	fillcircle((i + 1) * 100, 400, 20);
	Sleep(rand() % 300 + 100);
}
void eating(int i) {
	//printf_s("This is philosopher%d,I'm eating.\n", i);
	setfillcolor(BLUE);
	fillcircle((i + 1) * 100, 400, 20);
	Sleep(rand() % 300 + 100);
}
DWORD WINAPI Philosopher_deadLock(LPVOID lpParam) {
	int ID = (int)lpParam;
	HANDLE left = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, chopsticksSemaphore[ID]);
	HANDLE right = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, chopsticksSemaphore[(ID + 1) % 5]);
	while (true) {
		WaitForSingleObject(left, INFINITE);
		setfillcolor(GREEN);
		fillcircle((ID + 1) * 100, 400, 20);
		//printf_s("This is Philosopher%d,I got my left chopsticks\n", ID);
		Sleep(rand() % 300 + 100);

		WaitForSingleObject(right, INFINITE);
		setfillcolor(YELLOW);
		fillcircle((ID + 1) * 100, 400, 20);
		//printf_s("This is Philosopher%d,I got my right chopsticks\n", ID);
		Sleep(rand() % 300 + 100);

		eating(ID);

		ReleaseSemaphore(left, 1, NULL);
		ReleaseSemaphore(right, 1, NULL);

		setfillcolor(BLACK);
		fillcircle((ID + 1) * 100, 400, 20);
		Sleep(rand() % 300 + 100);
		think(ID);
	}
	return 0;
}
void PhilosopherDinner_deadLock() {
	initgraph(800, 800);
	Chopsticks[0] = CreateSemaphore(NULL, 1, 1, "0");
	Chopsticks[1] = CreateSemaphore(NULL, 1, 1, "1");
	Chopsticks[2] = CreateSemaphore(NULL, 1, 1, "2");
	Chopsticks[3] = CreateSemaphore(NULL, 1, 1, "3");
	Chopsticks[4] = CreateSemaphore(NULL, 1, 1, "4");
	HANDLE philosophers[5];
	for (int i = 0; i <= 4; i++) {
		philosophers[i] = CreateThread(NULL, 0, Philosopher_deadLock, (LPVOID)i, NULL, NULL);
	}
	WaitForMultipleObjects(5, philosophers, TRUE, INFINITE);
}
DWORD WINAPI Philosopher_undeadLock(LPVOID lpParam) {
	int ID = (int)lpParam;

	HANDLE left = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, chopsticksSemaphore[ID]);
	HANDLE right = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, chopsticksSemaphore[(ID + 1) % 5]);
	HANDLE check = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, chopsticksSemaphore[(ID + 2) % 5]);
	while (true) {
		WaitForSingleObject(check, INFINITE);
		ReleaseSemaphore(check, 1, NULL);
		WaitForSingleObject(left, INFINITE);
		setfillcolor(GREEN);
		fillcircle((ID + 1) * 100, 400, 20);
		//printf_s("This is Philosopher%d,I got my left chopsticks\n", ID);
		Sleep(rand() % 300 + 100);
		WaitForSingleObject(right, INFINITE);
		setfillcolor(YELLOW);
		fillcircle((ID + 1) * 100, 400, 20);
		//printf_s("This is Philosopher%d,I got my right chopsticks\n", ID);
		Sleep(rand() % 300 + 100);
		eating(ID);
		ReleaseSemaphore(left, 1, NULL);
		ReleaseSemaphore(right, 1, NULL);
		setfillcolor(BLACK);
		fillcircle((ID + 1) * 100, 400, 20);
		Sleep(rand() % 300 + 100);
		think(ID);
	}
	return 0;
}
void PhilosopherDinner_undeadLock() {
	initgraph(800, 800);
	Chopsticks[0] = CreateSemaphore(NULL, 1, 1, "0");
	Chopsticks[1] = CreateSemaphore(NULL, 1, 1, "1");
	Chopsticks[2] = CreateSemaphore(NULL, 1, 1, "2");
	Chopsticks[3] = CreateSemaphore(NULL, 1, 1, "3");
	Chopsticks[4] = CreateSemaphore(NULL, 1, 1, "4");
	HANDLE philosophers[5];
	for (int i = 0; i <= 4; i++) {
		philosophers[i] = CreateThread(NULL, 0, Philosopher_undeadLock, (LPVOID)i, NULL, NULL);
	}
	WaitForMultipleObjects(5, philosophers, TRUE, INFINITE);
}

void main() {
	PhilosopherDinner_undeadLock();
}