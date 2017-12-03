#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
	int readfd;
	readfd = open("file1",O_RDONLY);
	if( readfd < 0 ){
		perror("open : ");
		printf("Write Error : %d",errno);
	}
	int readNum;
	char str3[14];
	readNum = read(readfd,str3,14);
	if( readNum != 14){
		printf("Read File1 Error\n");
	}
	else{
		printf("Read File1 OK\n");
	}
	int writefd,writeNum1,writeNum2;
	writefd = open("file2",O_RDWR);
	if( writefd < 0 ){
		perror("open:");
		printf("write Error: %d",errno);
	}
	char str4[14];
	writeNum2 = read(writefd,str4,14);
	if(writeNum2 != 14){
		printf("Read File2 Error\n");
	}
	else{
		printf("Read File2 OK\n");
	}

	lseek(writefd,0,SEEK_SET);
	writeNum1 = write(writefd,str3,14);
	if(writeNum1 != 14 ){
		printf("Write1 Error\n");
	}
	else{
		printf("Write1 OK\n");
	}
	lseek(writefd,0,SEEK_END);
	writeNum2 = write(writefd,str4,14);
	if(writeNum2 != 14){
		printf("Write2 Error\n");
	}
	else{
		printf("Write2 OK\n");
	}
	close(writefd);
	close(readfd);
	return 0;
}
