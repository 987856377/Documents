#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>
void *thr_fun(void *arg){
	printf("the thread have been created!\n");
}
int main(){
	pthread_t tpid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);    	// pthread_create_detached
	printf("the thread have been set detached!\n");
	
	sleep(1);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);		// pthread_create_joinable
	printf("the thread have been set joinable!\n");
	
	sleep(1);	
	pthread_create(&tpid,&attr,thr_fun,NULL);
	
	pthread_attr_destroy(&attr);

	pthread_exit(0);
	sleep(1);
	return 0;
}
