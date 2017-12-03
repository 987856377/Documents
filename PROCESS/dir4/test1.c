#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
int main(int argc,char **argv){
    int pid,status;
    int ret_pid;
    pid = vfork();
    if(pid<0){
        perror("vfork()");
    }
    else if(pid==0){
        printf("Child pid:%d\n",getpid());
        exit(0);
    }
    else{
	sleep(1);
        ret_pid = wait(&status);
	printf("Parent pid:%d;\nStatus:%d;\nChild return pid:%d;\n",getpid(),status,ret_pid);
	if(WIFEXITED(status)){
	    	printf("wait on pid:%d,  normal exit,return value is:%d\n",ret_pid,WEXITSTATUS(status));
	}
	else if(WIFSIGNALED(status)){
	    	printf("wait on pid:%d,  recieve signal,return value is:%d\n",ret_pid,WIFSIGNALED(status));
	}
    }
    return 0;
}
