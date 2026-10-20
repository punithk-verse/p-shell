
#include <stdio.h>
#include <string.h>
#include "shell.h"

int parse_command(char *input, char **args)
{
    static char parsed[1024];
    char *read = input;
    char *write = parsed;
    int argc = 0;
    char quote = '\0';

    while (*read != '\0') {
        while (*read == ' ' || *read == '\t') {
            read++;
        }

        if (*read == '\0') {
            break;
        }

        if (argc >= 99) {
            fprintf(stderr, "pshell: too many arguments\n");
            args[0] = NULL;
            return -1;
        }

        args[argc++] = write;
        int started = 0;

        while (*read != '\0') {
            if (quote == '\0') {
                if (*read == ' ' || *read == '\t') {
                    break;
                }

                if (*read == '\'' || *read == '"') {
                    quote = *read++;
                    started = 1;
                    continue;
                }
            } else if (*read == quote) {
                quote = '\0';
                read++;
                started = 1;
                continue;
            }

            *write++ = *read++;
            started = 1;
        }

        if (quote != '\0') {
            fprintf(stderr, "pshell: unmatched quote\n");
            args[0] = NULL;
            return -1;
        }

        *write++ = '\0';

        (void)started;
    }

    args[argc] = NULL;
    return 0;
}
