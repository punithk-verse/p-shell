#include<stdio.h>
#include<unistd.h>
#include "shell.h"

int trace_enabled=0;

void trace_fork(pid_t parent_pid,pid_t child_pid){
    if(trace_enabled){
        fprintf(stderr,
            "[fork] parent=%d created child=%d\n",
            parent_pid,child_pid);
    }
}

void trace_pipe(int read_fd,int write_fd){
    if(trace_enabled){
        fprintf(stderr,
            "[pipe] created\n"
            "       read end  = fd %d\n"
            "       write end = fd %d\n",
            read_fd,write_fd);
    }
}

void trace_dup2(int old_fd,int new_fd){
    if(trace_enabled){
        if(new_fd == STDIN_FILENO){
            fprintf(stderr,
                "[stdin]  fd %d -> stdin (fd 0)\n",
                old_fd);
        }
        else if(new_fd == STDOUT_FILENO){
            fprintf(stderr,
                "[stdout] fd %d -> stdout (fd 1)\n",
                old_fd);
        }
        else{
            fprintf(stderr,
                "[dup2] fd %d -> fd %d\n",
                old_fd,new_fd);
        }
    }
}
void trace_stdout_pipe(const char *command, int fd){
    if(trace_enabled){
        fprintf(stderr,
            "[stdout] %s -> pipe\n"
            "         fd %d -> stdout (fd 1)\n",
            command,fd);
    }
}

void trace_stdin_pipe(const char *command, int fd){
    if(trace_enabled){
        fprintf(stderr,
            "[stdin]  %s <- pipe\n"
            "         fd %d -> stdin (fd 0)\n",
            command,fd);
    }
}

void trace_stdout_file(const char *command, const char *filename, int fd){
    if(trace_enabled){
        fprintf(stderr,
            "[stdout] %s -> %s\n"
            "         fd %d -> stdout (fd 1)\n",
            command,filename,fd);
    }
}

void trace_exec(pid_t child_pid,const char *command){
    if(trace_enabled){
        fprintf(stderr,
            "[exec] child=%d -> running \"%s\"\n",
            child_pid,command);
    }
}