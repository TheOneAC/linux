#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 6789
#define SERVERAADR "127.0.0.1"
#define MAXLINE 50
#define CONNECT_LIMIT 5

void* server_thread(void* arg){
	int servering_clientfd = *((int *)arg);
	char message_receive[MAXLINE];

	int message_len;
	while((message_len = recv(servering_clientfd, message_receive, sizeof(message_receive),0)) > 0){
		message_receive[message_len] = '\0';
		puts(message_receive);

		message_len = send(servering_clientfd, message_receive, sizeof(message_receive),0);
		if(message_len < 0){
			perror("message send failure");
			return NULL;
		}
	}
	if(message_len == 0){
		puts("client not connect");
		fflush(stdout);
	}
	else if(message_len == -1){
		perror("\n recv failed");
	}
	pthread_exit(0);
}

int main(int argc, char const *argv[])
{
	int server_fd, client_fd;
	struct sockaddr_in server, client;
	server_fd =socket(AF_INET,SOCK_STREAM,0);
	if(server_fd <0){
		perror("server socket init failure");
		return -1;
	}
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);
	if(bind(server_fd, (struct sockaddr *)&server,sizeof(server)) < 0){
		perror("bind failure");
		return -1;
	}
	listen(server_fd,CONNECT_LIMIT);
	int client_len = sizeof(struct sockaddr_in);
	while((client_fd = accept(server_fd,(struct sockaddr *)&client,(socklen_t*)&client_len)) > 0){
		puts("------A new connection-----");
		pthread_t thread;
		if(pthread_create(&thread,NULL, &server_thread,(void*)&client_fd) < 0){
			perror("create thread failure");
			return -1;
		}
		pthread_join(thread,NULL);
	}
	return 0;
}