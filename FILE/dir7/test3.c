#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
	char ch;
	ch = getchar();
	putchar(ch);
	printf("\n");	

	char *string = "GG Bang\n";
	puts(string);

	FILE *fp;
	char *str = (char*)malloc(20*sizeof(char));
	if((fp=fopen("file1","w+"))==NULL){
		printf("open file error\n");
		return -1;
	}
	//rewind(fp);
	//fseek(fp,0,SEEK_SET);
	fprintf(fp,"hello World\n");
	fputs("GG",fp);
	fclose(fp);
	fp = fopen("file1","r");

	fgets(str,20,fp);
	printf("%s",str);

	fgets(str,2,fp);
	printf("%s\n",str);

	fclose(fp);
	return 0;
}
