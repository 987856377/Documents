#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
int main(int argc, char *argv[]){
	int fd[2];
	char str[13];
	if(pipe(fd)<0){
		perror("pipe");
		exit(-1);
	}	
	write(fd[1],"hello world",13);
	read(fd[0],str,sizeof(str));
	printf("str:%s\n",str);
	close(fd[1]);
	close(fd[0]);
	return 0;
}
