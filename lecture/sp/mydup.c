#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

main() {

  int fd;

  fd = open("/tmp/foo", O_CREAT|O_WRONLY|O_TRUNC, 0660);

  if( fd == -1 ) {
    perror("open"); 
    exit(1);
  }
  close(STDOUT_FILENO);

  /* If succeeds file desc 1 is "/tmp/foo" */
  if( dup(fd) != STDOUT_FILENO ) { 
    fprintf(stderr,"dup failed to return 1!\n");
    exit(1); 
  }
  /* Don't need fd any more */
  close(fd);

  /* stdout output goes to "/tmp/foo" */
  printf("Welcome to LINUX System & Network Programming !\n");
}
