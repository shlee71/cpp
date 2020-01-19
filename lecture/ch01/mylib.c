#include <stdio.h>
#include <time.h>
#include <sys/types.h>

int main(void)
{
	time_t cur_time;
	char *time_str;

	time(&cur_time);
	time_str=ctime(&cur_time);
	printf("Current Time = %s[%p]\n", time_str,time_str);

        cur_time += ( 60 * 60 * 24 );
        time_str=ctime(&cur_time);
        printf("Tomorrow Time = %s[%p]\n", time_str,time_str);


	return 0;
}
