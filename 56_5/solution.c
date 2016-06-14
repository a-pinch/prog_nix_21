#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSZ    1000

int main(int argc, char * argv[])
{ 
    if(argc != 3){
        perror("illigal arguments");
        exit(1);
    }

    int shmid, shmid1,shmid2;
    int *shm, *shm1, *shm2;
    int i;

    key_t key = ftok(argv[0], 1), key1, key2;
    if(key < 0){
        perror("ftok");
        exit(1);
    }
    sscanf(argv[1], "%d", &key1);
    sscanf(argv[2], "%d", &key2);
    
    if((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0){
        perror("shmget");
        exit(1);
    }
    if((shmid1 = shmget(key1, SHMSZ, 0666)) < 0){
        perror("shmget1");
        exit(1);
    }
    if((shmid2 = shmget(key2, SHMSZ, 0666)) < 0){
        perror("shmget2");
        exit(1);
    }

    if((shm = shmat(shmid, NULL, 0)) == (int *)-1){
        perror("shmat");
        exit(1);
    }
    if((shm1 = shmat(shmid1, NULL, 0)) == (int *)-1){
        perror("shmat1");
        exit(1);
    }
    if((shm2 = shmat(shmid2, NULL, 0)) == (int *)-1){
        perror("shmat2");
        exit(1);
    }

    for(i=0; i<100; ++i){
        shm[i] = shm1[i] + shm2[i];
    }

    printf("%d\n", key);
    return 0;
}
