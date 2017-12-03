#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<limits.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#define BUFSZ PIPE_BUF
int main(int argc,char**argv){
	int fd;
	char str[13];
	fd = open("file",O_RDONLY | O_NONBLOCK);
	if(fd<0){
		printf("open error\n");
		exit(-1);
	}
	read(fd,str,13);
	printf("str: %s\n",str);
	close(fd);
	return 0;
}
