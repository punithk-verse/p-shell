#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include "shell.h"
void shell_loop(){
  char input[1024];
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
   if(fgets(input,sizeof(input),stdin)==NULL){
    break;
   }

   if (strchr(input, '\n') == NULL && !feof(stdin)) {
      int ch;

      while ((ch = getchar()) != '\n' && ch != EOF) {
        /* Discard the rest of this input line. */
      }

    fprintf(stderr, "pshell: input line too long (maximum 1023 characters)\n");
    continue;
   }

   input[strcspn(input,"\n")]='\0';
   char *args[100];
   if(parse_command(input,args)==-1){
    continue;
   }
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
