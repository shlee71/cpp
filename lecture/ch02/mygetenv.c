#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
 	char *mydir, filename[80];
	FILE *fp;

	mydir=getenv("HOME");
	strcpy(filename, mydir);
	strcat(filename, "/sample.dat");

	if ((fp=fopen(filename, "w")) == NULL)
	{
		perror("fopen");
		exit(1);
	}

	fwrite("getenv test\n", 12, 1, fp);
	fclose(fp);

	return 0;
}
