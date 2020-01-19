#include <stdio.h>
#include <time.h>
#include <sys/types.h>

int main(void)
{
	time_t cur_time;
	time(&cur_time);
	printf("Current Time=%d\n", cur_time);
}
