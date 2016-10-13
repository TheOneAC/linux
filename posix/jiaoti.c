#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#define MAX 30
pthread_mutex_t child_mutex,parent_mutex;

void * child(void*arg)
{
	pthread_mutex_lock(&child_mutex);
	int i;
	for(i=1;i<=10;i++)
	{
		sleep(1);
		printf("this is child :%d\n",i);
	}
	pthread_mutex_unlock(&parent_mutex);
}
void * parent(void*arg)
{
	pthread_mutex_lock(&parent_mutex);
	int i;
	for(i=1;i<=20;i++)
	{
		sleep(1);
		printf("this is parent :%d\n",i);
	}
	pthread_mutex_unlock(&child_mutex);
}
int main()
{
	pthread_t child_id,parent_id;
        pthread_mutex_init(&child_mutex,0);
	pthread_mutex_init(&parent_mutex,0);
	pthread_mutex_lock(&parent_mutex);
	int i;
	for(i=1;i<=MAX;i++)
	{
		printf("the %dth implement:\n",i);
		pthread_create(&child_id,0,child,0);
		pthread_create(&parent_id,0,parent,0);
		pthread_join(child_id,0);
		pthread_join(parent_id,0);
	}
	pthread_mutex_destroy(&child_mutex);
	pthread_mutex_destroy(&parent_mutex);
}
