#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

static int alarm_flag=0;

void alarm_handler(int sig)
{
	alarm_flag =1 ;
}

int main(void)
{
	signal(SIGALRM, alarm_handler);
	alarm(5);
	pause();
	if (alarm_flag)
		printf("ALARM\n");
	return 0;
}
