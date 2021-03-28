#include <stdio.h>
#include <stdlib.h>

int main()
{
	pid_t pid;
	pid = fork();

	if (pid == 0)
		printf("this is Son,and my pid is %d\n", pid);
	else if (pid < 0)
		printf("ERROR");
	else
		printf("this is father and pid is %d\n", pid);

	return 0;
}