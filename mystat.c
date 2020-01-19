#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[])

{
    struct stat fstatbuf;
    char filename[30];

    if(argc != 2)
    {
        fprintf(stderr,"Usage:mystat filename\n");
        exit(1);
    }

    if(stat(argv[1],&fstatbuf) == -1){
        if(errno==ENOENT)
            fprintf(stderr,"%s is not found\n", argv[1]);
        else if(errno==EACCES)
            fprintf(stderr,"No permission for %s\n",argv[1]);
        exit(1);
    }

    if(S_ISDIR(fstatbuf.st_mode))
        printf("%s is Directory\n", argv[1]);
    else if(S_ISREG(fstatbuf.st_mode))
        printf("%s is Regular File\n",argv[1]);
    else if(S_ISBLK(fstatbuf.st_mode))
        printf("%s is Block Device File\n", argv[1]);
    else if(S_ISCHR(fstatbuf.st_mode))
        printf("%s is Character Device File\n", argv[1]);

    printf("Permission USR:");

    if(fstatbuf.st_mode & S_IRUSR)
        putchar('r');
    if(fstatbuf.st_mode & S_IWUSR)
        putchar('w');
    if(fstatbuf.st_mode & S_IXUSR)
        putchar('x');
    putchar('\n');

    printf("inode = %ld, uid = %d, size = %ld\n", fstatbuf.st_ino, fstatbuf.st_uid, fstatbuf.st_size);
 
    printf("Permission Check Befer Change USR GRP OTH:");

    if(fstatbuf.st_mode & S_IRUSR)
        putchar('r');
    else
        putchar('-');
    if(fstatbuf.st_mode & S_IWUSR)
        putchar('w');
    else
        putchar('-');
    if(fstatbuf.st_mode & S_IXUSR)
        putchar('x');
    else
        putchar('-');
    if(fstatbuf.st_mode & S_IRGRP)
        putchar('r');
    else
        putchar('-');
    if(fstatbuf.st_mode & S_IWGRP)
        putchar('w');
    else
        putchar('-');
    if(fstatbuf.st_mode & S_IXGRP)
        putchar('x');
    else
        putchar('-');
    if(fstatbuf.st_mode & S_IROTH)
        putchar('r');
    else
        putchar('-');
    if(fstatbuf.st_mode & S_IWOTH)
        putchar('w');
    else
        putchar('-');
    if(fstatbuf.st_mode & S_IXOTH)
        putchar('x');
    else
        putchar('-');

    putchar('\n');

    chmod(argv[1], S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH);
    stat(argv[1],&fstatbuf);   
    printf("Permission Check After Change USR GRP OTH:");

    if(fstatbuf.st_mode & S_IRUSR)
        putchar('r');
    else
        putchar('-');
    if(fstatbuf.st_mode & S_IWUSR)
        putchar('w');
    else
        putchar('-');
    if(fstatbuf.st_mode & S_IXUSR)
        putchar('x');
    else
        putchar('-');
    if(fstatbuf.st_mode & S_IRGRP)
        putchar('r');
    else
        putchar('-');
    if(fstatbuf.st_mode & S_IWGRP)
        putchar('w');
    else
        putchar('-');
    if(fstatbuf.st_mode & S_IXGRP)
        putchar('x');
    else
        putchar('-');
    if(fstatbuf.st_mode & S_IROTH)
        putchar('r');
    else
        putchar('-');
    if(fstatbuf.st_mode & S_IWOTH)
        putchar('w');
    else
        putchar('-');
    if(fstatbuf.st_mode & S_IXOTH)
        putchar('x');
    else
        putchar('-');
    putchar('\n');
   
    return 0;
}

