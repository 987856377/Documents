#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALAZER;	// 静态分配互斥量
//pthread_cond_t cond = PTHREAD_COND_INITIALAZER;		// 静态分配条件量
pthread_cond_t cond;
pthread_mutex_t mutex;
int i=1,j=9;

void *thr_fun1(void *arg){
	sleep(1);
	printf("1\n");
	while(1){
		printf("3\n");
		if(i==j){
			printf("5\n");
			pthread_mutex_lock(&mutex);
			printf("7\n");
			pthread_cond_signal(&cond);		// 满足条件,发送信号给条件变量，解锁一个或多个等待它的线程
			printf("9\n");
			pthread_mutex_unlock(&mutex);
			sleep(1);
		}
		else{
			++i;
			--j;
			printf("i = %d   j = %d\n",i,j);
			printf("11\n");
		}
	}
}
void *thr_fun2(void *arg){	
	// struct timespec timeout;
	// timeout.tv_sec = time(0)+3;
	while(1){
		printf("2\n");
		if(i!=j){
			// pthread_con_timewait(&cond,&mutex,&timeout); // 在pthread_cond_wait 的条件下增加了时间限制
			printf("4\n");
			pthread_mutex_lock(&mutex);
			printf("6\n");
			pthread_cond_wait(&cond,&mutex);	// 自动解锁互斥量及等待条件变量
			printf("8\n");
		}
		printf("i = %d  j = %d\n",i,j);
		i=1;j=9;
		pthread_mutex_unlock(&mutex);
	}
}
int main(){
	pthread_t tpid1,tpid2;
	pthread_cond_init(&cond,NULL);
	pthread_mutex_init(&mutex,NULL);
	
	pthread_create(&tpid1,NULL,thr_fun1,NULL);
	pthread_create(&tpid2,NULL,thr_fun2,NULL);
	while(1);	
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	pthread_join(tpid1,NULL);
	pthread_join(tpid2,NULL);	
	return 0;
}
