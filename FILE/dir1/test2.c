#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
int main(){
	    int fd;
	    fd = open("file2",O_RDWR | O_CREAT,S_IRWXU);
	    if(fd < 0){
		    perror("open:");
		    printf("Write Error: %d",errno);
	    }
	    int writeNum;
	    char str2[] = "ABCDEFGHIJKLMN";
	    writeNum = write(fd,str2,14);
	    if(writeNum != 14){
		    perror("Write Error\n");
	    }
	    else{
		    printf("Write OK\n");
	    }
	    close(fd);
	    return 0;
}
