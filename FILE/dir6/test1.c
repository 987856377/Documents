#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<dirent.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
void openDir(char *path){
	DIR *dir;
	struct dirent *dirBuf;
	struct stat statBuf;
	if((dir = opendir(path))==NULL){
		perror("opendir ");
	}
	chdir(path);
	while((dirBuf = readdir(dir))!=NULL){
		lstat(dirBuf->d_name,&statBuf);
		if(S_IFDIR & statBuf.st_mode){
			if(strcmp(dirBuf->d_name,".")==0 || strcmp("..",dirBuf->d_name)==0){
				continue;
			}
			printf("directory name :%s inode :%d\n",dirBuf->d_name,(int)dirBuf->d_ino);
			openDir(dirBuf->d_name);
		}
		else{
			printf("file %s\n",dirBuf->d_name);
		}
	}
	chdir("..");
	closedir(dir);
}
int main(){
	char *path = "/home";
	openDir(path);
	return 0;
}
