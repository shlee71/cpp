#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    DIR *dirp;
    struct dirent *dirent;
    struct stat fstat;

    if( argc != 2 )
    {
        fprintf(stderr,"Usage:mydir directoryname\n");
        exit(1);
    }
    
    stat(argv[1], &fstat);
    if(!S_ISDIR(fstat.st_mode))
    {
        fprintf(stderr,"%s is nor Directory\n",argv[1]);
        exit(1);
    }

    if((dirp=opendir(argv[1])) == NULL)
    {
        perror("opendir");
        exit(1);
    }

    while((dirent=readdir(dirp)) !=NULL)
    {
        printf("inode=%ld, filename=%s\n", dirent->d_ino, dirent->d_name);
    }

    closedir(dirp);
    return 0;
}

