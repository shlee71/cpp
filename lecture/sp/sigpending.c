/*** sigpeinding.c ***/

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>

int main()
{   sigset_t toblock, checkblock;
  
     sigemptyset(&toblock);
     sigemptyset(&checkblock);
     sigaddset(&toblock, SIGINT);
     
     sigprocmask(SIG_BLOCK, &toblock, (sigset_t *)NULL);
     sleep(5);
     sigpending(&checkblock);

     if (sigismember(&checkblock, SIGINT))
		printf("^C pressed!!!\n");
     sigprocmask(SIG_UNBLOCK, &toblock, (sigset_t *)NULL);

     printf("SIGINT is ignored!!!\n");
     return 0;
}

