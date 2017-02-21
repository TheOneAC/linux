/*
 * get message from pipe
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
 int main(int argc, char const *argv[])
 {
 	int fd = open("test.pipe",O_RDONLY);
	if(-1 == fd){
		perror("open");exit(-1);
	}
	int i,x;
	for(i = 0 ;i < 99; i++){
		write(fd,&x,4);
		printf("Get %d \n",x);
	}
	close(fd);
 	return 0;
 }