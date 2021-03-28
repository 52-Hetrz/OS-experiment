#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <time.h>

void countTime() {
	int num = 50;
	clock_t start, finish;
	int a[50][50] = { 0 };


	for (int s = 0; s < 4; s++) {
		start = clock();
		for (int i = 0; i < 50000; i++) {
			for (int j = 0; j < 50; j++)
				for (int k = 0; k < 50; k++)
					a[j][k] = 1;
		}
		finish = clock();

		printf("先行后列: %f \n", ((double)finish - (double)start));

		start = clock();
		for (int i = 0; i < 50000; i++) {
			for (int j = 0; j < 50; j++)
				for (int k = 0; k < 50; k++)
					a[k][j] = 1;
		}
		finish = clock();

		printf("先列后行: %f \n \n", ((double)finish - (double)start));
	}
}

void main() {
	countTime();
}