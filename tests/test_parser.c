#include<stdio.h>
#incude<string.h>
#include "../P-shell/src/shell.h"

int main(){
    int passed =0;
    int failed=0;
    {
        char input[]="ls -l /home";
        char *args[10];
        parse_command(input,args);
        if(strcmp(args[0], "ls") == 0 &&
           strcmp(args[1], "-l") == 0 &&
           strcmp(args[2], "/home") == 0 &&
           args[3] == NULL)
        {
            printf("PASS: Basic parsing\n");
            passed++;
        }
        else
        {
            printf("FAIL: Basic parsing\n");
            failed++;
        }
    }

    
    {
        char input[] = "ls    -l";
        char *args[10];

        parse_command(input, args);

        if(strcmp(args[0], "ls") == 0 &&
           strcmp(args[1], "-l") == 0 &&
           args[2] == NULL)
        {
            printf("PASS: Multiple spaces\n");
            passed++;
        }
        else
        {
            printf("FAIL: Multiple spaces\n");
            failed++;
        }
    }

    {
        char input[] = "";
        char *args[10];

        parse_command(input, args);

        if(args[0] == NULL)
        {
            printf("PASS: Empty input\n");
            passed++;
        }
        else
        {
            printf("FAIL: Empty input\n");
            failed++;
        }
    }

    printf("\nTest summary\n");
    printf("Passed: %d\n", passed);
    printf("Failed: %d\n", failed);

    return failed == 0 ? 0 : 1;
}
    