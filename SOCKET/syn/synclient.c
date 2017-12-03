#include<sys/types.h>
#include<sys/socket.h>
#include<sys/signal.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#define max_data_size 256
int main(int argc,char **argv){
	int sockfd,clientfd;
	int bytes;
	pid_t pid;
	socklen_t lenth;
	char buff[max_data_size];
	struct sockaddr_in serv_addr,cli_addr;
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));
	bzero(&(serv_addr.sin_zero),8);

	if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1){	
		perror("socket");
		exit(-1);
	}
	printf("socket success\n");
	
	if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr))==-1){
		perror("connect");
		exit(-1);
	}
	printf("connect success\n");

	if((pid = fork())==-1){
		perror("fork");	
		exit(-1);
	}
	else if(pid==0){
		while(1){
			bzero(&buff,max_data_size);
	                printf("client('quit' to exit):");
        	        fgets(buff,max_data_size,stdin);
	                if(!strncasecmp(buff,"quit",4)){
        	                perror("client closing");
        	               	kill(getppid(),SIGKILL);
				break;
        	        }
                
                	bytes = send(sockfd,buff,sizeof(buff),0);
                	if(bytes<0){
                        	perror("send to server");
                        	break;
                	}
		}		
		close(sockfd);
		exit(0);
	}
	else{
		while(1){
                	bzero(&buff,max_data_size);
                	bytes = recv(sockfd,buff,max_data_size,0);
                	if(bytes<0){
                	        perror("recieve from server");
                	        break;
                	}
			else if(bytes>0){
                		printf("server: %s",buff);
			}
			else{
				printf("\nthe server maybe have been closed\n");
				close(sockfd);	
				break;
			}
		}
	}
	close(sockfd);
	return 0;
}
