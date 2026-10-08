#ifndef SHELL_H
#define SHELL_H
#include<sys/types.h>
extern int trace_enabled;
void shell_loop();
void trace_fork(pid_t parent_pid,pid_t chid_pid);
void trace_pipe(int read_fd,int write_fd);
void trace_dup2(int old_fd,int new_fd);
void trace_exec(pid_t child_pid,const char *command);
void parse_command(char *input,char **args);
int builtin_command(char **args);
void execute_command(char **args);
void trace_stdout_pipe(const char *command, int fd);
void trace_stdin_pipe(const char *command, int fd);
void trace_stdout_file(const char *command, const char *filename, int fd);
#endif
