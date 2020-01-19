#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void redirect_out(char *filename);

int main(int argc, char *argv[])
{
	char *filename;

	if (argc < 2)
	{	printf("STDOUT\n");
		filename="";
	}
	else
	{	printf("REDIRECT OUT to %s\n", argv[1]);
		filename = argv[1];
	}

	redirect_out(filename);
	return 0;
}


void redirect_out(char *filename)
{
	int fd;

	if (*filename != '\0')
	{	if ((fd=open(filename, O_WRONLY|O_CREAT|O_TRUNC, 0666)) == -1)
		{	perror("open");
			exit(1);
		}
		close(1);
		dup(fd);
		close(fd);
	}
	printf("Hello\n");
	printf("This is dup() test file\n");
	printf("Good bye !!\n");
	fprintf(stderr,"This is Eror Messae... \n");
	return;
}
