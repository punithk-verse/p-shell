#include<stdio.h>
#include<string.h>
#include "shell.h"
void shell_loop(){
  char input[100];
  while(true){
   printf("pshell>");
   fgets(input,sizeof(input),stdin);
   input[strcspn(input,"\n")]=0;
   if(strcmp(input,"exit")==0){
     printf("i know u will come again ");
     break; }
    execute_command(input);
  }
}
