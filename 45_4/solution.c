#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
int getppid(char* pid){
    char path[80];
    int ppid;
    FILE * f;
    sprintf(path, "/proc/%s/stat", pid);
    f = fopen(path, "r");
    if(f){
        fscanf(f, "%*d %*s %*c %d", &ppid); 
        fclose(f);
        return ppid;
    }
    else {
        return -1;
    }
}

int main(int argc, char * argv[]){
    if(argc > 1){
        char *pid = argv[1];
        int ppid;
        while((ppid=getppid(pid))>1){
            printf("%s\n",pid);
            sprintf(pid, "%d", ppid);
        }
        if(ppid==1) printf("%d\n",ppid);
    }
        
    return 0;
}

