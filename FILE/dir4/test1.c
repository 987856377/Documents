#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argv[]){
	umask(0);
	if(creat("testfile",S_IRUSR | S_IWUSR | S_IRGRP)<0){
		perror("create file:");
	}
	else{
		printf("create file OK\n\n");
	}
	struct stat statBuf;
       	if(link("testfile","testfile1")<0){
		perror("create link file error");
	}
	else{
		printf("create link file OK\n");
						    
	}
	lstat("testfile1",&statBuf);
	int inode1 = statBuf.st_ino;
	int size1 = statBuf.st_size;
	printf("link file's inode is %d\n",inode1);
	printf("link file's size is %d\n\n",size1);
	if(symlink("testfile","testfile2")<0){
		perror("create symlink file error");
	}
	else{
		printf("create symlink file OK\n");
	}
	lstat("testfile2",&statBuf);
	int inode2 = statBuf.st_ino;
	int size2 = statBuf.st_size;
	printf("symlink file's inode is %d\n",inode2);
	printf("symlink file's size is %d\n",size2);
	char buff[256];
	readlink("testfile2",buff,256);
	printf("file context is %s\n\n",buff);
	
	stat("testfile",&statBuf);
	int inode = statBuf.st_ino;
	int size = statBuf.st_size;
	int count = statBuf.st_nlink;
	printf("source file's inode is %d\n",inode);
	printf("source file's size is %d\n",size);
	printf("source file's link count is %d\n",count);	
	if(unlink("testfile")<0){                
		perror("unlink source file: ");
	}
	stat("testfile",&statBuf);
	int linkNum = statBuf.st_nlink;
	printf("after unlink source file,link number is:%d\n",linkNum);
	return 0;
}
