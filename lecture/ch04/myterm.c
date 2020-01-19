#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#define Control_A  '\01'

int main(int argc, char *argv[])
{
	struct termio tbuf, oldtbuf;
	char in, out, ch;

	if (ioctl(0, TCGETA, &tbuf) == -1)
	{ 	perror("ioctl");
		exit(1);
	}
	oldtbuf = tbuf;

	tbuf.c_lflag &= ~ICANON;
	tbuf.c_cc[VMIN] = 1;
	tbuf.c_cc[VTIME] = 0;
	if (ioctl(0, TCSETAF, &tbuf) == -1)
	{	perror("ioctl");
		exit(1);
	}

	while(1)
	{
		ch = getchar();
		if (ch == Control_A)
			break;
		printf("%x ", ch);
	}

	if (ioctl(0, TCSETAF, &oldtbuf) == -1)
	{	perror("ioctl");
		exit(1);
	}
	return 0;
}
