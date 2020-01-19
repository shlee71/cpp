#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	int status;
	
	switch(fork())
	{
		case -1 :
			exit(1);
			break;
		case 0 :
			sleep(3);
			//exit(0);
			exit(1);
			break;
		default :
			wait(&status);
			if (WIFEXITED(status)) {
				printf("exit code of child process : %d\n", WEXITSTATUS(status));
			}
	}
}
