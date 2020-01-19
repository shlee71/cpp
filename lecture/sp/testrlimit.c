/*** testrlimit.c  ***/

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {

  struct rlimit myrlim;

  getrlimit(RLIMIT_NOFILE, &myrlim);
  printf("I can only open %d[%d] files\n", 
		myrlim.rlim_cur, myrlim.rlim_max);

  myrlim.rlim_cur = 256;

  if (setrlimit(RLIMIT_NOFILE, &myrlim) == -1) {
    perror("setrlimit");
    exit(1);
  }

  getrlimit(RLIMIT_NOFILE, &myrlim);
  printf("I can now open %d files\n", myrlim.rlim_cur);
  printf("sysconf() says %d files.\n", 
      sysconf(_SC_OPEN_MAX));
}
