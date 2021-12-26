/****  mmap1.c  *****/
#include <sys/types.h>
#include <sys/mman.h> 
#include <sys/stat.h>
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

main(int argc, char *argv[]) {

  int fd;
  caddr_t addr;
  struct stat statbuf;

  if (argc != 2) {
    fprintf(stderr,"Usage: mmap1 filename\n");
    exit(1);
  }

  if (stat(argv[1], &statbuf) == -1) { 
    perror("stat"); 
    exit(1); 
  }

  fd = open(argv[1], O_RDONLY);
  if (fd == -1) { 
    perror("open"); 
    exit(1); 
  }

  addr = mmap((caddr_t)NULL, statbuf.st_size, PROT_READ, MAP_PRIVATE, fd, (off_t)0);
  if (addr == MAP_FAILED) { 
    perror("mmap");
    exit(1); 
  }

  /* no longer need fd */
  close(fd);

  write(STDOUT_FILENO, addr, statbuf.st_size);
  return(0);
}
