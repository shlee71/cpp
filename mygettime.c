#include <stdio.h>
#include <sys/time.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    struct timeval curtime;

    gettimeofday(&curtime, NULL);
    printf("current seconds = %ld, mrcor seconds = %ld\n", curtime.tv_sec, curtime.tv_usec);

    int i;
    time_t c_time;

    clock_t oldtime, newtime;
    struct tms oldtms, newtms;
    double tick = sysconf(_SC_CLK_TCK);

    oldtime = times(&oldtms);
    if ( oldtime == -1 )
    {
        perror("old times");
        exit(1);
    }

    for ( i =0; i < 10000000; i++)
    {
        time(&c_time);
    }
    
    newtime = times(&newtms);
    if ( newtime == -1 )
    {
        perror("new times");
        exit(1);
    }

    printf("current time     : %s \n", ctime(&c_time));
    printf("Real Time : %.2f clocks \n", (newtime - oldtime)/tick);
    printf("User mode time : %.2f clocks \n", (newtms.tms_utime - oldtms.tms_utime)/tick);
    printf("System mode time : %.2f clocks \n", (newtms.tms_stime - oldtms.tms_stime)/tick);

    return 0;
}
