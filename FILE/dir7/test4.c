#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
int main(){
    int fd;
    FILE *fp;
    char str[13]; 
    
    /*
    fp = fopen("change","w+");
    if(fp==NULL){
        perror("open file:");
        exit(EXIT_FAILURE);
    }
    fd = fileno(fp);
    printf("fp 转化为文件描述符：%d\n",fd);
    write(fd,"hello world\n",13); 
    close(fd);
    */

    
    fd = open("change",O_RDWR);
    if(fd<0){
        perror("open:");
        exit(EXIT_FAILURE);
    }
    fp = fdopen(fd,"w");
    printf("转化成功\n");
    fgets(str,13,fp);
    printf("从文件中读到：%s\n",str);
    fclose(fp);
    

    return 0;
}
