#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	void *file;
	int flag=PROT_READ|PROT_WRITE;

	if ((fd=open("MYTEMP", O_RDWR|O_CREAT|O_TRUNC, 0666)) < 0)
	{	perror("File Open Error");
		exit(1);
	}

	printf("Before ftruncate()\n");
	system("ls -l MYTEMP");
	ftruncate(fd, 10240);
	printf("After ftruncate()\n");
	system("ls -l MYTEMP");

	if ((file=mmap((void *)0, 10240, flag, MAP_SHARED, fd, 0)) == (void *)-1)
	{	perror("mmap error");
		exit(1);
	}
	close(fd);
	strcpy((char *)file, "ftruncate() test \n");
	return 0;
}
	
	
