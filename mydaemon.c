#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <time.h>

int main(void)
{
    pid_t pid;
    time_t tm;       

    if((pid=fork()) != 0)
        exit(0);

    setsid();
    chdir("/");

    // mydaemon process start
    syslog(LOG_INFO|LOG_DAEMON,"I am daemon process\n");
    for(;;) 
    {
        // loop
        sleep(5);
        time(&tm);
        syslog(LOG_INFO|LOG_DAEMON,"shlee, I am still alive %s\n",ctime(&tm));
    }
    // mydaemon process end

    return 0;
}

