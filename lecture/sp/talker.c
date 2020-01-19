/********   talker.c  ********/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

main() {

  int pd, n;
  char msg[128];

  printf(">> Please Input the string.\n");

  /* open the pipe for write */
  pd = open("myfifo", O_WRONLY);
  if( pd == -1) {
    perror("open");
    exit(1);
  }

  while ((n=read(0, msg, sizeof(msg))) > 0)
   		write(pd, msg, n);

  close(pd);
}
