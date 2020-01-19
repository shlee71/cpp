#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	struct stat fstatbuf;
	char filename[30];

	if (argc != 2)
	{	fprintf(stderr, "Usage : mystat filename\n");
		exit(1);
	}

	if (stat(argv[1], &fstatbuf) == -1)
	{ 	if (errno == ENOENT)
			fprintf(stderr, "%s is not found\n", argv[1]);
		else if (errno == EACCES)
				fprintf(stderr, "No permission for %s\n", argv[1]);
        perror("argv[1]");
		exit(1);
	}

	if (S_ISDIR(fstatbuf.st_mode))
		printf("%s is Derectory\n", argv[1]);
	else if (S_ISREG(fstatbuf.st_mode))
		printf("%s is Regular File\n", argv[1]);
	else if (S_ISCHR(fstatbuf.st_mode))
		printf("%s is Character Devie file\n", argv[1]);
	else if (S_ISBLK(fstatbuf.st_mode))
		printf("%s is Block Device File\n", argv[1]);
	
	printf("Permission:");
	if (fstatbuf.st_mode & S_IRUSR) putchar('r');
    else putchar('-');
	if (fstatbuf.st_mode & S_IWUSR) putchar('w');
    else putchar('-');
	if (fstatbuf.st_mode & S_IXUSR) putchar('x');
	else putchar('-');

	putchar('\n');

	printf("inode = %d, uid = %d, size =%d\n",
			fstatbuf.st_ino, fstatbuf.st_uid, fstatbuf.st_size);
	return 0;
}

