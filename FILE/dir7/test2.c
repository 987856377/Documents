#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
int main(int argc,char **argv){
	int fd,chg,umsk;
	fd = open("file1",O_RDWR | O_CREAT,0666);
	if(fd<0){
		perror("open file1");
	}
	chg = chmod("file1",0644);
	if(chg<0){
		printf("chmod error\n");
	}
	else{
		printf("chmod OK\n");
	}
	char *cwd = (char*)malloc(56*sizeof(char));
	cwd = getcwd(cwd,56);
	printf("pwd:%s\n",cwd);
	free(cwd);
	cwd = NULL;
	close(fd);
	return 0;
}
