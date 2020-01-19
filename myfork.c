#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid;
	
	switch(pid = fork())
	{
		case -1 : 
			perror("fork");
			break;
		case 0 : // child process
			printf("CHILD Process : %d\n", getpid());
			sleep(3);
			system("echo CHILD : ps -l");
			system("ps -l");
			exit(0);
			break;
		default :
			printf("PARENT Process : %d\n", getpid());
			printf("Return value of Fork : %d\n", pid);
			sleep(7);
			system("echo PARENT : ps -l");
			system("ps -l");
			break;
	}
	
	return 0;
}
