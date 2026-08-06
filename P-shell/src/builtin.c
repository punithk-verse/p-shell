
#include<stdio.h>
#include<unistd.h>
#include<string.h>

void builtin_command(char **args){
   
    if(args[1]==NULL)
    {
        printf("Usage : cd<directory>\n");
        return;
    }
    else{
        if (chdir(args[1])!=0)
        {
            perror("chdir");
        }
    }
}