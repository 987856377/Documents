#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
int main(int argc,char **argv){
    int pid;
    pid = vfork();
    if(pid<0){
        perror("vfork()");
    }
    else if(pid==0){
        printf("Child pid:%d  Parent pid:%d\n",getpid(),getppid());  //orphan_p
	sleep(2);
        printf("Child pid:%d  Parent pid:%d\n",getpid(),getppid());
    }
    else{
        exit(0);
    }
    return 0;
}
