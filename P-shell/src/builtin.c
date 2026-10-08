#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include<string.h>
#include <sys/wait.h>
#include "shell.h"
#include "process.h"
pid_t zombie_pid=-1;
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
    if(zombie_pid==-1){
        printf("[process] no zombie is currently tracked\n");
        return 1;
    }

    if(get_process_info(zombie_pid,&info)==-1)
    {
        printf("[process] PID %d no loner exists\n",zombie_pid);
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
if(strcmp(args[0],":zombie")==0)
{
    pid_t pid = fork();

    if(pid == -1)
    {
        perror("fork");
        return 1;
    }

    if(pid == 0)
    {
        printf("[zombie] child PID %d exiting\n",getpid());
        fflush(stdout);
        exit(0);
    }
    zombie_pid=pid;
    printf("[zombie] created child PID %d\n",pid);
    printf("[zombie] parent is NOT waiting...\n");
    sleep(5);
    return 1;
}
    if(strcmp(args[0],":zombie")==0)
{
    pid_t pid = fork();

    if(pid == -1)
    {
        perror("fork");
        return 1;
    }

    if(pid == 0)
    {
        printf("[zombie] child PID %d exiting\n",getpid());
        fflush(stdout);
        exit(0);
    }

    zombie_pid = pid;

    printf("[zombie] created child PID %d\n",pid);
    printf("[zombie] parent is NOT waiting...\n");

    sleep(5);

    printf("[zombie] checking child...\n");

    return 1;
}
if(strcmp(args[0],":reap")==0)
{
    if(zombie_pid == -1)
    {
        printf("[reap] no zombie to reap\n");
        return 1;
    }

    if(waitpid(zombie_pid,NULL,0)==-1)
    {
        perror("waitpid");
        return 1;
    }

    printf("[reap] collected child PID %d\n",zombie_pid);

    zombie_pid = -1;

    return 1;
    }
return 0;
}
