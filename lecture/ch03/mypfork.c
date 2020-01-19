#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

main()
{
	pid_t pid;
	int status;
	
	pid = fork();

	if(pid < 0)	
	{
		perror("fork");
		exit(1);
    }
	
	if (pid == 0 )	/* child */
	{
    	printf("Child process ...\n");
		sleep(10);
		printf("Child Sleeping !!!\n");
        sleep(60);
//		exit(0); 0-all normal exit 
        exit(2);
        //kill(getpid(),        //);/* 시그널번호);*/
		
	}
	else
    {
        printf("Parent proocess ...\n");
		sleep(10);
        printf("Parent Waiting  ...\n");
		wait(&status);
/*******************************************************/
        if (WIFEXITED(status))
		{
			printf("Child Normal Exited by %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
		{
			printf("Child terminated by signal (SIG#=%d\n",WTERMSIG(status));
		}
		else if (WIFSTOPPED(status))
		{
			printf("Child terminated by execution Stop (SIG#=%d\n", WSTOPSIG(status)); 
        }


/******************************************************/
        sleep(10);
        printf("Parent Terminalted !!!\n");
	}

}  

