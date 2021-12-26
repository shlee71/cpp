#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char cmd_buf[256+1];

    if(argc != 2)
    {
        fprintf(stderr ,"usage : mysystem filename\n");
        return(1);
    }

    memcpy(cmd_buf,"ls -al ", sizeof("ll -al "));
    strncat(cmd_buf, argv[0], sizeof(argv[0]));

    system(cmd_buf);

    memset(cmd_buf, 0x00, sizeof(cmd_buf));
    memcpy(cmd_buf,"ps -l", sizeof("ps -l"));

    system(cmd_buf);

    return 0;
}
