#include<sys/time.h>
#include<sys/types.h>
#include<errno.h>
#include<wait.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void signalHandler(int sig){
    switch(sig){
        case SIGALRM:
            printf("Caught [ __SIGALRM__ ]\n");
            break;
        case SIGVTALRM:
            printf("Caught ( *SIGVTALRM* )\n");
            break;
        case SIGPROF:
            printf("Caught {  ~SIGPROF~  }\n");
            break;
        default:
            printf("Error signal\n");
            break;
    }
}


int main(int argc,char *argv[]){
    int fk1,fk2,fk3;
    if((fk1=fork())<0){
        perror("fork fk1:");
        exit(-1);
    }
    else if(fk1==0){
        struct itimerval val;
        val.it_value.tv_sec = 0;
        val.it_value.tv_usec = 530000;
        val.it_interval.tv_sec = 0;
        val.it_interval.tv_usec = 350000;
        setitimer(ITIMER_REAL,&val,NULL);
		signal(SIGALRM,signalHandler);
		while(1);
		exit(0);
	}
	else{
		sleep(3);
		kill(fk1,SIGKILL);
    	if((fk2 = fork())<0){
     		perror("fork fk2:");
      		exit(-1);
   		} 
   		else if(fk2 == 0){
      		struct itimerval val;
      		val.it_value.tv_sec = 0;
       		val.it_value.tv_usec = 370000;
       		val.it_interval.tv_sec = 0;
       		val.it_interval.tv_usec = 300000;
       		setitimer(ITIMER_VIRTUAL,&val,NULL);
    		signal(SIGVTALRM,signalHandler);
			while(1);
			exit(0);
		}
		else{
			sleep(6);
			kill(fk2,SIGKILL);
   			if((fk3 = fork())<0){
   				perror("fork fk3:");
   				exit(-1);
   			}
    		else if(fk3 == 0){	
				struct itimerval val;
        		val.it_value.tv_sec = 0;
        		val.it_value.tv_usec = 350000;
        		val.it_interval.tv_sec = 0;
       			val.it_interval.tv_usec = 250000;
       			setitimer(ITIMER_PROF,&val,NULL);
				signal(SIGPROF,signalHandler);
				while(1);
				exit(0);
			}
			else{
				sleep(9);
				kill(fk3,SIGKILL);
			}
		}
	}			
	return 0;
}
