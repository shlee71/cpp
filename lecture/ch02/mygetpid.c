#include <stdio.h>
#include <unistd.h>

int main(void)
{
	printf("PID = %d\n", getpid());
	printf("PPID = %d\n", getppid());

	return 0;
}	
