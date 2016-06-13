#include <stdio.h>

int main(int argc, char * argv[])
{ 
    if(argc > 2){
        char *command;
        sprintf(command, "%s %s",argv[1],argv[2]);
        FILE *f = popen(command, "r");
        int c, count = 0;
        while((c=fgetc(f)) != EOF){
            if(c == '0') count++;
        }
        pclose(f);
        printf("%d\n", count);
    }
    return 0;
}
