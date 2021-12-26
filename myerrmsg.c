#include <stdio.h>

int main(void)
{
	int i;

	printf("sys_nerr = %d\n", sys_nerr);

	for(i =0; i< sys_nerr; i++)
		printf("%d %s\n", i, sys_errlist[i]);
	
	return 0;
}
