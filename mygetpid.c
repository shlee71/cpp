#include <unistd.h>
#include <stdio.h>

int main(void)
{
    printf("PID  = %d\n",getpid());
    printf("PPID = %d\n",getppid());

    return 0;
}
