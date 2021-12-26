#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(void)
{
	pid_t c_pid1, c_pid2, ret_pid, parent_pid;	
	int i = 0;
	
	printf("mywaitpid start pid %d \n", getpid());
	parent_pid = getpid();
	printf("1st fork  \n");
	switch(c_pid1=fork())
	{
		case -1 : 
			perror("fork1");
			exit(1);
			break;
		case 0 :
			printf("%d : long time child process\n", getpid());
			sleep(5);
			exit(0);
			break;
		default:
			printf("2nd fork pid %d \n", getpid());
			switch(c_pid2 =fork())
			{
				case -1:
					perror("fork2");
					exit(1);
					break;
				case 0:
					printf("%d :short time child process \n", getpid()); 
					sleep(1);
					exit(0);
					break;
			}
			
			if ( parent_pid == getpid())
			{
				printf("still parent~~~\n");
			}
			
			while(1)
			{

				while((ret_pid = waitpid(-1, NULL, WNOHANG)) > 0)
				{
					printf("\nreturn value of waitpid(): %d\n", ret_pid);
					printf("wait processed %d\n", i);
				}
				
				if (errno == ECHILD){
					printf("no child\n");
					break;
				}
				if ( i== 1000) {
					putchar('.');
					fflush(stdout);
					i = 0;
				}
				i++;
			}
			break;
	}
}
