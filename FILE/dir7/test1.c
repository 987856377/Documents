#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argv[]){
    FILE *fp1;
    char ch;
    char *str = (char*)malloc(15*sizeof(char));
    if((fp1=fopen("testfile","w+"))==NULL){
        perror("open file");
    }
/*
    fputc('w',fp1);
    ch = fgetc(fp1);    
    fputc(ch,stdout);
*/	
    fseek(fp1,0,SEEK_SET); // the same to next line
    rewind(fp1);

    fputs("hello world",fp1);
    printf("off_set is: %ld\n",ftell(fp1)); 

    rewind(fp1);
    fgets(str,15,fp1);
    fputs(str,stdout);

    puts("\nenter a string:");
    fgets(str,sizeof(str),stdin);
    fputs(str,stdout);
    
    free(str);
    str = NULL;
    fclose(fp1);
    return 0;
}
