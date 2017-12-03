#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<pthread.h>
#include<sys/types.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int global=0;
void *th_fun(){
	int i,j;
	j=global;
	pthread_mutex_lock(&mutex);
	for(i=0;i<9;++i){
		j+=1;
		global=j;
		printf("in thread: %d\n",global);
		sleep(1);
	}
	pthread_mutex_unlock(&mutex);
}
int main(){
	pthread_t tpid;
	int errno;
	errno = pthread_create(&tpid,NULL,th_fun,NULL);
	if(errno!=0){
		perror("pthread_create");
		exit(-1);
	}
	pthread_mutex_lock(&mutex);
	for(int i=0;i<9;++i){
		global+=1;
		printf("in main：%d\n",global);
		sleep(1);
	}
	pthread_mutex_unlock(&mutex);
	pthread_join(tpid,NULL);
	printf("at last: %d\n",global);
	return 0;
}
