#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int checkppid(char* chpid, char* chppid){
    char path[40];
    FILE* stat;
    int ppid;
    snprintf(path, 40, "/proc/%s/stat", chpid);
    stat = fopen(path, "r");
    if(!stat) return 0;
    fscanf(stat, "%*d %*s %*c %d", &ppid);
    fclose(stat);
    return strtol(chppid,(char **)NULL,10) == ppid;
}

int descendanscount(char* pid){
    DIR *d;
    struct dirent *entry;
    int c=1;
    d = opendir("/proc");
    while(entry = readdir(d)){
        if(isdigit(*entry->d_name))
            if(checkppid(entry->d_name, pid)) c+=descendanscount(entry->d_name);
    }
    closedir(d);
    return c;
}



int main(int argc, char * argv[])
{
    if(argc > 1)
        printf("%d\n",descendanscount(argv[1]));
    return 0;
}
