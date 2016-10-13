#include <limits.h>
#include <pthread.h>
#include "errors.h"

void *thread_routine(void *arg)  								 // detached thread
{
	printf("this ia deatched thread\n");
	return NULL;
}
int main(int argc ,char * argv[])
{
	pthread_t thread_id;
	pthread_attr_t thread_attr;
	struct sched_param thread_param; 							 //schedualling attratition
	size_t stack_size;   										 //maybe  explained in more deep understand
	int status;
	status=pthread_attr_init(&thread_attr);    					//init thread_attr
	if(status!=0)err_abort(status, "Create attr");
	status=pthread_attr_setdetachstate(&thread_attr,PTHREAD_CREATE_DETACHED);   
																//set detach attratition
	if(status!=0)err_abort(status,"set detach");
	status=pthread_create(&thread_id,&thread_attr,thread_routine,NULL);
									 // add a attratition in pthread_create
	if(status!=0)err_abort(status,"create thread");
	printf("main exiting\n");
	pthread_exit(NULL);
	return 0;
}

