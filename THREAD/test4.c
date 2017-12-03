#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
pthread_key_t key;
struct msg{
	int i;
	float j;
};

void *thr_fun1(void *arg){
	struct msg myMsg;
	struct msg *pMsg;
	myMsg.i = 1;
	myMsg.j = 1.2;
	pthread_setspecific(key,&myMsg);
	printf("MSG has been created!!!\n");
	pMsg = (struct msg*)pthread_getspecific(key);
	printf("pMsg->i : %d\n",pMsg->i);
	printf("pMsg->j : %f\n",pMsg->j);
}

void *thr_fun2(void *arg){
	int tmp = 10;
	sleep(1);
	int *getKey = NULL;
	pthread_setspecific(key,&tmp);
	printf("tmp has been set\n");
	getKey = (int *)pthread_getspecific(key);
	printf("get tmp from key : %d\n",*getKey);
	
}

int main(){
	pthread_t tpid1,tpid2;
	pthread_key_create(&key,NULL);
	pthread_create(&tpid1,NULL,thr_fun1,NULL);
	pthread_create(&tpid2,NULL,thr_fun2,NULL);	
	pthread_join(tpid1,NULL);
	pthread_join(tpid2,NULL);
	pthread_key_delete(key);
	return 0;
}
