#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
int getppid(char* chpid){
    char path[80];
    int pid, ppid, tgid;
    FILE * f;
    sprintf(path, "/proc/%s/stat", chpid);
    f = fopen(path, "r");
    if(f){
        fscanf(f, "%d %*s %*c %d %d", &pid, &ppid, &tgid); 
        fclose(f);
        return tgid != pid ? tgid : ppid;
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

