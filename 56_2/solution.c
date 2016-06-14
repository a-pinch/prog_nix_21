#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

int maxfd(int fds[], int size){
    int i,m=-1;
    for(i=0;i<size;++i){
        if(fds[i]>m) m=fds[i];
    }
    return m+1;
}

int main(int argc, char * argv[])
{ 
    int in[]={
        open("in1", O_RDONLY|O_NONBLOCK),
        open("in2", O_RDONLY|O_NONBLOCK)
    };
    int size = sizeof(in)/sizeof(int);
    int i, c, sum = 0;
    char buf[1];
    fd_set active_fd_set, read_fd_set;
    FD_ZERO(&active_fd_set);
    for(i=0;i<size;++i)
        FD_SET(in[i], &active_fd_set);   
    while(maxfd(in,size) > 0){
        read_fd_set = active_fd_set;
        if((select(maxfd(in,size), &read_fd_set, NULL, NULL, NULL)) < 0){
            perror("select");
            exit(-1);
        }
        for(i=0; i<size; ++i){
            if(FD_ISSET(in[i], &read_fd_set))
            {
                if((read(in[i],buf,1)) == 0){
                    close(in[i]);
                    FD_CLR(in[i], &active_fd_set);
                    in[i]=-1;
                }else{
                    if(isdigit(buf[0]))
                        sum += buf[0]-'0';
                }
            }
        }
    }
    printf("%d\n", sum);
    return 0;
}
