#include<sys/types.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<limits.h>
#include<fcntl.h>
#define BUFSZ PIPE_BUF
int main(int argc,char *argv[]){
	FILE *fp;
	char *cmd="ls -l";
	char buf[256];
	if((fp=popen(cmd,"r"))==NULL){
		perror("popen");
		exit(-1);
	}
	while(fgets(buf,BUFSZ,fp)!=NULL){
		printf("%s\n",buf);
	}
	pclose(fp);
	return 0;

}
