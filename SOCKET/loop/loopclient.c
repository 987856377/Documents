#include<sys/types.h>
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
#define max_data_size 256
int main(int argc,char **argv){
	int sockfd,bytes;
	socklen_t lenth;
	char buff[max_data_size];
	struct sockaddr_in serv_addr,cli_addr;

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));
	bzero(&(serv_addr.sin_zero),8);

	if((sockfd = socket(AF_INET,SOCK_DGRAM,0))==-1){
		perror("socket");
		exit(-1);
	}
	printf("socket success\n");
/*	
	if(bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr))==-1){
		perror("bind");
		exit(-1);
	}
	printf("bind success\n");
*/
	while(1){
		bzero(&buff,max_data_size);
		lenth = sizeof(struct sockaddr);
		printf("send to server('quit' to exit):");
		fgets(buff,max_data_size,stdin);
		if(!strncasecmp(buff,"quit",4)){
			perror("quit");
			break;
		}
		bytes = sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&serv_addr,lenth);
		if(bytes<0){
			perror("send to server");
			break;
		}
		else{
			printf("send to server OK\n");
		}
	}
	close(sockfd);
	return 0;
}
