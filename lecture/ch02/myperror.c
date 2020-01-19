#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(void)
{
	int fd;
	fd = open("/etc/shadow",O_RDONLY);
	if(fd = -1)
	{
		printf("errno = %d\n",errno);
		perror("open");
		exit(1);
	}
	return 0;
}
