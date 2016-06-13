#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int maxfd(int fds[], int size){
    int i,m=-1;
    for(i=0;i<size;++i){
        if(fds[i]>m) m=fds[i];
    }
    return m;
}

int main(int argc, char * argv[])
{ 
    int in1 = open("in1", O_RDONLY|O_NONBLOCK);
    printf("in1=%d\n",in1);
    int in2 = open("in2", O_RDONLY|O_NONBLOCK);
    printf("in2=%d\n",in2);
    int in[]={in1,in2};
    int size = sizeof(in)/sizeof(int);
    int i, c, sum = 0;
    char buf[10];
    struct timeval timeout;
    int k=10,j=-3;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    fd_set active_fd_set, read_fd_set;
    FD_ZERO(&active_fd_set);
    FD_SET(in[0], &active_fd_set);   
    FD_SET(in[1], &active_fd_set);
    while(k > 0){
        k--;
        printf("maxfd: %d\n",maxfd(in,size));
        read_fd_set = active_fd_set;
        if((j=select(maxfd(in,size), &read_fd_set, NULL, NULL, &timeout)) < 0){
            perror("select");
            exit(-1);
        }
        printf("select compelte %d\n",j);
        for(i=0; i<size; ++i){
            if(FD_ISSET(in[i], &read_fd_set))
            {
                printf("read from fd %d\n",in[i]);
                if((read(in[i],buf,10)) == 0){
                    printf("close %d\n",in[i]);
                    close(in[i]);
                    FD_CLR(in[i], &active_fd_set);
                    in[i]=-1;
                }else{
                    printf("%s\n",buf[0]);
                    sum += buf[0]-'0';
                }
            }
        }
    }
    printf("%d\n", sum);
    return 0;
}
