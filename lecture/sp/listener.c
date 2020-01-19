/*****  listener.c *****/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFSIZE 80

main() {

  int pd, n = 0;
  char inmsg[BUFSIZE];
  char* introMessage = ">> Listener heard\n"; 

  /* open the pipe for read */
  pd = open("myfifo", O_RDONLY);
  if(pd == -1) {
    perror("open");
    exit(1);
  }

  write(1, introMessage, strlen(introMessage));

  while( (n = read(pd, inmsg, BUFSIZE ) ) > 0 ) 
		write(1, inmsg, n );

  close(pd);
}
