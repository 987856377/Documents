#include<sys/types.h>
#include<sys/socket.h>
#include<sys/signal.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<wait.h>
#include<fcntl.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#define backlog 10
#define max_data_size 256
int main(int argc,char **argv){
	int sockfd,clientfd;
	int bytes;
	pid_t ppid,pid;
	socklen_t lenth;
	FILE *fp;
 	time_t time_now;
	char buff[max_data_size];
	struct sockaddr_in serv_addr,cli_addr;
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(atoi(argv[1]));
	bzero(&(serv_addr.sin_zero),8);

	if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1){	
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

	while(1){
		lenth = sizeof(struct sockaddr);
		if((clientfd = accept(sockfd,(struct sockaddr*)&cli_addr,&lenth))==-1){
			perror("accept");
			exit(-1);
		}
		printf("there is a client attached\n");

		if((fp=fopen("log.txt","a+"))==NULL){
			perror("open file");
			exit(-1);
		}
		bzero(&buff,max_data_size);
 		time(&time_now);

		sprintf(buff,"client IP %s, Port %d, Time %s",inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port),ctime(&time_now));
		fputs(buff,fp);

		if((ppid=fork())==-1){
			perror("fork");
			exit(-1);
		}
		else if(ppid==0){
			pid = fork();
			while(1){
				if(pid==-1){
					perror("fork");
					exit(-1);
				}
				else if(pid==0){
		        	        bzero(&buff,max_data_size);
        			        bytes = recv(clientfd,buff,max_data_size,0);
        			        if(bytes<0){
        			                perror("recv from client");
						exit(0);
              				}
	        		        else if(bytes>0){
        				        printf("client IP %s , Port %d , message is: %s\n",inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port),buff);         
                			}
                			else{
	        				printf("\nthe other one client closed\n");
						exit(0);
       	         			}
				}
				else{
                	               	bzero(&buff,max_data_size);
					int status;
					if(pid==waitpid(pid,&status,1)){
						printf("session exit\n");
						exit(0);
					}
                	               	printf("\nserver('quit' to exit): ");
                	               	fgets(buff,max_data_size,stdin);
                	               	if(!strncasecmp(buff,"quit",4)){
                	               	        perror("quit");
						kill(pid,SIGKILL);
                                
				                bzero(&buff,max_data_size);
                                                sprintf(buff,"the session closed\n");
                                                send(clientfd,buff,sizeof(buff),0);

						close(clientfd);
						exit(0);				
               	                	}
                                	bytes = send(clientfd,buff,sizeof(buff),0);
               	                	if(bytes<0){
                    	 			perror("send to client");
						exit(-1);
       	                        	}
				}
			}
		}
		else{
			sleep(1);
		}
	}	
	close(clientfd);
	close(sockfd);
	return 0;
}
