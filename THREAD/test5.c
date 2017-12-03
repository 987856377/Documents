#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<string.h>
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
char buff[128];
void *thr_fun(void *arg){
	while(1){
		pthread_mutex_lock(&mutex);
		if(buff[0]=='\0'){
			pthread_mutex_unlock(&mutex);
			sleep(1);
			printf("4\n");
		}
		else{
			if(!strncmp(buff,"end",3)){
				pthread_mutex_unlock(&mutex);
				break;
			}
			printf("read : %s\n",buff);
			buff[0]='\0';
			pthread_mutex_unlock(&mutex);
			printf("5\n");
		}
	}
}
int main(){
	pthread_t tpid;
	pthread_mutex_init(&mutex,NULL);
	pthread_create(&tpid,NULL,thr_fun,NULL);
	printf("input something , enter 'end' stop!\n");
	while(1){
		pthread_mutex_lock(&mutex);
		if(buff[0]=='\0'){
			printf("1\n");
			fgets(buff,128,stdin);
			pthread_mutex_unlock(&mutex);
		}
		else if(!strncmp(buff,"end",3)){
				printf("2\n");
				break;			
		}
		else{
			printf("3\n");
			pthread_mutex_unlock(&mutex);
			sleep(1);
		}
	}	
	pthread_mutex_unlock(&mutex);
	pthread_join(tpid,NULL);
	pthread_mutex_destroy(&mutex);
	return 0;
}
