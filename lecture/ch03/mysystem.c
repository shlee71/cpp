#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char cmd_buf[256];

	if (argc != 2)
	{	fprintf(stderr, "Usage : mysystem filename\n");
		exit(1);
	}

	printf("-----------------  system() start --------------------\n\n");
	strcpy(cmd_buf, "ls -l ");
	strcat(cmd_buf, argv[1]);
	system(cmd_buf);
	printf("\n-----------------  system() ended --------------------\n");
	return 0;
}
