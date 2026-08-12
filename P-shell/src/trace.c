#include<stdio.h>
#include "shell.h"
int trace_enabled=0;
void trace_fork(pid_t parent_pid,pid_t child_pid){
    if(trace_enabled){
    printf("[fork] parent=%d --> child %d\n",parent_pid,child_pid);
      }
}
void trace_pipe(int read_fd,int write_fd){
    if(trace_enabled){
        printf("[pipe] read_fd=%d write_fd=%d\n",read_fd,write_fd);
    }
}
void trace_dup2(int old_fd,int new_fd){
    if(trace_enabled)
    {
        fprintf(stderr,"[dup2] fd %d -->fd %d \n",old_fd,new_fd);
    }
}



