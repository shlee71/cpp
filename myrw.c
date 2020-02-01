#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	char buf[1024];
	int fd1,fd2,n;

	if(argc !=3){
		fprintf(stderr,"Usage : myrw filename1 filename2 \n");
		exit(1);
	}

	if((fd1 =open(argv[1],O_RDONLY)) == -1)
	{
		perror("open1");
		exit(1);
	}
	if((fd2 =open(argv[1],O_WRONLY)) == -1)
	{
		perror("open2");
		exit(1);
	}

	while((n=read(fd1, buf,sizeof(buf))) > 0)
	{
		printf(buf);
		putchar('\n');
		write(fd2, buf, n);
	}
	 
	close(fd1); 
	close(fd2);
	return 0;
}
