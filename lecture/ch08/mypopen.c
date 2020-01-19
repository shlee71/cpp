#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE *fp;
	int m;

	if ((fp=popen("grep 'Hello'", "w")) == NULL )
	{	fprintf(stderr, "popen failed.\n");
		exit(1);
	}

	for (m=1; m<=10; m++)
	{	fprintf(fp, "Hello, pipe!!\n");
		fprintf(fp, "Goodbye, pipe ...\n");
	}

	pclose(fp);
	return(0);
}
