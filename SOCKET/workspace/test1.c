#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define max_data_size 512
#define port 3333
int reg_num = 0;
int link_num = 0;
int sub_dir = 0;
int depth = 0;
int sub_dir_reg = 0;
int sub_dir_lnk = 0;
char buff[max_data_size];
void sub_Dir(char *path,int sockfd){
        DIR *dir;
        struct dirent *dirBuf;
        struct stat statBuf;
        if((dir = opendir(path))==NULL){
                perror("opendir ");
        }
        chdir(path);
        while((dirBuf = readdir(dir))!=NULL){
                lstat(dirBuf->d_name,&statBuf);
                if(S_ISDIR(statBuf.st_mode)){
                        if(strcmp(dirBuf->d_name,".")==0 || strcmp("..",dirBuf->d_name)==0){
                                continue;
                        }
                        printf("directory name :%s inode :%d\n",dirBuf->d_name,(int)dirBuf->d_ino);
                        sub_Dir(dirBuf->d_name,sockfd);
                }
                else if(S_ISREG(statBuf.st_mode)){
                        reg_num++;
			sub_dir_reg++;
                        printf("file: %s, size: %ld\n",dirBuf->d_name,statBuf.st_size);
			
			bzero(&buff,max_data_size);
			sprintf(buff,"file: %s, size: %ld\n",dirBuf->d_name,statBuf.st_size);
			send(sockfd,buff,sizeof(buff),0);
                }
                else if(S_ISLNK(statBuf.st_mode)){
        	        sub_dir_lnk++;
			link_num++;

                        bzero(&buff,max_data_size);
                        sprintf(buff,"link file: %s, size: %ld\n",dirBuf->d_name,statBuf.st_size);
                        send(sockfd,buff,sizeof(buff),0);

                }

        }
        chdir("..");
        closedir(dir);		
	depth+1;
}
void openDir(char *path,int sockfd){
        DIR *dir;
        struct dirent *dirBuf;
        struct stat statBuf;
	int i=0;
        if((dir = opendir(path))==NULL){
                perror("opendir ");
        }
        chdir(path);
        while((dirBuf = readdir(dir))!=NULL){
                lstat(dirBuf->d_name,&statBuf);
                if(S_ISDIR(statBuf.st_mode)){	
                        if(strcmp(dirBuf->d_name,".")==0 || strcmp("..",dirBuf->d_name)==0){
                                continue;
                        }
                        printf("directory name :%s inode :%d\n",dirBuf->d_name,(int)dirBuf->d_ino);
			sub_dir++; 
			sub_Dir(dirBuf->d_name,sockfd);
			
                        bzero(&buff,max_data_size);
                        sprintf(buff,"%d th directory: %s, depth: %d, regular file count: %d, link file count: %d\n",++i,dirBuf->d_name,depth,sub_dir_reg,sub_dir_lnk);
                        send(sockfd,buff,sizeof(buff),0);

			depth=0;
			sub_dir_reg=0;
			sub_dir_lnk=0;
                	printf("%d th directory count complete! ! !\n",i);
		}
                else if(S_ISREG(statBuf.st_mode)){
			reg_num++;
                        printf("file: %s, size: %ld\n",dirBuf->d_name,statBuf.st_size);

                        bzero(&buff,max_data_size);
                        sprintf(buff,"file: %s, size: %ld",dirBuf->d_name,statBuf.st_size);
                        send(sockfd,buff,sizeof(buff),0);
                }
		else if(S_ISLNK(statBuf.st_mode)){
			link_num++;
		}
		
        }
        closedir(dir);
}
int main(int argc,char **argv){
	int sockfd,bytes;
	socklen_t lenth;
	struct sockaddr_in serv_addr;

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(port);
	bzero(&(serv_addr.sin_zero),8);
	
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket");
		exit(-1);
	}
	printf("socket success\n");

	if((connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr)))==-1){
		perror("connect");
		exit(-1);
	}
	printf("connect success\n");

	struct stat statBuff;
	if(lstat(argv[1],&statBuff)==-1){
		perror("stat");
		exit(-1);
	}
	if(S_ISREG(statBuff.st_mode)){
		printf("regular file,size: %ld bytes\n",statBuff.st_size);	
		sprintf(buff,"regular file,size: %ld bytes\n",statBuff.st_size);	
		bytes = send(sockfd,buff,sizeof(buff),0);
		if(bytes<0){
			printf("send to server error\n");
			exit(-1);
		}
		printf("send OK\n");
	}
	else if(S_ISDIR(statBuff.st_mode)){
		openDir(argv[1],sockfd);
		buff[max_data_size]='\0';
		sprintf(buff,"in this directory total regular file count is: %d,link file count is: %d\n",reg_num,link_num);
		send(sockfd,buff,sizeof(buff),0);
	}
	close(sockfd);
	return 0;
}
