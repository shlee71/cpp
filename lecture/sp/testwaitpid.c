/*** testwaitpid.c  ***/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

main()
{
  pid_t  pid;
  int    status;

  pid = fork();
  if (pid < 0)
  {  perror("fork");
      exit(1);
  }

  if (pid == 0)       /* child process */
  {     execlp("who", "who", (char *)NULL);  /* abort() */
        perror("execlp");
        exit(1);
  }
  
  if (waitpid(pid, &status, WUNTRACED) == -1) 
  {    perror("waitpid");
        exit(1);
  }

   if (WIFSIGNALED(status)) 
        printf("Child Process terminated by signal %d.\n", 
							WTERMSIG(status));
   else 
        if (WIFEXITED(status)) 
             printf("Child Process exited with status %d.\n",
							WEXITSTATUS(status));
       else 
             if (WIFSTOPPED(status)) 
                 printf("Child Process stopped by signal %d.\n",
							WSTOPSIG(status));
  
  return 0;
}


