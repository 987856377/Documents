#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define backlog 10
#define max_data_size 256
int main(int argc,char **argv){
	int sockfd,clientfd;
	socklen_t lenth;
	char buff[max_data_size];
	struct sockaddr_in serv_addr,cli_addr;
	int flag;
	int bytes;

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(atoi(argv[1]));
	bzero(&(serv_addr.sin_zero),8);
	
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket");
		exit(-1);
	}
	printf("socket OK\n");
	if((bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)))==-1){
		perror("bind");
		exit(-1);
	}
	printf("bind OK\n");
	if((listen(sockfd,backlog))==-1){
		perror("listen");
		exit(-1);
	}
	printf("listen OK\n");
	
/*	if((flag=fcntl(sockfd,F_GETFL))==-1){
		perror("fcntl F_SETFL");
	}	
	flag |=O_NONBLOCK;
	if(fcntl(sockfd,F_SETFL,flag)<0){
		perror("fcntl");
	}
*/	
	while(1){
		lenth=sizeof(struct sockaddr);
		if((clientfd = accept(sockfd,(struct sockaddr*)&cli_addr,&lenth))==-1){
			perror("accept");
			exit(-1);
		}
		if((bytes=recv(clientfd,buff,max_data_size,0))==-1){
			perror("recieve");
			exit(-1);
		}
		if(read(clientfd,buff,max_data_size)<0){
			perror("read");
			exit(-1);
		}
		printf("recieve from client message is %s\n",buff);
		close(clientfd);
		exit(1);
	}

	return 0;
}
