#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{	fprintf(stderr, "Usage : mykill pid\n");
		exit(1);
	}

	if (kill(atoi(argv[1]), SIGTERM) == -1)
	{	if (errno == EINVAL)
			fprintf(stderr, "Invalid Signal \n");
		else if (errno == EPERM)
			fprintf(stderr, "No Permission\n");
		else if (errno == ESRCH)
			fprintf(stderr, "No search process\n");
	}
	return 0;
}
