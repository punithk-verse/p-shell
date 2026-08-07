
#include<stdio.h>
#include<unistd.h>
#include<string.h>

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
    return 0;
}