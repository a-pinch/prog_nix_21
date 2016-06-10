#include <stdio.h>
#define BUF_SIZE 0x100
int main(int argc, char * argv[])
{ char buf[BUF_SIZE];
    int len, i;
    int ppid;
    char dummy;
    FILE * f;
    f = fopen("/proc/self/stat", "r");
    fscanf(f, "%s %s %s %d", &dummy, &dummy, &dummy, &ppid); 
    fclose(f);
    printf("%d\n", ppid);
    return 0;
}
