#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler (int signo)
{
	printf("In SIGINT Handler...(signo#=%d) \n",signo);
}

void main()
{
	printf("*** Signal Test...\n");
    
	sleep(3);
	printf("1. Catching SININT\n");
	signal(SIGINT, handler);
	sleep(10);

	printf("2. Ignoring SIGINT..\n");
	signal(SIGINT, SIG_IGN);
	sleep(10);

	printf("3. Default Action of SIGINT .\n");
	signal(SIGINT, SIG_DFL);
	sleep(10);

	printf("End of Main\n");
	
}	
