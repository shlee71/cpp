#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	fd=open("anyfile",O_RDONLY);
	if(fd == -1)	{
		perror("myperror test open");
		exit(1);
	}
	return 0;
}
