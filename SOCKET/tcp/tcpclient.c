#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<errno.h>
#include<netdb.h>
#define port 3333
#define max_data_size 256
int main(int argc,char **argv){
	int sockfd,bytes;
	char buff[max_data_size];
	struct sockaddr_in serv_addr;
	pid_t pid;
	struct hostent *host;
			
	if(argc<3){
		fprintf(stderr,"enter server ip and port\n");
		exit(-1);
	}
	/*
	if((host=gethostbyname(argv[1]))==NULL){
		perror("host name");
		exit(-1);
	}	
	*/	
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket");
		exit(-1);
	}
	printf("socket OK\n");	
	bzero(&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]); 
	serv_addr.sin_port = htons(atoi(argv[2]));
	bzero(&(serv_addr.sin_zero),8);

	// INADDR_ANY recieve from any network card 	
	// inet_addr("127.0.0.1"); recieve from specific network card 
	if((connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)))==-1){
		perror("connect");
		exit(-1);
	}
	
	printf("connect OK\n");

	if((pid=fork())==-1){
		perror("fork");
		exit(-1);
	}
        else if(pid==0){
                while(1){
                        bzero(&(buff),max_data_size);
                        bytes = recv(sockfd,buff,max_data_size,0);
                        if(bytes<0){
                                perror("recieve from server");
                                break;
                        }
                        else if(bytes>0){
                                printf("client: %s",buff);
                        }
			else{
				printf("the server maybe have closed\n");
				break;
			}
                }
		exit(0);
        }
        else{
                while(1){
                        bzero(&(buff),max_data_size);
                        printf("client('quit' to exit):");
                        fgets(buff,max_data_size,stdin);
                        if(!strncasecmp(buff,"quit",4)){
                                printf("closing the connection. . .\n");
                            	kill(pid,SIGKILL);
			        break;
                        }
                        bytes = send(sockfd,buff,sizeof(buff),0);
                        if(bytes<0){
                                perror("send to server");
                                break;
                        }
                }
		close(sockfd);
        }

	close(sockfd);
	return 0;
}
