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
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));
	bzero(&(serv_addr.sin_zero),8);
	
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket");
		exit(-1);
	}
	printf("socket OK\n");
	if((connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr)))==-1){
		perror("connect");
		exit(-1);
	}
	printf("connect Ok\n");
	
	strcpy(buff,"hello");
	bytes = send(sockfd,buff,sizeof(buff),0);
	if(bytes<0){
		perror("send to server");
		exit(-1);
	}
	else{
		printf("send to server seccess\n");
	}
	close(sockfd);
	return 0;
}
