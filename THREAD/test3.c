#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<sched.h>
void *thr_fun(void *arg){
	int policy;
	pthread_t tpid;
	pthread_attr_t attr;
	int max_priority,min_priority;
	struct sched_param param;
	
	pthread_attr_init(&attr);	// 初始化线程属性变量
	pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);		// 设置线程继承性
	pthread_attr_getinheritsched(&attr,&policy);
/*
	int scope;	
	pthread_attr_setscope(&attr,PTHREAD_SCOPE_PROCESS);		// 进程内竞争资源
	pthread_attr_setscope(&attr,PTHREAD_SCOPE_SYSTEM);		// 系统级上竞争资源
	
	pthread_attr_getscope(&attr,&scope);

*/	
	printf("policy : %d\n",policy);
	if(policy==PTHREAD_EXPLICIT_SCHED){
		printf("policy : PTHREAD_EXPLICIT_SCHED\n");
	}
	if(policy==PTHREAD_INHERIT_SCHED){
		printf("policy : PTHREAD_INHERIT_SCHED\n");	
	}

	pthread_attr_setschedpolicy(&attr,SCHED_RR);	// 设置线程调度策略
	pthread_attr_getschedpolicy(&attr,&policy);
	
	printf("policy : %d\n",policy);	
	if(policy==SCHED_FIFO){
		printf("policy : SCHED_FIFO\n");
	}
	if(policy==SCHED_RR){
		printf("policy : SCHED_RR\n");
	}
	if(policy==SCHED_OTHER){
		printf("policy : SCHED_OTHER\n");
	}
	
	
	sched_get_priority_max(max_priority);	// 获得系统支持的线程优先权的最大值
	sched_get_priority_min(min_priority);	// 获得系统支持的县城优先权的最小值
	printf("max_priority: %u\n",max_priority);
	printf("min_priority: %u\n",min_priority);
	
	param.sched_priority = max_priority;	// 设置线程的调度参数
	pthread_attr_setschedparam(&attr,&param);
	printf("shced_priority: %u\n",param.sched_priority);
	
	pthread_attr_destroy(&attr);
}

int main(){
	pthread_t tpid;
	pthread_create(&tpid,NULL,thr_fun,NULL);
	pthread_join(tpid,NULL);
	return 0;
} 





