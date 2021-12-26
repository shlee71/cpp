#include <sys/types.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	struct rlimit mylimit;

	getrlimit(RLIMIT_FSIZE, &mylimit);
	printf("Current File Size : soft limit = %d, hard limit = %d\n",
		mylimit.rlim_cur, mylimit.rlim_max);

	getrlimit(RLIMIT_NPROC, &mylimit);
	printf("Current Number of Process : soft limit = %d, hard limit = %d\n",
		mylimit.rlim_cur, mylimit.rlim_max);

	getrlimit(RLIMIT_NOFILE, &mylimit);
	printf("Current Number of File : soft limit = %d, hard limit = %d\n",
		mylimit.rlim_cur, mylimit.rlim_max);


	mylimit.rlim_cur = 5;
	setrlimit(RLIMIT_NOFILE, &mylimit);
	getrlimit(RLIMIT_NOFILE, &mylimit);
	printf("Changed Number of File : soft limit = %d, hard limit = %d\n",
		mylimit.rlim_cur, mylimit.rlim_max);
	
	nofile_test();
	return 0;
}


int nofile_test(void)
{
	char *filename[6] = { "test1", "test2", "test3", "test4", "test5", "test6" };
	FILE *fp;
	int i;

	for (i=0; i<6; i++)
	{
		if ((fp=fopen(filename[i], "w")) == NULL)
		{	perror(filename[i]);
			exit(1);
		}
	}
	return 0;
}

