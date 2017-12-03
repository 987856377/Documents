#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#include<limits.h>
#include<wait.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
int main(int argc,char *argv[]){
    int fd;
    char str[13];
    if(argc!=2){
        printf("Please input a parameter\n");
        exit(EXIT_FAILURE);
    }
    if((mkfifo(argv[1],0666 | O_NONBLOCK))<0){
        printf("Mkfifo error\n");
        exit(EXIT_FAILURE);    
    }
    if((fd = open(argv[1],O_RDWR | O_NONBLOCK))<0){
        perror("open pipe file");
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<10;++i){
        if(write(fd,"hello world\n",13)<0){
            perror("write");
            exit(EXIT_FAILURE);
        }
    }
    lseek(fd,0,SEEK_SET);
    while((read(fd,str,13))>0){
        printf("read from Pipe file: %s",str);
    }
    close(fd);
    return 0;

}
