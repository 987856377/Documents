#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
int main(){
	int fd;
	fd = open("file1",O_RDWR | O_CREAT,S_IRWXU);
	if(fd < 0){
		perror("open:");
		printf("errno is %d",errno);
	}
	int writeNum;
    	char str1[] = "abcdefghijklmn";
	writeNum = write(fd,str1,14);
	if(writeNum != 14){
     		perror("Write Error\n");
        }
	else{
	        printf("Write OK\n");
	}
	close(fd);
        return 0;
}
