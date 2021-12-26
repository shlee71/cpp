#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int num;
	char num_char[10+1];
    printf("main() called\n");
	
	memset(num_char, 0x00, sizeof(num_char));
	memcpy(num_char, argv[1], sizeof(num_char));
	num = atoi(num_char);        
	
	printf("input caller number ==> [%d]\n",num);
    myshared(num);
    printf("main() end\n");
    return 0;
}
