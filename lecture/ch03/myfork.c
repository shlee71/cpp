#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid;

	switch (pid=fork())
	{	
	case -1 : 
		perror("fork");
		break;
	case 0 :  // child process
		printf("CHILD PROCESS :%d\n", getpid());
		printf("Return Value of fork : %d\n\n", pid);
		sleep(3);
		system("echo CHILD");
		system("ps -l");
		exit(0);
		break;
	default :
		printf("PARENT PROCESS : %d\n", getpid());
		printf("Return Value of fork : %d\n\n", pid);
		sleep(7);
		system("echo PARENT");
		system("ps -l");
		break;
	}
	return 0;
}	

