/***  mmap2.c  ***/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fdin, fdout;
	char *src, *dst;
	struct stat statbuf;

	if (argc != 3)
    {   fprintf(stderr, "Usage : %s <fromfile> <tofile>\n", argv[0]);
   	    exit(1);
    }

	if ((fdin=open(argv[1], O_RDONLY)) < 0)
	{   perror("fromfile");
		exit(1);
    }
    if ((fdout=open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0)
   	{   perror("tofile");
		exit(1);
 	}

	if (fstat(fdin, &statbuf) < 0)
	{   perror("fstat");
		exit(1);
  	}

	ftruncate(fdout, statbuf.st_size);

	if ((src=mmap(0, statbuf.st_size, PROT_READ, MAP_PRIVATE, fdin, 0)) == (caddr_t) -1)
	{	perror("mmap");
		exit(1);
	}
	if ((dst=mmap(0, statbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fdout, 0)) == (caddr_t) -1)
	{   perror("mmap");
		exit(1);
	}

	close(fdin);
	close(fdout);
	memcpy(dst, src, statbuf.st_size);
	exit(0);
}
