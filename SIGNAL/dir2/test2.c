#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
int main(){
    int fk;
    int qid;
    int lenth;
    char msg[256] = "hello world";
    lenth = strlen(msg);
    key_t key;
    key = ftok("file2",30);
    if((qid=msgget(key,IPC_CREAT | 0666))==-1){
        perror("parent msgget:");
        exit(-1);
    }
    printf("parent msgget OK\n");
    if((msgsnd(qid,&msg,lenth,IPC_NOWAIT))==-1){
        perror("parent msgsnd:");
        exit(-1);
    }else{
        printf("parent send OK\n");
    }

    if((fk = fork())==-1){
        perror("fork:");
        exit(-1);
    }
    else if(fk==0){
        int len;
		if(( qid = msgget(key,IPC_CREAT | 0666))==-1){
            perror("child msgget:");
            exit(-1);
        }
        else{
            printf("child msgget OK\n");
        }
        len = msgrcv(qid,&msg,4096,0,IPC_NOWAIT);
        if(len>0){
            printf("massage is: %s\n",msg);
        }
        else if(len==0){
            printf("no massage\n");
        }
        else{
            perror("child msgrcv:");
            exit(-1);
        }
    }
    else{
        system("ipcs -q");
        exit(0);
    }
    return 0;
}
