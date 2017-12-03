#include<sys/msg.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/sem.h>
union semun{
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *info;
};
int main(){
	int fk;
	int semid;
	key_t key;
	key = ftok(".",3);
	semid=semget(key,1,IPC_CREAT | 0666);
	if(semid==-1){
		perror("parent semget:");
		exit(-1);
	}
	
	struct sembuf sbuf = {0,-1,IPC_NOWAIT};
	union semun semopts;
	semopts.val = 5;
	if((semctl(semid,0,SETVAL,semopts))==-1){
		perror("parent semctl:");
		exit(-1);
	}


	if((fk=fork())==-1){
		perror("fork");
		exit(-1);
	}

	else if(fk==0){
		semid = semget(key,1,IPC_CREAT | 0666);
		if(semid==-1){
			perror("child semget:");
			exit(-1);
		}
		int semval;
		
		while(1){
			if((semval=semctl(semid,0,GETVAL,0))==-1){
				perror("child semctl:");
				exit(-1);
			}
			if(semval>0){
				printf("semval is: %d\n",semval);
			}
			else{
				printf("stop\n");
				break;
			}
			sleep(1);
		}
	}

	else{
		while(1){
			if(semop(semid,&sbuf,1)==-1){
				break;
			}
			sleep(1);
		}
		sleep(3);
	}
	return 0;
}
