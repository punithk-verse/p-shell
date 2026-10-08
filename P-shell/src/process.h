#include<sys/types.h>
typedef struct {
    pid_t pid;
    pid_t ppid;
    char state;
}process_info;
int get_process_info(pid_t pid,process_info *info);
