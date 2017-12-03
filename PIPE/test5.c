#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<limits.h>
#include<stdlib.h>
#include<stdio.h>
int main(int argc,char *argv[]){
	int fd;
	fd=open("file",O_RDONLY | O_NONBLOCK);
	if(fd<0){
		perror("open");
		exit(-1);
	}
	write(fd,"hello world \n",13);
	close(fd);
	printf("write OK\n");
	return 0;
}
