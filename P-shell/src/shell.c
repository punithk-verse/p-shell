#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include "shell.h"
void shell_loop(){
  char input[100];
  while(1){
  char cwd[1024];
  if(getcwd(cwd,sizeof(cwd))!=NULL)
   {
    printf("%s > ", cwd);
    }
  else
    {
    printf("pshell> ");
    }
   fgets(input,sizeof(input),stdin);
   input[strcspn(input,"\n")]='\0';
   char *args[100];
   parse_command(input,args);
      if (args[0] == NULL)
          {
          continue;
          }
   
   if(strcmp(args[0],"exit")==0){
     printf("i know u will come again \n");
     break; 
    }
    if(!builtin_command(args))
    {
      execute_command(args);
    }
  }
}
