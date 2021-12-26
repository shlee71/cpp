#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	int pd, n;
	char msg[1024];

	if ((pd=open("./myfifo", O_WRONLY)) == -1)
	{	perror("open");
		exit(1);
	}

	while(1)
	{	printf("namedpipe1> ");
		fgets(msg, 1023, stdin);
		if (strncmp(msg, "quit", 4) == 0)
			break;
		if ((n=write(pd, msg, strlen(msg))) == -1)
		{	perror("write");
			exit(1);
		}
	}
	close(pd);
	return(0);
}	
