#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

int main(void)
{
	struct passwd *mypw;

	mypw = getpwuid(getuid());
	printf("name = %s, uid = %d, gid = %d, home directory = %s, shell = %s\n",
		mypw->pw_name, mypw->pw_uid, mypw->pw_gid, mypw->pw_dir, mypw->pw_shell);

	mypw = getpwnam("root");
	printf("name = %s, uid = %d, gid = %d, home directory = %s, shell = %s\n",
		mypw->pw_name, mypw->pw_uid, mypw->pw_gid, mypw->pw_dir, mypw->pw_shell);

	return 0;
}
