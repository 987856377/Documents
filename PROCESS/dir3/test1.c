#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
void cpexit(void){
    printf("Child process exited!\n");
    printf("Child pid:%d,Parent pid:%d\n",getpid(),getppid());
	int fk;
	if((fk=fork())<0){
		perror("fork in child:");
		exit(-1);
	}
	else if(fk==0){
		
		char *env;
		setenv("user","root",1);
		env=getenv("user");
        printf("before: %s\n",env);
		setenv("user","zhangsan",1);
   		env = getenv("user");
		printf("later: %s\n",env);	
		exit(0);
	}else{
		sleep(1);
	}
}
int main(){
    int pid;
    pid = vfork();
    if(pid<0){
        perror("vfork()");
    }
    else if(pid==0){
        if(execl("/home/localhost/Documents/FILE/dir6/test1","./test1",NULL)<0){
	    	perror("execl");
		}
		exit(0);
    }
    else{
		sleep(1);
		atexit(cpexit);
		sleep(1);
    }
    return 0;
}
