#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#define BUFSZ 2048
int main(){
    int fk;
	int i=0;
    int shmid,tmp_mid;
    char *shm_write;
    char *shm_read;
    key_t key;
    key = ftok("file1",43);
    if((shmid=shmget(key,BUFSZ,IPC_CREAT | 0666))==-1){
        perror("shmget:");
        exit(-1);
    }
    else{
        printf("shmget OK\n");
    }

    if((shm_write=shmat(shmid,0,0))==(void*)-1){ // the second parameter if=0 address select by system or use the specific address by user
        perror("shmat write:");
        exit(-1);
    }
    else{
        printf("parent shmat OK\n");
    }

    char *write1 = "hello world";
    char *write2 = "end";
    
	if((fk=fork())==-1){
        perror("fork fk:");
        exit(-1);
    }
    else if(fk==0){
		sleep(1);
        tmp_mid = shmget(key,BUFSZ,IPC_CREAT | 0666);
        if((shm_read=shmat(tmp_mid,0,0))==(void*)-1){
            perror("shmat read:");
            exit(-1);
        }
        while(strcmp(shm_read,"end")!=0){
			printf("read%d: %s\n",i,shm_read);
			sleep(2);
        }
		sleep(1);
        if((shmdt(shm_read))==-1){
            perror("shmdt:");
            exit(-1);
        }
        else{
            printf("child process detached\n");
            exit(0);
        }
    }
    else{
		i=0;
		while(i<2){
			sprintf(shm_write,"%s",write1);
			printf("write%d: %s\n",i,shm_write);
			++i;
			sleep(2);
		}
		sprintf(shm_write,"%s",write2);
        printf("%s\n",shm_write);
		sleep(3);
		if((shmdt(shm_write))==-1){
            perror("parent process detached error:\n");
        }
        else{
            printf("parent process been detached\n");
        }
    }
    return 0;
}
