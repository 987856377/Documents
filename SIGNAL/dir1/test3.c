#include<sys/types.h>
#include<stdlib.h>
#include<fcntl.h>
#include<stdio.h>
#include<signal.h>
#include<sys/time.h>
#include<unistd.h>
#include<errno.h>
void _sigaction(int sig,siginfo_t *info,void *p)
{
    if(sig==SIGUSR1){
        printf("recieve SIGUSR1\n");
    }
    else{
        printf("error SIGNAL\n");
    
    }
    
}
int main(){
    struct sigaction act,oldact;
    act.sa_sigaction = _sigaction;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1,&act,&oldact);
    int fk;
    if((fk=fork())<0){
        perror("fork() ");
        exit(-1);
    }
    else if(fk==0){
        union sigval mysigval;        
        if(sigqueue(getppid(),SIGUSR1,mysigval)==-1){
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
