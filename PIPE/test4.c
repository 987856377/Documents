#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
int main(int argc,char *argv[]){
	if(argc!=2){
		printf("parameter not right\n");
		exit(-1);
	}	
	if((mkfifo(argv[1],0666 | O_NONBLOCK))<0){
		perror("mkfifo");
		exit(-1);
	}
	else{
		printf("Mkfifo successful :%s\n",argv[1]);
	}
	return 0;
}










































