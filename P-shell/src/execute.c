#include<stdio.h>
#include<unistd.h>
#include<sys/types.h> //this gives special data types used by Os
#include<sys/wait.h> //ethis give fun for controlling process 
#include<string.h>
#include<stdlib.h>
#include "shell.h"

void execute_command(char **args)
{
  int pipe_index=-1;
  for(int i=0;args[i]!=NULL;i++){
   if(strcmp(args[i],"|")==0)
   {
      pipe_index = i;
      break;
   }
  }
  if(pipe_index==-1){
   pid_t pid=fork();

  if(pid==0){
   execvp(args[0],args);
   perror("execvp");
   exit(1);
  }
  else if(pid>0){
   wait(NULL);
  }
  else{
   perror("fork");
  }
  return;
}
 args[pipe_index]=NULL;
 char **command1 = args;
 char **command2 = &args[pipe_index+1];
  int fd[2];
  if(pipe(fd)==-1)
  {
   perror("pipe");
   return;
  }
  trace_pipe(fd[0],fd[1]);
  pid_t pid1 = fork();
  if(pid1>0){
   trace_fork(getpid(),pid1);
  }
 if (pid1==0){
   close(fd[0]);
   if(dup2(fd[1],STDOUT_FILENO)==-1){
      perror("dup2");
      exit(1);
   }
   trace_dup2(fd[1],STDOUT_FILENO);
   close(fd[1]);
   trace_exec(getpid(),command1[0]);
   execvp(command1[0],command1);
   perror("execvp");
   exit(1);
 }
   pid_t pid2 =fork();
   if(pid2>0){
      trace_fork(getpid(),pid2);
   }
   if(pid2==0){
      close(fd[1]);
      if(dup2(fd[0],STDIN_FILENO)==-1){
         perror("dup2");
         exit(1);
      }
      trace_dup2(fd[0],STDIN_FILENO);
      close(fd[0]);
   trace_exec(getpid(),command2[0]);
   execvp(command2[0],command2);
   perror("execvp");
   exit(1);
   }
   close(fd[0]);
   close(fd[1]);
   waitpid(pid1,NULL,0);
   waitpid(pid2,NULL,0);
}
