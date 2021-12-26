#include <stdio.h>
#include <syslog.h>

int main(void)
{
    FILE *fp;

    if((fp=fopen("noexist", "r")) == NULL)
    {
        syslog(LOG_ERR|LOG_USER,"mysyslog - %m\n");
        perror("fopen");
        exit(1);
    }

    fclose(fp);
    return(0);

}
