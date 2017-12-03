#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
int main(int argc,char *argv[]){
	struct stat statBuf;
	char *ptr;
	for(int i=1;i<argc;++i){
		if(lstat(argv[i],&statBuf)<0){
			perror("lstat:");
		}
		if(S_ISREG(statBuf.st_mode)){
			ptr = "regular file\n";
		}
		else if(S_ISDIR(statBuf.st_mode)){
			ptr = "directory file\n";
		}
		else if(S_ISCHR(statBuf.st_mode)){
			ptr = "char device file\n";
		}
		else if(S_ISBLK(statBuf.st_mode)){
			ptr = "block device file\n";
		}
		else if(S_ISFIFO(statBuf.st_mode)){
			ptr = "FIFO file\n";
		}
		else if(S_ISLNK(statBuf.st_mode)){
			ptr = "link file\n";
		}
		else if(S_ISSOCK(statBuf.st_mode)){
			ptr = "socket file\n";
		}
		printf("%s is %s",argv[i],ptr);
		
		lstat(argv[i],&statBuf);
		if(statBuf.st_mode&S_IRUSR){
			printf("readable by owner\n");
			if(statBuf.st_mode&S_IWUSR){
				printf("writable by owner\n");
			}
			else if(statBuf.st_mode&S_IXUSR){
				printf("executable by owner\n");
			}
		}								                             
		else if(statBuf.st_mode&S_IWUSR){
			printf("writable by owner\n");
			if(statBuf.st_mode&S_IXUSR){
				printf("executable by owner\n");
			}
		}

		int nodeNum = statBuf.st_ino;
		int countNum = statBuf.st_nlink;
		int usrID = statBuf.st_uid,grpID = statBuf.st_gid;
		int size = statBuf.st_size;
		printf("%s's node is %d\n",argv[i],nodeNum);
		printf("%s's count is %d\n",argv[i],countNum);
		printf("%s's userID is %d\n",argv[i],usrID);
		printf("%s's groupID is %d\n",argv[i],grpID);
		printf("%s's size is %d\n",argv[i],size);				
		if(chmod(argv[i],S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | (statBuf.st_mode & ~S_IROTH))<0){
			printf("chmod error\n");
		}
		else{
			printf("chmod ok\n");
		}
	}
	return 0;
}
