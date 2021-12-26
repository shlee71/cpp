#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

char *pgm;
void handler(int sig);

void main( int argc, char **argv)
{
	struct sigaction act;
	if ( argc != 3 )
	{
		fprintf(stderr,"ussage > myarm pgm-name %ld \n", argc);
		exit(1);
    }
	
	if ( fork() != 0 ) exit(0);

	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	printf("Child Alarm Start\n");

	sigaction(SIGALRM, &act, 0);
	strncpy(pgm, argv[2], strlen(argv[2]));

	alarm(atoi(argv[1]));
    pause();
}

void handler( int sig)
{
	printf("Handler Start\n");
	printf("%s\n",execlp(pgm, pgm, 0));
	perror("execlp");
	exit(1);
}
