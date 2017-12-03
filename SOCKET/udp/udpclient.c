#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<netdb.h>
#define max_data_size 256
int main(int argc,char **argv){
	int sockfd;
	char buff[max_data_size];
	int retn;
	socklen_t lenth;
	struct sockaddr_in serv_addr,cli_addr;
	
	cli_addr.sin_family = AF_INET;
	cli_addr.sin_addr.s_addr = inet_addr(argv[1]);
	cli_addr.sin_port = htons(atoi(argv[2]));
	bzero(&(cli_addr.sin_zero),8);

	if((sockfd = socket(AF_INET,SOCK_DGRAM,0))==-1){
		perror("socket");
		exit(-1);
	}
	printf("socket OK\n");
	strcpy(buff,"hello WORLD this is FRANK");
	retn = sendto(sockfd,buff,strlen(buff)+1,0,(struct sockaddr*)&cli_addr,sizeof(cli_addr));
	printf("retn number is %d\n",retn);
	if(retn==-1){
		perror("send failure");
		exit(-1);
	}
	lenth = sizeof(serv_addr);	
	retn = recvfrom(sockfd,buff,max_data_size,0,(struct sockaddr*)&serv_addr,&lenth);
	if(retn==-1){
		perror("recieve failure");
		exit(-1);
	}
	
	printf("the server response msg is %s\n",buff);
	close(sockfd);
	return 0;
}
