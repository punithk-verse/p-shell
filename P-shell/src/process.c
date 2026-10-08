#include<stdio.h>
#include "process.h"
int get_process_info(pid_t pid,process_info *info){
    char path[64];
    snprintf(path,sizeof(path),"/proc/%d/stat",pid);
    FILE *file = fopen(path,"r");
    if(file==NULL){
        return -1;
    }
    if(fscanf(file,"%d (%*[^)]) %c %d",
       &info->pid,&info->state,
       &info->ppid)!=3){
        fclose(file);
        return -1;
       }
       fclose(file);
       return 0;
}
