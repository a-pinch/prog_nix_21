#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

int main(int c, char **v){
    int opchar = 0, opindex = 0;
    struct option opts[] = {
        {"query", required_argument, NULL, 'q'},
        {"longinformationrequest", no_argument, NULL, 'i'},
        {"version", no_argument, NULL, 'v'},
        {0,0,0,0},
    };
    while( -1 != (opchar = getopt_long(c, v, "q:iv", opts, &opindex))){
        switch( opchar ){
            case 'q':
            case 'i':
            case 'v':
                break;
            default:
                printf("-");
                return 0;    
        }
    }
    printf("+");
    return 0;
}
