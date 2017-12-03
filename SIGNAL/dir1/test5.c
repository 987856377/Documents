#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<sys/time.h>
#include<signal.h>
#include<unistd.h>
void _sigaction(int sig,siginfo_t *info,void *p){
    if(sig==SIGUSR1){
        printf("the signal is: SIGUSR1\n");
    }
    printf("the value is: %d\n",info->si_value.sival_int);
}
int main(int argc,char *argv[]){
    struct sigaction act,oldact;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = _sigaction;
    sigaction(SIGUSR1,&act,&oldact);
    int fk;
    if((fk=fork())<0){
        perror("fork ");
        exit(-1);
    }
    else if(fk==0){
        union sigval mysigval;
        mysigval.sival_int = 20;
        if(sigqueue(getppid(),SIGUSR1,mysigval)==-1){
            printf("send Error\n");
        }
        else{
            printf("send OK\n");
        }
    
    }
    else{
        sleep(2);
        printf("recieve OK\n");
        exit(0);
    }

    return 0;
}
