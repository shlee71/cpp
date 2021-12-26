#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	int pd, n=0;
	char rcvmsg[1024];

	if ((pd=open("./myfifo", O_RDONLY)) == -1)
	{	perror("open");
		exit(1);
	}

	while((n=read(pd, rcvmsg, 1023)) > 0)
	{	rcvmsg[n] = '\0';
		write(1, "namedpipe2> ", 12);
		write(1, rcvmsg, n);
	}
 
	if (n== -1)
	{	perror("read");
		exit(1);
	}
	write(1, "\n", 1);
	close(pd);
	return(0);
}	
