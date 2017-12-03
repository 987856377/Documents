#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
int main(){
    int pid;
    pid = vfork();
    if(pid<0){
        perror("vfork()");
    }
    else if(pid==0){
        printf("Child pid:%d  Parent pid:%d\n",getpid(),getppid());  //zoomb process (defunct)
        exit(0);
    }

    else{
        sleep(3);
	system("ps");
	exit(0);
    }
    return 0;
}
