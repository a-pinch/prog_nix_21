#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

struct sockaddr_in local;

int main(int c, char **v){
    if(c!=2)
        return -1;

    int s = socket (AF_INET, SOCK_DGRAM, 0);
    inet_aton("127.0.0.1",&local.sin_addr);
    int p;
    sscanf(v[1], "%d", &p);
    local.sin_port = htons(p);
    local.sin_family = AF_INET;

    bind(s, (struct sockaddr*) &local, sizeof(local));
    
    char buf[BUFSIZ];
    int n;
    while(1){
        n = read(s, buf, BUFSIZ);
        if(!strncmp(buf, "OFF",n-1)) return 0;
        printf("%.*s\n", n, buf);
    }
}
