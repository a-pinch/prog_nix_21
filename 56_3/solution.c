#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

int usr1=0,usr2=0;

void sig_handler(int signo)
{
    if (signo == SIGUSR1)
        usr1++;
    else if (signo == SIGUSR2)
        usr2++;
    else if (signo == SIGTERM){
       printf("%d %d\n", usr1, usr2);
       exit(0);
    }
}

int main(void)
{
    signal(SIGUSR1, sig_handler);
    signal(SIGUSR2, sig_handler);
    signal(SIGTERM, sig_handler);
    while(1) 
        sleep(1);
    return 0;
}
                    
