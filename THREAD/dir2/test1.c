#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<pthread.h>
int count=0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *creator(void *arg){
	printf("creator thread is running\n");
	printf("creator add lock\n");
	pthread_mutex_lock(&mutex);
	count++;
	printf("in creator count is: %d\n",count);
	if(count>0){
		pthread_cond_signal(&cond);
	}
	printf("creator release lock\n");
	pthread_mutex_unlock(&mutex);
	return 	NULL;
}

void *consumer(void *arg){
	printf("consumer thread is running\n");
	printf("consumer add lock\n");
	pthread_mutex_lock(&mutex);
	if(count<=0){
		printf("begin wait\n");
		pthread_cond_wait(&cond,&mutex);
		printf("end wait\n");
	}
	count--;
	printf("in consumer count is %d\n",count);
	pthread_mutex_unlock(&mutex);
	printf("consumer release lock\n");
	return NULL;
}

int main(){

	pthread_t tpid1,tpid2;
	for(int i=0;i<=9;++i){
		pthread_create(&tpid1,NULL,consumer,NULL);
	}
	sleep(1);
	for(int i=0;i<=9;++i){	
		pthread_create(&tpid2,NULL,creator,NULL);
	}
	pthread_join(tpid1,NULL);
	pthread_join(tpid2,NULL);
	return 0;
}
