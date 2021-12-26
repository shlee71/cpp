#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MAXSIZE 4096

int main(void)
{
	int pd[2];
	pid_t pid;
	int n;
	char buf[MAXSIZE];

	if (pipe(pd) == -1)
	{	perror("pipe");
		exit(1);
	}

	switch(pid=fork())
	{
	case -1 : 
		perror("fork");
		exit(1);
		break;
	case 0 :
		close(pd[0]);
		dup2(pd[1], 1);
		close(pd[1]);
		execlp("ls", "ls", "-l", (char *)NULL);
		perror("execlp");
		exit(1);
		break;
	default :
		close(pd[1]);
		n=read(pd[0], buf, MAXSIZE);
		buf[n] = '\0';
		close(pd[0]);
		printf("PARENT : %s from CHILD\n", buf);
		
		if (waitpid(pid, (int *)NULL, 0) == -1)
		{	perror("waitpid");
			exit(1);
		}
		break;
	}
	return 0;
}	
