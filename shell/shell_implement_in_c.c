/*
You should be familiar with the so-called shell programs. These are programs that run in a terminal window
and accept commands typed by the user. Implement a small shell that repeatedly asks for the program name and
then executes that program using fork() and exec; you can use wait() function to make the parent process wait for
the child to terminate.
To simplify the problem, fill in the missing part of the following program:
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#define NUM 1024
#define SIZE 50
int mystrtok(char *argv[], char* string){
int i=0;
char delim[]=" ";
char *p;
argv[0] = strtok(string,delim);
while(argv[i]!=NULL){
argv[++i] = strtok(NULL,delim);
// printf("%d is %s\n",i,argv[i]);
}
return 0;
}
int main(){
char str[NUM];
int status;
pid_t pid;
char * argv[NUM];
while(1){
printf("\n$:");
gets(str);
status = mystrtok(argv,str);
if(status!=0){
printf("fail to get command!\n");
}
pid = fork();
if(pid==-1) printf("fork failure!\n");
else if(pid==0) {
	execvp(argv[0], argv);
/* Please fill in part of the program here.*/
}
else {
wait();
}
}
}
