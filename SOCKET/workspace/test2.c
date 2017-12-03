#include<sys/types.h> 
#include<sys/stat.h>
#include<dirent.h>
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
#define backlog 10
#define port 3333
#define max_data_size 512
int main(int argc,char **argv){
        struct sockaddr_in serv_addr,cli_addr;
        int sockfd,clientfd;
        int bytes;
        socklen_t lenth;
        char buff[max_data_size];
        int retn;
	FILE *fp;

        bzero(&serv_addr,sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(port);
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

	if((fp = fopen("save.txt","w"))==NULL){
		perror("save information");
		exit(-1);
	}
	while(1){
        	bzero(&(buff),max_data_size);
        	bytes = recv(clientfd,buff,max_data_size,0);
        	if(bytes<0){
        	        printf("recieve from client");
        	}
        	else if(bytes>0){
		        printf("recieve: %s",buff);
        	
		
			retn  = fputs(buff,fp);
			/*if(retn==-1){
				printf("write error\n");
			}
			else{
				printf("write OK\n");
			}*/
		}
		else{
			printf("save ok\n");
			break;
		}
	}
	fclose(fp);
        close(clientfd);
        close(sockfd);
        return 0;
}

