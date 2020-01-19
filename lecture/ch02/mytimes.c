#include <sys/times.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int i;
	time_t c_time;

	clock_t oldtime, newtime;
	struct tms oldtms, newtms;
	double tick = sysconf(_SC_CLK_TCK);

	if ((oldtime=times(&oldtms)) == -1)
	{	perror("old times");
		exit(1);
	}

	for (i=1; i<=10000000; i++)
		time(&c_time);
	
	if ((newtime=times(&newtms)) == -1)
	{	perror("new times");
		exit(1);
	}

	printf("Real Time : %.2f  clocks\n", (newtime-oldtime)/tick);
	printf("User mode Time : %.2f clocks\n", (newtms.tms_utime-oldtms.tms_utime)/tick);
	printf("System mode Time : %.2f  clocks\n", (newtms.tms_stime-oldtms.tms_stime)/tick);
	return 0;
}	
