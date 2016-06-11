#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>

int checkname(char* pid, char* match){
    char path[40];
    FILE* comm;
    char name[100];
    snprintf(path, 40, "/proc/%s/comm", pid);
    comm = fopen(path, "r");
    if(!comm)
        return -1;
    fgets(name, 100, comm);
    fclose(comm);
    name[strcspn(name,"\n")] = '\0';
    return strcmp(name, match);
}



int main(int argc, char * argv[])
{ 
    struct dirent *entry;
    DIR *d;
    int c=0;
    d = opendir("/proc");
    while(entry = readdir(d)){
        if(isdigit(*entry->d_name))
            if(checkname(entry->d_name, "genenv") == 0) c++;
    }    
    printf("%d\n",c);
    closedir(d);
    return 0;
}
