#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(void)
{
	struct stat fstatbuf;

	system("touch data; ls -l data");
	stat("data", &fstatbuf);
	printf("\nchmod()\n");
	chmod("data", fstatbuf.st_mode|S_IXUSR|S_IXGRP);
	system("ls -l data");

	link("data", "data1");
	symlink("data", "data2");
	printf("\nlink() & symlink\n");
	system("ls -li data data1 data2");
	return 0;
}
