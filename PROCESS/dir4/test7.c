#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
int main(){
	int i;

	if((i=access("test1.c",F_OK | R_OK | W_OK))==-1){
		perror("access test1.c");
		exit(EXIT_FAILURE);
	}
	else{
		printf("Access test1.c OK\n");
	}
	return 0;
}
