#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(void)
{
	pid_t pid;
    int *status;
	
	pid = fork();
	
	switch(pid)
	{
		case -1:
			perror("fork");
			exit(-1);
			break;
		case 0 :
			printf("CHILD Process\n");
			//execlp("ls", "ls","-l",(char *) 0);
            execl("/bin/ls","ls","-l",(char *) 0);
			perror("execl");
			exit(0);
			break;
		default:
			wait(status);
			printf("CHILD is dead\n");
			break;
	}
	return 0;
}
