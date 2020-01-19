#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>

int main(int argc, char *argv[])
{
	uid_t c_uid;
	struct passwd *pw;

	if (argc != 2)
	{	fprintf(stderr, "Usage : mysetuid username\n");
		exit(1);
	}

	printf("Current Real UID = %d, Effective UID = %d\n",
		getuid(), geteuid());

	pw = getpwnam(argv[1]);

	if (setuid(pw->pw_uid) == -1)
	{	perror("setuid");
		exit(1);
	}

	printf("Current Real UID = %d, Effective UID = %d\n",
		getuid(), geteuid());

	return 0;
}
