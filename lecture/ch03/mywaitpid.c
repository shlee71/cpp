#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(void)
{
	pid_t c_pid1, c_pid2, ret_pid;
	int i=0;

	switch (c_pid1=fork())
	{	
	case -1 : 
		perror("fork");
		exit(1);
		break;
	case 0 :  
		printf("%d :long time child process\n", getpid());
		sleep(10);
		exit(0);
		break;
	default :
		switch (c_pid2=fork())
		{
			case -1 : 
				perror("fork");
				exit(1);
				break;
			case 0 :
				printf("%d :short time child process\n", getpid());
				sleep(1);
				exit(0);
				break;
		}


		while (1)
		{
			while ((ret_pid=waitpid(-1, NULL, WNOHANG)) > 0)
			{	
				printf("\nreturn value of waitpid():%d\n",
						ret_pid);
			}
			if (errno == ECHILD)
			{
				printf("no child\n");
				break;
			}
			if (i == 1000)
			{
				putchar('.');
				fflush(stdout);
				i=0;
			}
			i++;
		}
		break;
	} 
}

