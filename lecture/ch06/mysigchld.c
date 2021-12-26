#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

void c_handler(int signo);

int main(void)
{
	struct sigaction act;

	act.sa_handler=c_handler;
	sigfillset(&act.sa_mask);
	act.sa_flags=SA_RESTART;
	sigaction(SIGCHLD, &act, (struct sigaction *)NULL);

	switch (fork())
	{
	case -1 :
		perror("fork");
		exit(1);
	case 0: 
		printf("CHILD 1 :%d\n", getpid());
		execlp("sleep", "sleep", "20", NULL);
		perror("child1");
		exit(1);
	default :
		switch (fork())
		{
		case -1 :
			perror("fork");
			exit(1);
		case 0:
			printf("CHILD 2 :%d\n", getpid());
			execlp("sleep", "sleep", "30", NULL);
			perror("child2");
			exit(1);
		default:
			printf("PARENT : %d\n", getpid());
			break;
		}
	}	
	
	while(1);
	return 0;
}


void c_handler(int signo)
{
	int status, saveerrno;
	pid_t pid;

	for (;;)
	{
		pid = waitpid(-1, &status, WNOHANG);

		if (pid == 0)
			break;
		else 
			if (pid == -1 && errno==ECHILD)
				break;
			else
				if (pid == -1)
				{ 
					perror("waitpid");
					abort();
				}
		printf("PID of the dead child = %d\n", pid);
	}
	return;
}	
