#include <stdio.h>
int main()
{
	union {
		short s;
		unsigned char c[sizeof(short)];
	} un;
	
	un.s = 0x0102;
	if (un.c[0] == 1 && un.c[1] == 2)
		printf("big-endian\n");
	else if (un.c[0] == 2 && un.c[1] == 1)
		printf("little-endian\n");
	else
		printf("Unknown\n");
}
