#include<sys/wait.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
void test(void){
	int pid;
	pid = vfork();
	if(pid<0){
		perror("vfork()");
		exit(EXIT_FAILURE);
	}
	else if(pid==0){
		printf("1:  Child pid:%d,Parent pid:%d\n",getpid(),getppid());
		return;
	}
	else{
		
		printf("2:  Child pid:%d,Parent pid:%d\n",getpid(),getppid());
	}
}

void fun(void){
	int buf[100];
	memset(buf,'\0',100);
	printf("3:  Child pid:%d,Parent pid:%d\n",getpid(),getppid());
}

int main(){
	test();    // parent process shared stack with child process, the stack space is cleared when child process have been exited ;

	fun();	   // run fun(), cover previous stack space
	
	// when child process exit, parent process continue run at where vfork() return, but the stack space not exited, result Stack Error 
	return 0;    

}
