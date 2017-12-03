#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
int main(){
	int pid,ret_pid,status,tmp;
	pid = vfork();
	if(pid<0){
		perror("vfork()");
	}
	else if(pid==0){
		tmp = getpid();
		printf("Child pid:%d,Parent pid:%d\n",getpid(),getppid());
		exit(0);	
	}

	else{
		//sleep(1);		// child process run greater, parent process sleep;
		
		printf("continue...\n");
		ret_pid = wait(&status);		//wait any child process exit, child process exit status return 0, return exit child pid;

		//ret_pid = waitpid(tmp,&status,WNOHANG);    //no child exit return 0, or return child pid;

		printf("return pid:%d,status:%d\n",ret_pid,status);
		
	}

	return 0;
}
