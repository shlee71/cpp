#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <sys/types.h>

int main(void)
{
	pid_t pid;

	if ((pid=fork()) !=0 )
		exit(0);
	setsid();
	chdir("/");

// 데몬 프로세스의 실지 처리 부분 구현
	syslog(LOG_INFO|LOG_DAEMON, "I am daemon process\n");

	for(;;)
		sleep(10);

	return 0;
}
