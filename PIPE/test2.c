#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#define BUFSZ 256		
int main(int argc,char *argv[]){
	int fd[2];
	int pid;
	char buf[BUFSZ];
	if(pipe(fd)<0){
		perror("pipe");
		exit(-1);
	}	
	if((pid=fork())<0){
		perror("fork");
		exit(-1);
	}
	else if(pid>0){
		printf("Parent process\n");
		close(fd[0]);
		write(fd[1],"Father write to Pipe",BUFSZ);
		close(fd[1]);
		exit(0);
	}
	else{
		printf("Child process\n");
		close(fd[1]);
		read(fd[0],buf,sizeof(buf));
		printf("buf: %s",buf);
		close(fd[0]);
		exit(0);
	}

	return 0;
}
