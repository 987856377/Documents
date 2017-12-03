#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<fcntl.h>
#define max_data_size 256

void my_fun(char *trans){

	if(trans==NULL){
		return;
	}
	for(;*trans!='\0';trans++){
		if(*trans>='A'&&*trans<='Z'){
			*trans = *trans-'A'+'a';
		}
	}

}

int main(int argc,char **argv){
	int sockfd,recvbytes;
	socklen_t lenth;
	struct sockaddr_in serv_addr,cli_addr;
	char buff[max_data_size];
	char address[max_data_size];	
	int retn;
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(atoi(argv[1]));
	bzero(&(serv_addr.sin_zero),8);
	
	if(argc!=2){
		perror("enter the port");
		exit(-1);
	}	

	if((sockfd = socket(AF_INET,SOCK_DGRAM,0))==-1){
		perror("socket");
		exit(-1);
	}
	printf("socket OK\n");
	if(bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr))==-1){
		perror("bind");
		exit(-1);
	}
	printf("bind OK\n");
	
	printf("begin while\n");
	while(1){
		lenth = sizeof(struct sockaddr);
		printf("begin recieve. . .\n");
		retn = recvfrom(sockfd,buff,max_data_size,0,(struct sockaddr*)&cli_addr,&lenth);
		printf("retn number is %d\n",retn);
		if(retn==-1){
			perror("recieve failure");
			exit(-1);	
		}
		//inet_ntop(AF_INET,&cli_addr.sin_addr,addr_p,sizeof(addr_p));
		printf("client IP is %s , port is %d\n",inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port));
		printf("content is %s\n",buff);
		my_fun(buff);
		retn = sendto(sockfd,buff,strlen(buff)+1,0,(struct sockaddr*)&cli_addr,lenth);
		if(retn==-1){
			perror("send failure\n");
			exit(-1);
		}
		printf("send to udp client OK\n");
	}	

	close(sockfd);
	return 0;
}
