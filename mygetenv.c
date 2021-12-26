#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	char *mydir, filename[80];
	FILE *fp;
	
	// change default home directory
	putenv("HOME=./");

	mydir = getenv("HOME");
	strcpy(filename,mydir);
	strcat(filename,"/sample.dat");

	if((fp = fopen(filename,"w")) == NULL )
	{
		perror("fopen:");
	}

	printf("mygetenv Normal end !!!\n");
	fwrite("getenv test\n",12,1,fp);

	fclose(fp);
}
