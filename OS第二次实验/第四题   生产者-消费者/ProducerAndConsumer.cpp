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

DWORD WINAPI Producer(LPVOID lpParam) {
	int id = (int)lpParam;
	HANDLE hEmpty = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, "empty");      //打开信号量hEmpty
	HANDLE hFull = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, "full");       //打开信号量hFull
	while (true) {
		WaitForSingleObject(hEmpty, INFINITE);                                       //对hEmpty进行P操作，检查是否有空位
		EnterCriticalSection(&cs);                                                   //进入临界区
		{food++;
		printf("This is Producer%d ,I'm making. Now there are %d Bread on the counter.\n", id, food);
		}
		LeaveCriticalSection(&cs);                                                   //离开临界区
		ReleaseSemaphore(hFull, 1, NULL);                                            //对hFull进行V操作，给食品柜上增加一个可用食品
		Sleep(100);
	}
	return 0;
}
DWORD WINAPI Consumer(LPVOID lpParam) {
	int id = (int)lpParam;
	HANDLE hFull = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, "full");       //唤醒信号量hFull
	HANDLE hEmpty = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, "empty");     //唤醒信号量hEmpty
	while (true) {
		WaitForSingleObject(hFull, INFINITE);                                        //对hFull进行P操作，检查是否有商品可以买
		EnterCriticalSection(&cs);                                                   //进入临界区
		{food--;
		printf_s("This is Consumer%d ,I'm bying.  Now there are %d Bread on the counter. \n", id, food);
		}
		LeaveCriticalSection(&cs);                                                   //离开缓冲区
		ReleaseSemaphore(hEmpty, 1, NULL);                                           //对hEmpty执行V操作，释放一个商品柜上的空位
		Sleep(100);
	}
	return 0;
}
void ProducerAndConsumer() {
	HANDLE hEmpty = CreateSemaphore(NULL, 5, 5, "empty");  //初始化食品柜空位置的信号量
	HANDLE hFull = CreateSemaphore(NULL, 0, 5, "full");    //初始化食品柜上食品数量信号量
	InitializeCriticalSection(&cs);                                 //初始化临界区
	HANDLE Producers[3];
	HANDLE Consumers[3];
	for (int i = 0; i <= 4; i++) {
		Producers[i] = CreateThread(NULL, 0, Producer, (LPVOID)(i + 1), NULL, NULL);
	}
	for (int i = 0; i <= 4; i++) {
		Consumers[i] = CreateThread(NULL, 0, Consumer, (LPVOID)(i + 1), NULL, NULL);
	}
	WaitForMultipleObjects(5, Producers, TRUE, INFINITE);           //等待生产者线程结束
	WaitForMultipleObjects(5, Consumers, TRUE, INFINITE);           //等待消费者线程结束

	DeleteCriticalSection(&cs);                                     //释放临界区
}

void main() {
	ProducerAndConsumer();
}