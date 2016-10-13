#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 6789
#define SERVERADDR "127.0.0.1"
#define MAXLINE 50

int main(int argc, char const *argv[])
{
	int client_fd;
	struct sockaddr_in server;
	client_fd = socket(AF_INET, SOCK_STREAM,0);
	if(client_fd == -1){
		perror("fail to init client_fd socket");
		return -1;
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = inet_addr(SERVERADDR);
	if((connect(client_fd,(struct sockaddr*)&server,sizeof(server))) < 0){
		perror("fail to init connect to server");
		return -1;
	}
	puts("connection server success!");
	char message_send[MAXLINE],message_receive[MAXLINE];
	while(1){
		puts("$$ > :");
		fgets(message_send,sizeof(message_send),stdin);
		if(strlen(message_send) == 0)continue;
		if(strlen(message_send)== 2 && message_send[0] == 'q')break;
		int message_len = send(client_fd,message_send,sizeof(message_send),0);
		if(message_len < 0){
			perror("fail to send message");
			return -1;
		} 
		message_len = recv(client_fd,message_receive,sizeof(message_receive),0);
		if(message_len < 0){
			perror("fail to receive message");
			return -1;
		}
		printf("** < :%s",message_receive);
	}
	return 0;
}