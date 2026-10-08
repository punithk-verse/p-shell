#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include "shell.h"
#include "process.h"
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

    if(strcmp(args[0],":process")==0)
{
    process_info info;

    if(get_process_info(getpid(),&info)==-1)
    {
        perror("get_process_info");
        return 1;
    }

    printf("[process]\n");
    printf("  PID   : %d\n",info.pid);
    printf("  PPID  : %d\n",info.ppid);
    const char *state_name;

if(info.state == 'R')
{
    state_name = "running";
}
else if(info.state == 'S')
{
    state_name = "sleeping";
}
else if(info.state == 'T')
{
    state_name = "stopped";
}
else if(info.state == 'Z')
{
    state_name = "zombie";
}
else
{
    state_name = "unknown";
}

printf("  State : %c (%s)\n",info.state,state_name);

    return 1;
}
return 0;
}
