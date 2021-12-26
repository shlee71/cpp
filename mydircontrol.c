#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char cmdbuf[256];
	char pathbuf[1024];
	
	if(argc!=2)
	{
		fprintf(stderr,"Usage:mydircontrol dirname\n");
		exit(1);
	}
	
	mkdir(argv[1],0755);
	strcpy(cmdbuf,"ls -l | grep ");
	strcat(cmdbuf,argv[1]);
	printf("%s\n",cmdbuf);
	system(cmdbuf);
	
	chdir(argv[1]);
	if(getcwd(pathbuf, 1023) == NULL)
	{
		perror("getcwd");
		exit(1);
	}
	printf("Current Direcotry :%s\n", pathbuf);
	chdir("..");
	rmdir(argv[1]);
	printf("%s\n",cmdbuf);
	system(cmdbuf);
	return 0;
}

