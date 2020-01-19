#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	int status;
	
	switch(pid =fork())
	{
		case -1 :
				perror("fork");
				break;
		case 0 :
				sleep(3);
				printf("CHILD PROCESS : %d\n", getpid());
				system("ps -l");
				exit(0);
				break;
		default :
				wait(&status);
				if ( WIFEXITED(status)) {
					printf("Child Process is deaded by exit()\n");
				} else if ( WIFSIGNALED(status)) {
					printf("Child Process is deaded by SIGNAL\n");
				}
				
				printf("PARENT PROCESS : %d\n", getpid());
				printf("Return Value of fork : %d\n", pid);
				system("ps -l");
				break;
	}
	
	return 0;
}
