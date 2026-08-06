#include<stdio.h>
#include<unistd.h>
#include<sys/types.h> //this gives special data types used by Os
#include<sys/wait.h> //ethis give fun for controlling process 
#include "shell.h"

void execute_command(char *command)
{
  pid_t pid = fork();
 if (pid==0){
   execlp(command,command,NULL);
   printf("COMMAND NOT FOUND !);
     }
  else if(pid>0)
     {
     wait(NULL);
     }
  else
     {
    printf("fork failed \n");
    }
}
