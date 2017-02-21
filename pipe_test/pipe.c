/*
 * send message into pipe
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
int main(int argc, char const *argv[])
{
	int status = mkfifo("test.pipe",0666);
	if(status == -1){
		perror("mkfifo");exit(-1);
	}
	int fd = open("test.pipe",O_WRONLY);
	if(-1 == fd){
		perror("open");exit(-1);
	}
	int i;
	for(i = 0 ;i < 99; i++){
		write(fd,&i,4);
		sleep(100);
		printf("werite%d  ",i);
		if(i % 10 == 0)printf("\n");
	}
	printf("\n");
	close(fd);
	return 0;
}