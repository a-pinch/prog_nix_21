#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sig_handler(int signo){
    if(signo == SIGURG)
       exit(0);
}

int main(int argc, char * argv[])
{ 
    pid_t pid = 0;
    pid_t sid =0;
    pid = fork();
    if(pid < 0){
        printf("fork failed!\n");
        exit(1);
    }
    if(pid > 0){
        printf("%d\n",pid);
        exit(0);
    }
    sid = setsid();
    if(sid < 0){
        printf("session failed");
        exit(1);
    }
    chdir("/");
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    signal(SIGURG, sig_handler);
    while(1){
        sleep(1000);
    }
    return 0;
}
