#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#include<wait.h>
#include<limits.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
    int fd1[2],fd2[2];
    int status;
    int elder_pid,younger_pid;
    int fk1,fk2;
    char str1[10],str2[10];
    char elder_write[256] = "This is elder brother ，pid is ",younger_write[256] = "This is younger brother ，pid is ";
    char elder_read[256],younger_read[256];
    if(pipe(fd1)<0){
        perror("pipe fd1:");
        exit(EXIT_FAILURE);
    }
    if(pipe(fd2)<0){
        perror("pipe fd2:");
        exit(EXIT_FAILURE);
    }
    if((fk1=fork())<0){
        perror("fork() elder:");
        exit(EXIT_FAILURE);
    }
    
    else if(fk1==0){    // elder
        /*      elder write      */
        close(fd1[0]);
        elder_pid = getpid();
        
        /*sprintf(str1,"%d",elder_pid);    // int to char*
        printf("\nstr1: %s\n",str1);
        
        //  link the two char*
        strcat(elder_write,str1);      
        printf("after link: %s\n",elder_write);*/

        //  write to pipe
        sprintf(elder_write,"%s%d",elder_write,elder_pid);
        write(fd1[1],elder_write,sizeof(elder_write));
        close(fd1[1]);
        
        sleep(1);

        /*     elder read   */
        close(fd2[1]);
        read(fd2[0],elder_read,256);
        printf("elder read,info: %s\n\n",elder_read);
        exit(0);
    }


    else{
        // younger
        sleep(1);
        if((fk2=fork())<0){
            perror("fork() younger:");
            exit(EXIT_FAILURE);
        }
        else if(fk2==0){
            /*      younger read     */
            close(fd1[1]);
            //  read from pipe
            read(fd1[0],younger_read,256);
            close(fd1[0]);
            printf("\nyounger read,info: %s\n\n",younger_read);
            
            
            /*     younger write     */
            younger_pid = getpid();
            
            /*
            sprintf(str2,"%d",younger_pid);
            printf("str2: %s\n",str2);
            
            strcat(younger_write,str2);
            printf("after link: %s\n",younger_write);*/
            
            sprintf(younger_write,"%s%d",younger_write,younger_pid);
            close(fd2[0]);
            write(fd2[1],younger_write,sizeof(younger_write));
            exit(0);
        }
        else{
            sleep(1);
            close(fd2[1]);
            close(fd2[0]);
            waitpid(younger_pid,&status,1);
            waitpid(elder_pid,&status,1);
            exit(0);
        }
    }
    return 0;
}
