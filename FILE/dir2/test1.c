#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
	int fd;
	fd = open("file4",O_RDWR | O_CREAT,S_IRWXU);
	if(fd < 0 ){
		perror("open:");
		printf("Open Error:%d",errno);
	}
	int fdcopy,t;
	t= dup2(fd,fdcopy);
	
	//int fdcp1,fdcp2;
	//dup2(fd,fdcp1);
	//fdcp2 = fcntl(fd,F_DUPFD,0);
	if(t==-1){
		printf("dup Copy Error\n");
	}
	else{
		printf("dup Copy OK\n");
	}
	int writeNum;
	char str3[11] = "class_name";
	writeNum = write(fdcopy,str3,11);
	if(writeNum != 11){
		printf("Write File Error\n");
	}
	else{
		printf("Write File OK\n");
	}

	lseek(fdcopy,0,SEEK_SET);
	int readNum;
	char str4[11];
	readNum = read(fd,str4,11);
	if(readNum != 11){
		printf("Read File Error\n");
	}
	else{
		printf("Read Fiel OK: %s\n",str4);
	}    
	return 0;
}
