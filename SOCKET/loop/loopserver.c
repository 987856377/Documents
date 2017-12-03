#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define max_data_size 256
int main(int argc,char **argv){
	int sockfd,bytes;
	socklen_t lenth;
	char buff[max_data_size];
	struct sockaddr_in serv_addr,cli_addr;
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(atoi(argv[1]));
	bzero(&(serv_addr.sin_zero),8);

	if((sockfd = socket(AF_INET,SOCK_DGRAM,0))==-1){
		perror("sokcet");
		exit(-1);
	}
	printf("socket success\n");
	
	if(bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr))==-1){
		perror("bind");
		exit(-1);
	}
	printf("bind success\n");
	while(1){
		bzero(&buff,max_data_size);
		lenth = sizeof(struct sockaddr);
		bytes = recvfrom(sockfd,buff,max_data_size,0,(struct sockaddr*)&cli_addr,&lenth);

		if(bytes<0){
			perror("recieve from client");
			break;
		}
		else if(bytes>0){
			printf("client IP %s , port %d , message is : %s\n",inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port),buff);
		}
		else{
			printf("the other one closed,quit\n");
			break;
		}
			
	}
	close(sockfd);
	return 0;
}
