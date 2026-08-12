
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include "shell.h"
int builtin_command(char **args){
   if(strcmp(args[0], "cd") == 0)
    {
     if(args[1]==NULL)
       {
        printf("Usage : cd <directory>\n");  
       }
    else{
        if (chdir(args[1])!=0)
        {
            perror("chdir");
        }
    }
        return 1;
    }
    
    if(strcmp(args[0],":explain")==0){
        trace_enabled=!trace_enabled;
        if(trace_enabled){
            printf("explain mode:ON\n");
        }
        else{printf("Explain mode:OFF\n");
        }
    return 1;
    }
return 0;
}
