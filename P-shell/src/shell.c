#include<stdio.h>
#include<string.h>
#include "shell.h"
void shell_loop(){
  char input[100];
  while(1){
   printf("pshell>");
   fgets(input,sizeof(input),stdin);
   input[strcspn(input,"\n")]='\0';
   char *args[100];
   parse_command(input,args);
  //  for(int i=0;args[i]!=NULL;i++)
  //  {
  //   printf("args[%d]=%s\n",i,args[i]);
  //  }
   
   if(strcmp(args[0],"exit")==0){
     printf("i know u will come again \n");
     break; 
    }
    if(strcmp(args[0],"cd")==0)
    {
      builtin_command(args);
    }
    else
    {
      execute_command(args);
    }
  }
}
