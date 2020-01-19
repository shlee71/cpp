#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(void)
{
	pid_t pid;
	
	pid = fork();
	switch(pid)
	{
	case -1 : 
		perror("fork");
		exit(1);
		break;
	case 0 :
		printf("CHILD PROCESS\n");
		sleep(10);
		printf("Child Exec ...\n");
		execlp("sleep", "SLEEP", "l0", (char *)0);
		perror("execlp");
		exit(1);
	default :
		wait(NULL);
		printf("child is dead\n");
		break;
	}
	return 0;
}
