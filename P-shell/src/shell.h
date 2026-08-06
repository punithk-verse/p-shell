#ifndef SHELL_H
#define SHELL_H
void shell_loop();
void parse_command(char *input,char **args);
void builtin_command(char **args);
void execute_command(char **args);
#endif
