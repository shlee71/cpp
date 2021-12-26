/*****  sigprocmask.c  ******/

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>

int main() 
{
	sigset_t toblock;

	sigemptyset(&toblock);
	sigaddset(&toblock, SIGINT);

	sigprocmask(SIG_BLOCK, &toblock, (sigset_t *)NULL);
	printf("Signal Blocked..\n");
	sleep(10);
	printf("Signal will be Unblocked...\n");
	sigprocmask(SIG_UNBLOCK, &toblock, (sigset_t *)NULL);

	printf("a SIGINT is ignored !!!\n");
	return 0;
}
