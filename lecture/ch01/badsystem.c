#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void)
{
	time_t *cur_time;
	//time(&cur_time);
	cur_time =(time_t*) malloc(sizeof(time_t));
    time(cur_time);
	printf("Current Time=%d\n", *cur_time);
}
