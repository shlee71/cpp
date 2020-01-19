#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	int fd;

	if (argc != 2)
	{	fprintf(stderr, "Usage : myopen filename\n");
		exit(1);
	}

	if ((fd=open(argv[1], O_RDONLY)) == -1)
	{	perror("open");
		fprintf(stderr, "File Read Fail ...\n");
	}
	else
	{	printf("File Read Success!! fd=%d\n", fd);
		//close(fd);
	}

	if ((fd=open("MYDATA", O_WRONLY|O_CREAT|O_TRUNC, 0666)) == -1)
	{	perror("open2");
		fprintf(stderr, "File Create Fail ...\n");
	}
	else
	{	printf("file Create Success!! fd=%d\n", fd);
		close(fd);
	}
	
	return 0;
}
	
