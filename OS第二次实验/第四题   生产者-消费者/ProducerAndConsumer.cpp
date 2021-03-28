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
	HANDLE hEmpty = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, "empty");      //���ź���hEmpty
	HANDLE hFull = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, "full");       //���ź���hFull
	while (true) {
		WaitForSingleObject(hEmpty, INFINITE);                                       //��hEmpty����P����������Ƿ��п�λ
		EnterCriticalSection(&cs);                                                   //�����ٽ���
		{food++;
		printf("This is Producer%d ,I'm making. Now there are %d Bread on the counter.\n", id, food);
		}
		LeaveCriticalSection(&cs);                                                   //�뿪�ٽ���
		ReleaseSemaphore(hFull, 1, NULL);                                            //��hFull����V��������ʳƷ��������һ������ʳƷ
		Sleep(100);
	}
	return 0;
}
DWORD WINAPI Consumer(LPVOID lpParam) {
	int id = (int)lpParam;
	HANDLE hFull = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, "full");       //�����ź���hFull
	HANDLE hEmpty = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, "empty");     //�����ź���hEmpty
	while (true) {
		WaitForSingleObject(hFull, INFINITE);                                        //��hFull����P����������Ƿ�����Ʒ������
		EnterCriticalSection(&cs);                                                   //�����ٽ���
		{food--;
		printf_s("This is Consumer%d ,I'm bying.  Now there are %d Bread on the counter. \n", id, food);
		}
		LeaveCriticalSection(&cs);                                                   //�뿪������
		ReleaseSemaphore(hEmpty, 1, NULL);                                           //��hEmptyִ��V�������ͷ�һ����Ʒ���ϵĿ�λ
		Sleep(100);
	}
	return 0;
}
void ProducerAndConsumer() {
	HANDLE hEmpty = CreateSemaphore(NULL, 5, 5, "empty");  //��ʼ��ʳƷ���λ�õ��ź���
	HANDLE hFull = CreateSemaphore(NULL, 0, 5, "full");    //��ʼ��ʳƷ����ʳƷ�����ź���
	InitializeCriticalSection(&cs);                                 //��ʼ���ٽ���
	HANDLE Producers[3];
	HANDLE Consumers[3];
	for (int i = 0; i <= 4; i++) {
		Producers[i] = CreateThread(NULL, 0, Producer, (LPVOID)(i + 1), NULL, NULL);
	}
	for (int i = 0; i <= 4; i++) {
		Consumers[i] = CreateThread(NULL, 0, Consumer, (LPVOID)(i + 1), NULL, NULL);
	}
	WaitForMultipleObjects(5, Producers, TRUE, INFINITE);           //�ȴ��������߳̽���
	WaitForMultipleObjects(5, Consumers, TRUE, INFINITE);           //�ȴ��������߳̽���

	DeleteCriticalSection(&cs);                                     //�ͷ��ٽ���
}

void main() {
	ProducerAndConsumer();
}