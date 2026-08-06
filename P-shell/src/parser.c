#include<stdio.h>
#include<string.h>
#include "shell.h"
 
void parse_command(char *input,char **args)
{
    int i=0;
    char *token = strtok(input," ");
    while(token!=NULL){
        args[i] = token;
        i++;
        token = strtok(NULL," ");
    }
    args[i]=NULL;
}