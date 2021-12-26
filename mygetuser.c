#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    printf("UID = %d\n", getuid());
    printf("Name = %s\n", getlogin());
    return 0;
}
