#include<sys/types.h>
#include<sys/time.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<signal.h>
void _sigaction(int sig,siginfo_t *info,void *p){
    if(sig==SIGUSR1){
        printf("the signal is SIGUSR1\n");
    }
    printf("sender pid: %d\n",info->si_pid);
    printf("sender uid: %d\n",info->si_uid);
}
int main(){
    struct sigaction act,oldact;
    sigemptyset(&act.sa_mask);
    act.sa_sigaction = _sigaction;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1,&act,&oldact);
    int fk;
    if((fk=fork())<0){
        perror("fork ");
        exit(-1);
    }
    else if(fk==0){
        union sigval mysigval;
        if((sigqueue(getppid(),SIGUSR1,mysigval))==-1){
            printf("send Error\n");
        }
        else{
            printf("send OK\n");
        }
        exit(0);
    }
    else{
        sleep(2);
        printf("recieve OK\n");
    }

    return 0;
}
