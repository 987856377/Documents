#include<stdio.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<signal.h>
#define backlog 10
#define max_conn_num 10
#define max_data_size 256
int main(int argc,char **argv){
	struct sockaddr_in serv_addr,cli_addr;
	int sockfd,clientfd;
	int bytes;
	socklen_t lenth;
	char buff[max_data_size];
	pid_t pid;

	bzero(&serv_addr,sizeof(serv_addr));	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(atoi(argv[1]));
	bzero(&(serv_addr.sin_zero),8);

	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket");
		exit(-1);
	}
	printf("socket success\n");

	if(bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr))==-1){
		perror("bind");
		exit(-1);
	}
	printf("bind success\n");

	if(listen(sockfd,backlog)==-1){
		perror("listen");
		exit(-1);
	}
	printf("listen success\n");

	lenth = sizeof(struct sockaddr);
	if((clientfd = accept(sockfd,(struct sockaddr*)&cli_addr,&lenth))==-1){
		perror("accept");
		exit(-1);
	}
	printf("accept success\n");
	printf("client IP is %s port is %d\n",inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port));	
	
	
	if((pid = fork())==-1){
		perror("fork");
		exit(-1);
	}
        else if(pid==0){
                while(1){
                        bzero(&(buff),max_data_size);
                        bytes = recv(clientfd,buff,max_data_size,0);
                        if(bytes<0){
                                perror("recieve from client");
                                break;
                        }
                        else if(bytes>0){
                                printf("client: %s",buff);
                        }
			else{
				printf("the client maybe have been closed");
				break;
			}
                }
		close(clientfd);
		exit(0);
        }
        else{
                while(1){
                        bzero(&(buff),max_data_size);
                        printf("server('quit' to exit):");
                        fgets(buff,max_data_size,stdin);
                        if(!strncasecmp(buff,"quit",4)){
                                printf("closing the connection. . . \n");
                               	kill(pid,SIGKILL);
				close(clientfd);
				break;
                        }
                        bytes = send(clientfd,buff,sizeof(buff),0);
                        if(bytes == -1){
                                perror("send to client");
                                break;
                        }
                }
        }
		
	close(sockfd);

	return 0;
}
