/*
 *
 * three thread print A B C respectively 
 * Synchronous  by cond_wait in pthread
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define threads 3
int count =10;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t cond_a = PTHREAD_COND_INITIALIZER;
//pthread_cond_t cond_b = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond[threads];
char arg[threads];
void * print_a(void*argu){
	int index = 0;
	pthread_mutex_lock(&mutex);
	while(count){
		pthread_cond_wait(&cond[index],&mutex);
		printf("*********%d times **********\n",count);
		printf("A >> !\n");
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&cond[1]);
		//sleep(1);
	}
	//return NULL;
	exit(0);
}
void * print_b(void*argu){
	int index = 1;
	pthread_mutex_lock(&mutex);
	while(count){
		pthread_cond_wait(&cond[index],&mutex);
		printf("B >> !\n");
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&cond[2]);
		//sleep(1);
	}
	//return NULL;
	exit(0);
}
void * print_c(void*argu){
	int index = 2;
	pthread_mutex_lock(&mutex);
	while(count){
		pthread_cond_wait(&cond[index],&mutex);
		printf("C >> !\n");
		count--;
		pthread_mutex_unlock(&mutex);
		
		//sleep(1);
	}
	exit(0);
}


int main()
{
	int status,i;
	pthread_t pid[threads];
	for(i=0;i< threads;i++){
		//cond[i] = PTHREAD_COND_INITIALIZER;
		status = pthread_cond_init (&cond[i], NULL);
    	if (status != 0){ printf("init error");return 0;}
	}
	pthread_create(&pid[0],NULL,print_a,NULL);
	pthread_create(&pid[1],NULL,print_b,NULL);
	pthread_create(&pid[2],NULL,print_c,NULL);
	while(count){
		pthread_cond_signal(&cond[0]);
		sleep(1);
	}

	for(i=0;i< threads;i++){
		status = pthread_join(pid[i], NULL);
		if(status != 0){ printf("create error");return 0;}
	}
	return 0;
}
