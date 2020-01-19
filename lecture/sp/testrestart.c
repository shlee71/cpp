/*****   testrestart.c  ******/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void handler(int);
main()
{
	struct sigaction act;
	int len;
	char line[100];

	act.sa_handler=handler;
	//act.sa_flags=SA_RESTART;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);

	if (sigaction(SIGINT, &act, 0) == -1)
	{	perror("sigaction error");
		exit(1);
	}

	write(1, "Input the string:", 18);
	len=read(0, line, sizeof(line));
	if (len < 0) 
	{	perror("read");
		exit(1);
	}
	write(1, "string read:", 13);
	write(1, line, len);
}

void handler(int signo)
{
	write(1, "caught signal->INT\n", 21);
	write(1, "Input the string:", 18);
}
