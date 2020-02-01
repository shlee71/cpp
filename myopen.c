#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	int fd;

	if(argc != 2){
		fprintf(stderr,"Usage: myopen filename\n");
		exit(1);
	}
	if((fd= open(argv[1],O_RDONLY)) == -1)
	{
		perror("open1");
		fprintf(stderr,"File Read Fail....\n");
	}
	else
	{
		printf("File open Success[%s] ,fd=[%d] \n",argv[1],fd);
		system("ls -la");
		close(fd);
	}

	if((fd=open("MYDATA",O_WRONLY|O_CREAT,0666)) == -1)
	{
		perror("open2");
		fprintf(stderr,"File Open Fail...\n");
		exit(1);
	}
	else
	{
		printf("File Creat Success !!! fd=%d\n", fd);
		close(fd);
	}

	return 0;
}

