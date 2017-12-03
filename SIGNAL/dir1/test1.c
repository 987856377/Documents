#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<stdio.h>
#include<signal.h>
#include<wait.h>
void sig_usr(int sig){
    if(sig==SIGUSR1){
        printf("recieve SIGUSR1\n");
    }
    else{
        printf("Undeclared signal %d\n",sig);
    }
}
int main(){
    int fk;
    int pid,status;
    int ret_val;
    fk = fork();
    pid = getpid();
    if(fk<0){
        perror("fork() ");
        exit(EXIT_FAILURE);
    }

    else if(fk==0){
        ret_val = kill(getppid(),SIGUSR1);
        if(ret_val==0){
            printf("send OK\n");
        }
        else{
            printf("send Error\n");
        }
        exit(EXIT_SUCCESS);
    }
    else{
        signal(SIGUSR1,sig_usr);
        sleep(2);
    }

    return 0;
}
