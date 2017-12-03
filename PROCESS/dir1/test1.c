#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char **argv){
    int pid;
    int status;
    pid=vfork();
    if(pid<0){
	perror("fork()");
	return 0;
    }
    else if(pid==0){
	char *str1 = "Software Design 3 - Xu Zhenkui - 1615925215";
	FILE *fp;
	if((fp=fopen("file1","w+"))==NULL){
	    perror("open file1");
	}
	chmod("file1",0644);
	fputs(str1,fp);
	fclose(fp);
	exit(0);
    }
    else{
	FILE *fp1;
	if((fp1=fopen("file1","r+"))==NULL){
	    perror("open file1");
	}
	char *str2 = (char*)malloc(43*sizeof(char));
	fgets(str2,43,fp1);
	pid = wait(&status);
	puts(str2);
	printf("Child pid %d,Status %d\n",pid,status);
	fclose(fp1);
    }

    return 0;
}
