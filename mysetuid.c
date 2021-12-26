#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

int main(void)
{
	uid_t c_uid;
	struct passwd *pw;
	
	if(argc != 2) {
		fprintf(stderr,"Ussge:mysetuid username\n");
		exit(1);
	}
	
	printf("Current Real UID = %d, Effective UID = %d\n", getuid(), geteuid());
	pw= getpwnam(argv[1]);
	if(setuid(pw->uid) == -1) {
		perror("setuid");
		exit(1);
	}
	
	printf("Current Real UID = %d, Effective UID = %d\n", getuid(), geteuid());
	
	return 0;
}