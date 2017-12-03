#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
int main(int argc,char **argv){
    int pid,n;
    pid = fork();
    if(pid<0){
        perror("fork() ");
	return 0;
    }
    else if(pid==0){
        printf("fork Child pid:%d,n=%d\n",getpid(),++n);
    	exit(0);
    }
    else{
		sleep(1);
        printf("fork Parents pid:%d,n=%d\n\n",getpid(),n);
    }

    pid = vfork();
    if(pid<0){
	perror("vfork() ");
	return 0;
    }
    else if(pid==0){
	printf("vfork Child pid:%d,n=%d\n",getpid(),++n);
    	exit(0);
    }
    else{
	printf("vfork Parents pid:%d,n=%d\n",getpid(),n);
    }
    return 0;
}
