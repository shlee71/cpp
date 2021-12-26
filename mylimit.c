#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
int nofile_test(void);

int main(void)
{
    struct rlimit mylimit;

    getrlimit(RLIMIT_FSIZE, &mylimit);
    printf("Current File Size      : soft limit %ld, hard limit %ld\n", mylimit.rlim_cur, mylimit.rlim_max);
    getrlimit(RLIMIT_NPROC, &mylimit);
    printf("Current Number of Proc : soft limit %ld, hard limit %ld\n", mylimit.rlim_cur, mylimit.rlim_max);

    mylimit.rlim_cur= 5;
    getrlimit(RLIMIT_CPU, &mylimit);
    getrlimit(RLIMIT_FSIZE, &mylimit);
    printf("Current File Size      : soft limit %ld, hard limit %ld\n", mylimit.rlim_cur, mylimit.rlim_max);


    getrlimit(RLIMIT_CPU, &mylimit);
    printf("Current Speed of CPU   : soft limit %ld, hard Limit %ld\n", mylimit.rlim_cur, mylimit.rlim_max);

    return 0;
}

int nofile_test(void)
{
    char *filename[6]= {"test1","test2","test3","test4","test5","test6"};
    FILE *fp;

    for ( int i =0; i < 6; i++)
    {
        if(( fp=fopen(filename[i], "w")) == NULL)
        {
            perror(filename[i]);
            exit(1);
        }
    }

    return 0;
}



