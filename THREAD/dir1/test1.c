#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<pthread.h>
#include<string.h>
pthread_key_t key;
pthread_t cur_pid;
struct info{
	char prt[256];
};
void cleanup1(void *arg){
	
	printf("thread1,exited! : key: %s\n",(char*)arg);
}

void cleanup2(void *arg){

	printf("thread2,exited! : key: %s\n",(char*)arg);
}
void *pth_func1(void *arg){
	struct info myinfo;
	struct info *get_key =NULL;
	strcpy(myinfo.prt,"hello world");
	cur_pid = pthread_self();

	pthread_setspecific(key,&myinfo);
	get_key = (struct info*)pthread_getspecific(key);
	for(int i=0;i<3;++i){
		printf("pthread ID %lu: %s\n",cur_pid,get_key->prt);
	}

	int status;
	status = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	if(status!=0){
		perror("pthread_setcancelstate:");
		exit(-1);
	}else{
		printf("pthread_setcancelstate OK\n");
	}
	
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
	
	//printf("thread1,exited! : key: %s\n",get_key->prt);
	
	pthread_cleanup_push(cleanup1,get_key->prt);
	pthread_cleanup_pop(1);
	pthread_testcancel();
	//pthread_exit((void*)0);
}

void *pth_func2(void *arg){
	int tmp = 6;
	char str[256];
	int *get_key = NULL;
	pthread_setspecific(key,&tmp);
	get_key = (int*)pthread_getspecific(key);
	
	pthread_cancel(cur_pid);
	//printf("thread2,exited! : key: %d\n",*get_key);

	sprintf(str,"%d",*get_key);
	pthread_cleanup_push(cleanup2,str);
	pthread_cleanup_pop(1);
	pthread_exit((void*)0);
}
int main(){
	pthread_t ptid1,ptid2;
	void *ret;
	pthread_key_create(&key,NULL);
	pthread_create(&ptid1,NULL,pth_func1,NULL);
	pthread_create(&ptid2,NULL,pth_func2,NULL);
	pthread_join(ptid2,(void**)&ret);
	pthread_join(ptid1,(void**)&ret);
	printf("thread1 exit status: %ls\n",(int*)ret);
	printf("thread2 exit status: %ls\n",(int*)ret);
	pthread_key_delete(key);
	return 0;
}
