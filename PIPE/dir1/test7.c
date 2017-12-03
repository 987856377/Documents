#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<limits.h>
#include<wait.h>
int main(){
    int fd1[2],fd2[2];
    int fk;
    int ret_pid,status;
    char send[] = "hello child";
    char response[] = "hello father";
    char child_recieve[15],father_recieve[15];
    if(pipe(fd1)<0){
        perror("pipe(fd1)");
        exit(EXIT_FAILURE);
    }
    if(pipe(fd2)<0){
        perror("pipe(fd2)");
        exit(EXIT_FAILURE);
    }
    fk = fork();
    if(fk<0){
        perror("fork()");
        exit(EXIT_FAILURE);
    }
    else if(fk>0){
        close(fd1[0]);
        write(fd1[1],send,13);
        close(fd1[1]);
        sleep(1);
        
        close(fd2[1]);
        read(fd2[0],father_recieve,15);
        close(fd2[0]);
        printf("father recieve OK,info: %s\n",father_recieve);
        ret_pid = wait(&status);
        printf("child exit status: %d, child pid: %d\n",status,ret_pid);
        exit(0);
    }
    else{
        close(fd1[1]);
        read(fd1[0],child_recieve,15);
        printf("child recieve OK,info: %s\n",child_recieve);
        close(fd1[0]);
        
        close(fd2[0]);
        write(fd2[1],response,15);
        close(fd2[1]);
        exit(0);
    }


    return 0;
}
