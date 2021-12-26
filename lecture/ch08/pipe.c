#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

main()
{
	int pd[2], n;
	char buf[100];

	pipe(pd);

	if (fork() > 0)	/* Parent */
	{
		close(pd[0]); /* close read */

		while(n=read(0,buf, sizeof(buf)) > 0)
			write(pd[1],  buf, n);

		close(pd[1]);
	}
	else
	{
		close(pd[1]);

		while(n=read(pd[0],buf, sizeof(buf)) > 0)
		{
			write(1, "[CHILD]", 7);
			write(1, buf, n);
		}
		close(pd[0]);
	}
}
		
