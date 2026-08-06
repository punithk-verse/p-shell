#include<stdio.h>
#include<string.h>
#include "shell.h"
void shell_loop(){
  char input[100];
  while(1){
   printf("pshell>");
   fgets(input,sizeof(input),stdin);
   char *args[100];
   parse_command(input,args);
   execute_command(args);
   input[strcspn(input,"\n")]=0;
   if(strcmp(input,"exit")==0){
     printf("i know u will come again ");
     break; }
    execute_command(input);
  }
}
