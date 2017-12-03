#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc,char *argv[]){
	if(mkdir("/home/user",666)<0){
		perror("mkdir ");
	}
	chdir("/home/user");
	char *path = (char*)malloc(256*sizeof(char));
	getcwd(path,256);
	printf("Path: %s\n",path);
	free(path);
	return 0;
}
