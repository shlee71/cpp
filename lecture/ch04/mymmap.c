#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char**argv)
{
	int fd;
//	void *file = NULL;
	void *file;
	struct stat sb;
	int flag = PROT_READ;

	if (argc < 2)
	{	fprintf(stderr, "Usage input\n");
		exit(1);
	}

	if ((fd=open(argv[1], O_RDONLY))< 0)
	{	perror("File Open Error");
		exit(1);
	}
	if (fstat(fd, &sb) < 0)
	{	perror("fstat error");
		exit(1);
	}
	if ((file=mmap((void *)0, sb.st_size, flag, MAP_SHARED, fd, 0)) == (void *) -1)
	{	perror("mmap error");
		exit(1);
	}
	printf("%s\n", (char *)file);
	close(fd);
}
	
