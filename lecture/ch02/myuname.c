#include <sys/utsname.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	struct utsname mysystem;
	char myhostname[256];

	if (gethostname(myhostname, 255) != 0)
	{	perror("gethostname");
		exit(1);
	}
	printf("gethostname = %s\n", myhostname);

	if (uname(&mysystem) == -1)
	{	perror("uname");
		exit(1);
	}
	printf("OS 종류 = %s\n", mysystem.sysname);
	printf("hostname = %s\n", mysystem.nodename);
	printf("release = %s\n", mysystem.release);
	printf("version = %s\n", mysystem.version);
	printf("hardware = %s\n", mysystem.machine);
	
	return 0;
}
