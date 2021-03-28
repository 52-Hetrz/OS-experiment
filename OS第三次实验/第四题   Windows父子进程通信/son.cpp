#include <stdio.h>
#include<Windows.h>

#define SIZE 25


void right() {
	HANDLE ReadHandle;
	CHAR buffer[SIZE];
	DWORD read;
	ReadHandle = GetStdHandle(STD_INPUT_HANDLE);
	for (int i = 0; i <= 100; i++)
	{
		if (ReadFile(ReadHandle, buffer, SIZE, &read, NULL))
			printf("Child read %d\n", buffer[0]);
		else
			printf("error");

	}
}
int main()
{
	right();
	return 0;
}