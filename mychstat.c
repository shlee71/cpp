#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
    struct stat fstatbuf;

    system("touch data;ls -l data");
    stat("data",&fstatbuf);
    printf("\nchmode()\n");

    chmod("data",fstatbuf.st_mode|S_IXUSR|S_IXGRP);
    system("ls -l data");
    link("data","data1");
    symlink("data","data2");
    printf("\nnlink() & symlink()\n");
    system("ls -li data data1 data2");
    return 0;
}
